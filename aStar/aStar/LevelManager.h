//#pragma once
//#include "ECS.h"
//#include "SpriteComponent.h"
//#include "ComponentList.h"
//#include "Collisions.h"
//#include "SystemTemplate.h"
//#include "SpriteComponent.h"
//#include "World.h"
////#include <TextureHandler.h>
//class LevelManager:public System
//{
//public:
//	/// <summary>
//	/// reserves space for four portals
//	/// </summary>
//	LevelManager() {
//		m_entities.reserve(4);
//	}
//	~LevelManager() {}
//	/// <summary>
//	/// iterates through all the portals for collision detection
//	/// </summary>
//	/// <param name="ent">the entity to check collision with</param>
//	void checkCollision(Entity *ent)
//	{
//		if (ent != nullptr)
//		{
//			if (GatesActive == true)
//			{
//				for (int i = 0; i < m_entities.size(); i++)
//				{
//					if (Collisions::collisionDetection(m_entities[i]->getComponent<PositionComponent>(), ent->getComponent<PositionComponent>()))
//					{
//						ChangeRoom();
//					}
//				}
//			}
//		}
//	}
//	/// <summary>
//	/// function called after room changing, this sets certain flags, calls the world init function
//	/// </summary>
//	void ChangeRoom()
//	{
//		m_world->init(m_nextLevel);
//		m_CurrentLevel = m_nextLevel;
//		m_nextLevel++;
//		GatesActive = false;
//		ChangingLevel = true;
//	}
//	/// <summary>
//	/// Draw function
//	/// </summary>
//	/// <param name="render">The sdl renderer</param>
//	void draw(SDL_Renderer *render)
//	{
//		if (GatesActive == true)
//		{
//			for (int i = 0; i < m_entities.size(); i++)
//			{
//				m_entities[i]->getComponent<PositionComponent>().setRotation(gateRotation);
//				m_entities[i]->getComponent<SpriteComponent>().setRotation(gateRotation);
//				m_entities[i]->draw(render);
//			}
//			gateRotation += 0.3f;
//		}
//	}
//	/// <summary>
//	/// adds an entity to the vector
//	/// </summary>
//	/// <param name="ent"></param>
//	void addEntity(Entity *ent) override
//	{
//		m_entities.push_back(ent);
//	}
//	/// <summary>
//	/// Assigns the local pointer to the world object
//	/// </summary>
//	/// <param name="worl"></param>
//	void setWorld(World * worl) {
//		m_world = worl;
//	}
//	bool GatesActive=true;
//	bool ChangingLevel = false;
//private:
//	//manages different levels
//	World *m_world;
//	int m_CurrentLevel = 0;
//	int m_nextLevel = 1;
//	float gateRotation = 0;
//};
