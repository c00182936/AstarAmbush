#pragma once
#include "ECS.h"
#include "ComponentList.h"
#include "Observer.h"
class System
{

protected:
	std::vector<Entity*> m_entities;
	std::vector<Observer*> m_observers;
	bool m_removed;

public:
	System() { m_entities.reserve(50); m_observers.reserve(50); m_removed = false; };
	virtual ~System() {};

	virtual void update() {};
	virtual void addEntity(Entity *ent) {};

	virtual void refresh()
	{
		int startSize = m_entities.size();

		m_entities.erase(std::remove_if(std::begin(m_entities), std::end(m_entities),
			[](Entity* mEntity)
		{
			return !mEntity->isActive() || mEntity == nullptr;
		}),
			std::end(m_entities));

		int endSize = m_entities.size();

		if (startSize != endSize)
		{
			m_removed = true;
		}
	}

	virtual bool getRemoved() { return m_removed; };
	virtual void setRemove(bool value) {};
};
