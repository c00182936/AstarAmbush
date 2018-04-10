#pragma once
#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <bitset>
#include <array>
#include <SDL.h>

class Component;
class Entity;
class EntityManager;

enum Groups : size_t
{
	PlayerGroup,
	EnemyGroup,
	PortalGroup
};

using ComponentID = std::size_t;
using Group = std::size_t;

inline ComponentID getComponentTypeID()
{
	static ComponentID lastID = 0;
	return lastID++;
}

template <typename T> inline ComponentID getComponentTypeID() noexcept
{
	static ComponentID typeID = getComponentTypeID();
	return typeID;
}


constexpr std::size_t maxComponents = 32;
constexpr std::size_t maxGroups = 32;

using GroupBitSet = std::bitset<maxGroups>;

using ComponentBitSet = std::bitset<maxComponents>;
using ComponentArray = std::array<Component*, maxComponents>;

class Component
{
public:
	virtual ~Component() {};
	virtual void init() {};
	virtual void update() {};
	virtual void Draw(SDL_Renderer * Renderer) {};

	Entity * m_owner;
private:

};

class Entity
{
public:
	Entity(EntityManager & Manager) : m_manager(Manager) {};

	virtual ~Entity() {};
	void update()
	{
		for (auto& c : m_components)
		{
			c->update();
		}
	}

	void draw(SDL_Renderer * Renderer) 
	{
		for (auto& c : m_components)
		{
			c->Draw(Renderer);
		}
	};

	bool isActive() { return m_active; };
	void destroy() { m_active = false; };

	bool hasGroup(Group group)
	{
		return m_groupBitSet[group];
	};

	void addGroup(Group group);

	void delGroup(Group group)
	{
		m_groupBitSet[group] = false;
	}

	template <typename t> bool hasComponent() const
	{
		return ComponentBitSet[getComponentTypeID<t>()];
	}

	/// <summary>
	/// adds one component which takes multiple arguments
	/// </summary>
	template<typename t, typename... TArgs>
	t& addComponent(TArgs&&... mArgs)
	{
		t* c(new t(std::forward<TArgs>(mArgs)...));
		c->m_owner = this;

		std::unique_ptr<Component> uPtr{ c };
		m_components.emplace_back(std::move(uPtr));

		m_componentArray[getComponentTypeID<t>()] = c;
		m_componentBitset[getComponentTypeID<t>()] = true;

		c->init();
		return *c;
	}
	
	/// <summary>
	///  example of use
	///  gameobject.getComponent<PositionComponent>().setXpos(25);
	/// 
	/// </summary>
	/// <returns></returns>
	template<typename t> 
	t& getComponent()
	{
		auto ptr(m_componentArray[getComponentTypeID<t>()]);
		return *static_cast<t*>(ptr);
	}


private:
	bool m_active = true;
	std::vector<std::unique_ptr<Component>> m_components;
	ComponentArray m_componentArray;
	ComponentBitSet m_componentBitset;
	GroupBitSet m_groupBitSet;
	EntityManager & m_manager;
};


class EntityManager
{
public:
	void update()
	{
		for (auto& e : m_entities)
		{
			e->update();
		}
	}
	void Draw(SDL_Renderer * Renderer)
	{
		for (auto& e : m_entities)
		{
			e->draw(Renderer);
		}
	}

	/// <summary>
	/// Removes entities whose m_active is set to false
	/// </summary>
	void refresh()
	{
		for (auto i(0u); i < maxGroups; i++)
		{
			auto& v(m_groupedEntities[i]);

			v.erase(std::remove_if(std::begin(v), std::end(v), [i](Entity* mEntity)
			{
				return !mEntity->isActive() || !mEntity->hasGroup(i);
			}),
				std::end(v));
		}

		m_entities.erase(std::remove_if(std::begin(m_entities), std::end(m_entities),
			[](const std::unique_ptr<Entity> &mEntity)
		{
			return !mEntity->isActive();
		}),
			std::end(m_entities));
	}

	Entity& addEntity(Entity * arg)
	{
		std::unique_ptr<Entity> uptr{ arg };
		m_entities.emplace_back(std::move(uptr));
		
		return *arg;
	}

	Entity& CreateEntity()
	{
		Entity * e = new Entity(*this);
		std::unique_ptr<Entity> uptr{ e };
		m_entities.emplace_back(std::move(uptr));
		return *e;
	}

	void addToGroup(Entity * ent, Group group)
	{
		m_groupedEntities[group].emplace_back(ent);
	}

	std::vector<Entity*>& getGroup(Group group)
	{
		return m_groupedEntities[group];
	}

	std::vector<std::unique_ptr<Entity>> const& getEntities() const
	{
		return m_entities;
	}

private:
	std::vector<std::unique_ptr<Entity>> m_entities;
	std::array<std::vector<Entity*>, maxGroups> m_groupedEntities;
};