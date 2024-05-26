#pragma once

#include "../Util/Pool.h"

#include <algorithm>
#include <bitset>
#include <deque>
#include <memory>
#include <set>
#include <typeindex>
#include <unordered_map>
#include <map>
#include <list>
#include <vector>


const unsigned int MAX_COMPONENTS = 32;
typedef std::bitset<MAX_COMPONENTS> Signature;

class IComponent {
protected:
	inline static size_t nextId;
};

template<typename TComponent>
class Component : public IComponent {
public:
	static size_t GetId() {
		static size_t id = nextId++;
		return id;
	}
};

class Entity {
	size_t id = 0;
public:
	Entity(size_t id) : id(id) {}
	Entity(const Entity& entity) = default;

	size_t GetId() const;
	void Kill();

	bool operator ==(const Entity& other) const { return id == other.id; }
	bool operator !=(const Entity& other) const { return id != other.id; }
	bool operator >(const Entity& other) const { return id > other.id; }
	bool operator <(const Entity& other) const { return id < other.id; }

	//Manage Components
	template<typename TComponent, typename ...TArgs>
	void AddComponent(TArgs&& ...args);

	template<typename TComponent>
	void RemoveComponent();

	template<typename TComponent>
	bool HasComponent() const;

	template<typename TComponent>
	TComponent& GetComponent() const;

	void AddTag(const std::string& tag) const;
	std::string GetTag() const;

	class ECSManager* manager = nullptr;
};

class System {
	Signature componentSignature;
	std::vector<Entity> entities;
public:
	System() = default;
	~System() = default;

	void AddEntityToSystem(Entity entity);
	void RemoveEntityFromSystem(Entity entity);

	std::vector<Entity> GetSystemEntities() const;

	const Signature& GetComponentSignature() const;

	template<typename TComponent>
	void RequireComponent();
};

class ECSManager {
	size_t numEntities = 0;
	
	std::vector<std::shared_ptr<IPool>> componentPools;
	
	std::vector<Signature> entityComponentSignatures;
	
	std::unordered_map<std::type_index, std::shared_ptr<System>> systems;

	std::set<Entity> entitiesToBeAdded;
	std::set<Entity> entitiesToBeKilled;
	
	std::deque<size_t> freeIds;

	// Tags
	std::map<int, std::string> entityTag;
	
	std::map<std::string, std::list<int>> entityGroups;

public:
	void Update();
	//Manage Entities
	Entity CreateEntity();
	void KillEntity(Entity entity);

	//Manage Components
	template<typename TComponent, typename ...TArgs>
	void AddComponent(Entity entity, TArgs&& ...args);

	template<typename TComponent>
	void RemoveComponent(Entity entity);

	template<typename TComponent>
	bool HasComponent(Entity entity) const;

	template<typename TComponent>
	TComponent& GetComponent(Entity entity) const;

	//Manage Sytems
	template<typename TSystem, typename ...TArgs>
	void AddSystem(TArgs&& ...args);

	template<typename TSystem>
	void RemoveSystem();

	template<typename TSystem>
	void HasSystem() const;

	template<typename TSystem>
	TSystem& GetSystem() const;

	//General Manage
	void AddEntityToSystem(Entity entity);
	void RemoveEntityToSystem(Entity entity);

	// Tag management
	void AddTagToEntity(Entity entity, const std::string& tag);
	std::string GetTagFromEntity(Entity entity);
	void ClearTags();
};

template<typename TComponent>
void System::RequireComponent() {
	size_t componentId = Component<TComponent>::GetId();
	componentSignature.set(componentId);
}

template<typename TComponent, typename ...TArgs>
void ECSManager::AddComponent(Entity entity, TArgs && ...args) {
	const auto componentId = Component<TComponent>::GetId();
	const auto entityId = entity.GetId();

	if (componentId >= componentPools.size()) {
		componentPools.resize(componentId + 1, nullptr);
	}

	if (!componentPools[componentId]) {
		componentPools[componentId] = std::make_shared<Pool<TComponent>>();
	}

	std::shared_ptr<Pool<TComponent>> componentPool 
		= std::static_pointer_cast<Pool<TComponent>>(componentPools[componentId]);

	if (entityId >= componentPool->GetSize()) {
		componentPool->Resize(entityId + 1);
	}

	TComponent newComponent(std::forward<TArgs>(args)...);
	
	componentPool->Set(entityId, newComponent);
	entityComponentSignatures[entityId].set(componentId);
}

template<typename TComponent>
void ECSManager::RemoveComponent(Entity entity) {
	const auto componentId = Component<TComponent>::GetId();
	const auto entityId = entity.GetId();

	entityComponentSignatures[entityId].set(componentId, false);
}

template<typename TComponent>
bool ECSManager::HasComponent(Entity entity) const {
	const auto componentId = Component<TComponent>::GetId();
	const auto entityId = entity.GetId();

	return entityComponentSignatures[entityId].test(componentId);
}

template<typename TComponent>
TComponent& ECSManager::GetComponent(Entity entity) const
{
	const auto componentId = Component<TComponent>::GetId();
	const auto entityId = entity.GetId();

	std::shared_ptr<Pool<TComponent>> componentPool
		= std::static_pointer_cast<Pool<TComponent>>(componentPools[componentId]);
	
	return componentPool->Get(entityId);
}

template<typename TSystem, typename ...TArgs>
void ECSManager::AddSystem(TArgs && ...args) {
	std::shared_ptr<System> newSystem = std::make_shared<TSystem>(
		std::forward<TArgs>(args)...);
	systems.insert(std::make_pair(std::type_index(typeid(TSystem)), newSystem));
}

template<typename TSystem>
void ECSManager::RemoveSystem() {
	auto it = systems.find(std::type_index(typeid(TSystem)));
	systems.erase(it);
}

template<typename TSystem>
void ECSManager::HasSystem() const {
	auto it = systems.find(std::type_index(typeid(TSystem)));
	return it != systems.end();
}

template<typename TSystem>
TSystem& ECSManager::GetSystem() const
{
	auto it = systems.find(std::type_index(typeid(TSystem)));
	return *(std::static_pointer_cast<TSystem>(it->second));
}

template<typename TComponent, typename ...TArgs>
void Entity::AddComponent(TArgs && ...args) {
	manager->AddComponent<TComponent>(*this, std::forward<TArgs>(args)...);
}

template<typename TComponent>
void Entity::RemoveComponent() {
	manager->RemoveComponent<TComponent>(*this);
}

template<typename TComponent>
bool Entity::HasComponent() const {
	return manager->HasComponent<TComponent>(*this);
}

template<typename TComponent>
TComponent& Entity::GetComponent() const
{
	return manager->GetComponent<TComponent>(*this);
}
