#pragma once

#include "Event.h"
#include <map>
#include <memory>
#include <list>
#include <map>
#include <typeindex>

class IEventCallback
{
	virtual void Call(Event& e) = 0;
public:
	~IEventCallback() = default;
	void Execute(Event& e) {
		Call(e);
	}
private:

};

template <typename TOwner, typename TEvent>
class EventCallback : public IEventCallback {
	typedef void (TOwner::* CallbackFunction)(TEvent&);

	TOwner* owner;
	CallbackFunction function;

	virtual void Call(Event& e) override {
		std::invoke(function, owner, static_cast<TEvent&>(e));
	}

public:
	EventCallback(TOwner* owner, CallbackFunction function) {
		this->owner = owner;
		this->function = function;
	}

	virtual ~EventCallback() = default;
};

typedef std::list<std::shared_ptr<IEventCallback>> HanddlerList;

class EventManager {
	std::map<std::type_index, std::shared_ptr<HanddlerList>> subscribers;

public:
	EventManager() {}
	~EventManager() {}

	void Clear() {
		subscribers.clear();
	}

	template <typename TOwner, typename TEvent>
	void SubscribeToEvent(TOwner* owner, void (TOwner::* function)(TEvent&)) {
		if (!subscribers[typeid(TEvent)].get()) {
			subscribers[typeid(TEvent)] = std::make_shared<HanddlerList>();
		}

		auto subscriber = std::make_shared<EventCallback<TOwner, TEvent>>(owner, function);
		subscribers[typeid(TEvent)]->push_back(subscriber);
	}

	template <typename TEvent, typename ...TArgs>
	void EmitteEvent(TArgs&& ...args) {
		auto handler = subscribers[typeid(TEvent)].get();
		if (handler) {
			for (auto it = handler->begin(); it != handler->end(); it++) {
				auto subscriber = *it;
				TEvent e(std::forward<TArgs>(args)...);
				subscriber->Execute(e);
			}
		}
	}

};
