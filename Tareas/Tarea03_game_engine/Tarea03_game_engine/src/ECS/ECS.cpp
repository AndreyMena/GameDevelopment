#include "ECS.h"
#include <iostream>

size_t Entity::GetId() const {
	return id;
}

void Entity::Kill() {
	manager->KillEntity(*this);
}

void Entity::AddTag(const std::string& tag) const {
	manager->AddTagToEntity(*this, tag);
}

std::string Entity::GetTag() const {
	return manager->GetTagFromEntity(*this);
}

void System::AddEntityToSystem(Entity entity) {
	entities.push_back(entity);
}

void System::RemoveEntityFromSystem(Entity entity) {
	auto newEnd = std::remove_if(
		entities.begin(),
		entities.end(),
		[&entity](Entity other) {
			return entity == other;
		}
	);
	entities.erase(newEnd, entities.end());
}

std::vector<Entity> System::GetSystemEntities() const
{
	return entities;
}

const Signature& System::GetComponentSignature() const
{
	return componentSignature;
}

void ECSManager::Update() {
	for (auto entity : entitiesToBeAdded) {
		AddEntityToSystem(entity);
	}
	entitiesToBeAdded.clear();

	for (auto entity : entitiesToBeKilled) {
		RemoveEntityToSystem(entity);
		entityComponentSignatures[entity.GetId()].reset();
		freeIds.push_back(entity.GetId());
	}

	entitiesToBeKilled.clear();
}

Entity ECSManager::CreateEntity() {
	size_t entityId;

	if (freeIds.empty()) {
		entityId = numEntities++;
		if (entityId >= entityComponentSignatures.size()) {
			entityComponentSignatures.resize(entityId + 1);
		}
	}else{
		entityId = freeIds.front();
		freeIds.pop_front();
	}

	Entity entity(entityId);
	entity.manager = this;
	entitiesToBeAdded.insert(entity);

	std::cout << "Entity id: " << entity.GetId() << std::endl;

	return entity;
}

void ECSManager::KillEntity(Entity entity) {
	entitiesToBeKilled.insert(entity);
}

void ECSManager::AddEntityToSystem(Entity entity) {
	const auto entityId = entity.GetId();
	const auto& eSig = entityComponentSignatures[entityId];

	for (auto system: systems) {
		const auto& sSig = system.second->GetComponentSignature();

		bool isInterested = (eSig & sSig) == sSig;

		if (isInterested) {
			system.second->AddEntityToSystem(entity);
		}
	}

}

void ECSManager::RemoveEntityToSystem(Entity entity) {
	//Remover tag del map asociado al id del entity
	entityTag.erase(entity.GetId());

	//TODO remover del entityGroups, esto no se usa, pero si se usara hay que eliminarlo

	//Remueve la entidad del sistema
	for (auto system : systems) {
		system.second->RemoveEntityFromSystem(entity);
	}
}

std::set<Entity> ECSManager::GetEntitiesToBeAdded() {
	return entitiesToBeAdded;
}

void ECSManager::AddTagToEntity(Entity entity, const std::string& tag) {
	auto it = entityTag.find(entity.GetId());

	// Si la entidad ya tiene un tag entonces no hace nada
	if (it != entityTag.end()) {
		return;
	}

	// Agregar el tag a la entidad
	entityTag.emplace(entity.GetId(), tag);
	
	// Agregar la entidad al grupo
	entityGroups[tag].push_back(entity.GetId());
}

std::string ECSManager::GetTagFromEntity(Entity entity) {
	auto tag = entityTag[entity.GetId()];
	return tag;
}

void ECSManager::ClearTags() {
	entityTag.clear();
	entityGroups.clear();
}

void ECSManager::KillAllEntities() {
	// Marca todas las entidades para ser eliminadas
	for (size_t entityId = 0; entityId < numEntities; ++entityId) {
		Entity entity(entityId);
		entitiesToBeKilled.insert(entity);
	}
	freeIds.clear();
	//numEntities = 0;

	// Actualiza el sistema para eliminar las entidades marcadas
	// Al quitarlo de aqui se bugea en el cambio de niveles
	Update();
}