#pragma once
#include "ECS.h"
#include "GameData.h"
#include "SystemTemplate.h"
//#include "BulletHandler.h"
#include "AIBehaviour.h"

class AISystem : System
{
public:
	//Enum used to differentiate between different AI types.
	enum aiTypes
	{
		ALLY,
		DOG,
		PISTOL,
		ENGINEER,
		SLIME,
		JUGGERNAUT,
		TANK
	};

	/// <summary>
	/// Default constructor.
	/// </summary>
	AISystem()
	{
		//pf.AStar(finder.GetNearestCell(CD_Vector(64, 64)), finder.GetNearestCell(CD_Vector(639, 639)));
	}

	void InitializePathfinder()
	{
		pf = PathFinder(GameData::m_roomLayout.at(0));
		pf.AddLinks();
	}

	//void InitialiseBulletHandler(BulletHandler * bullets)
	//{
	//	//m_BulletHandler = bullets;
	//}
	/// <summary>
	/// Loops through all attached entities and updates them.
	/// Maybe the actual logic should be placed here instead.
	/// </summary>
	void update() override
	{
		refresh();

		//m_BulletHandler->SetFiring(true);

		for (int i = 0; i < m_entities.size(); i++)
		{
			thisEntity = m_entities[i];

			switch (m_entities[i]->getComponent<AIComponent>().getAIType())
			{
			case aiTypes::ALLY:
				aiAlly();
				break;
			case aiTypes::DOG:
				aiDog();
				break;
			case aiTypes::PISTOL:
				aiPistol();
				break;
			case aiTypes::ENGINEER:
				aiEngineer();
				break;
			case aiTypes::SLIME:
				aiSlime();
				break;
			case aiTypes::JUGGERNAUT:
				aiJuggernaut();
				break;
			case aiTypes::TANK:
				aiTank();
				break;
			default:
				break;
			};
		}
	}

	/// <summary>
	/// Runs the Ally AI. 
	/// Currently a "placeholder" AI type.
	/// </summary>
	void aiAlly()
	{
		CD_Vector thisPosition(thisEntity->getComponent<PositionComponent>().GetPosition());

		CD_Vector targetPosition(400, 400);

		if (thisEntity->getComponent<AIComponent>().getTarget() != nullptr)
		{
			targetPosition = CD_Vector(thisEntity->getComponent<AIComponent>().getTarget()->getComponent<PositionComponent>().GetPosition());
		}

		if (path.empty() || pf.GetNearestCell(thisPosition) != pf.GetNearestCell(path.back()))
		{
			pathfind(thisPosition, targetPosition);
		}

		if (path.size() > 2)
		{
			CD_Vector nextCell = path[path.size() - 2];
			nextCell.x -= CELL_WIDTH / 4;
			nextCell.y -= CELL_HEIGHT / 4;
			seek(nextCell);
		}
		else
		{
			seek(targetPosition);
		}

		CD_Vector normal = targetPosition - thisEntity->getComponent<PositionComponent>().GetPosition();
		float rotation = atan2f(normal.x, -normal.y);
		rotation = rotation * 180 / M_PI;
		thisEntity->getComponent<PositionComponent>().setRotation(rotation);
		thisEntity->getComponent<SpriteComponent>().setRotation(rotation);
	}

	void aiDog() {}
	void aiPistol() {}
	void aiEngineer() {}
	void aiSlime() {}
	void aiJuggernaut() {}
	void aiTank() {}

	/// <summary>
	/// Manipulates movement component to move directly towards the given point.
	/// </summary>
	/// <param name="there"></param>
	void seek(CD_Vector there)
	{
		CD_Vector here = thisEntity->getComponent<PositionComponent>().GetPosition();
		if (there.x < here.x - 4)
		{
			thisEntity->getComponent<MovementComponent>().setLeft(true);
			thisEntity->getComponent<MovementComponent>().setRight(false);
		}
		else if (there.x > here.x + 4)
		{
			thisEntity->getComponent<MovementComponent>().setRight(true);
			thisEntity->getComponent<MovementComponent>().setLeft(false);
		}
		else
		{
			thisEntity->getComponent<MovementComponent>().setLeft(false);
			thisEntity->getComponent<MovementComponent>().setRight(false);
		}

		if (there.y < here.y - 4)
		{
			thisEntity->getComponent<MovementComponent>().setUp(true);
			thisEntity->getComponent<MovementComponent>().setDown(false);
		}
		else if (there.y > here.y + 4)
		{
			thisEntity->getComponent<MovementComponent>().setDown(true);
			thisEntity->getComponent<MovementComponent>().setUp(false);
		}
		else
		{
			thisEntity->getComponent<MovementComponent>().setDown(false);
			thisEntity->getComponent<MovementComponent>().setUp(false);
		}
	}

	void pathfind(CD_Vector here, CD_Vector there)
	{
		path = pf.AStar(pf.GetNearestCell(here), pf.GetNearestCell(there));
	}

	/// <summary>
	/// Add an entity to the list that this system acts on.
	/// Do not add entities that lack MovementComponents.
	/// </summary>
	/// <param name="ent">Entity to add.</param>
	void addEntity(Entity *ent)
	{
		m_entities.push_back(ent);
	}

	/// <summary>
	/// Receives a pointer for the bullet handler object
	/// for use in creating bullets
	/// </summary>
	/// <param name="bull">pointer to the bulletHandler instance</param>
	//void SetBulletHandler(BulletHandler *bull)
	//{
	//	m_BulletHandler = bull;
	//}

	bool getRemoved() override { return m_removed; };
	void setRemove(bool value) override { m_removed = value; };

private:
	Entity* thisEntity;
	//BulletHandler * m_BulletHandler = &BulletHandler();
	PathFinder pf;
	std::vector<CD_Vector> path;
};