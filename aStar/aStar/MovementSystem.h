#pragma once
#include "SystemTemplate.h"

class MovementSystem : System
{
public:
	/// <summary>
	/// Constructor function.
	/// </summary>
	MovementSystem()
	{
		m_removed = false;
	}

	/// <summary>
	/// Loops through all attached entities and commands them to move.
	/// Uses data from the MovementComponent to make the current entity move. 
	/// </summary>
	void update() override
	{
		refresh();

		for (int i = 0; i < m_entities.size(); i++)
		{
			//This one line is just here to shorten pretty much every other line in this function.
			MovementComponent m = m_entities[i]->getComponent<MovementComponent>();

			//Handles vertical movement. If moving up or down, increase velocity; otherwise, slow to a stop.
			//Also ensures velocity does not exceed maximum possible.
			//This does not affect horizontal movement; you can move on both axes at the same time.
			if (m.isMovingUp())
			{
				m.setVelocity(CD_Vector(m.getVelocity().x, m.getVelocity().y - m.getAcceleration()));
				if (m.getVelocity().y < -m.getMaxVelocity())
				{
					m.setVelocity(CD_Vector(m.getVelocity().x, -m.getMaxVelocity()));
				}
			}
			else if (m.isMovingDown())
			{
				m.setVelocity(CD_Vector(m.getVelocity().x, m.getVelocity().y + m.getAcceleration()));
				if (m.getVelocity().y > m.getMaxVelocity())
				{
					m.setVelocity(CD_Vector(m.getVelocity().x, m.getMaxVelocity()));
				}
			}
			else
			{
				if (m.getVelocity().y < m.getMinVelocity())
				{
					m.setVelocity(CD_Vector(m.getVelocity().x, 0));
				}
				else
				{
					m.setVelocity(CD_Vector(m.getVelocity().x, m.getVelocity().y * m.getDeceleration()));
				}
			}

			//Handles horizontal movement. If moving left or right, increase velocity; otherwise, slow to a stop.
			//Also ensures velocity does not exceed maximum possible.
			//This does not affect vertical movement; you can move on both axes at the same time.
			if (m.isMovingLeft())
			{
				m.setVelocity(CD_Vector(m.getVelocity().x - m.getAcceleration(), m.getVelocity().y));
				if (m.getVelocity().x < m.getMaxVelocity())
				{
					m.setVelocity(CD_Vector(-m.getMaxVelocity(), m.getVelocity().y));
				}
			}
			else if (m.isMovingRight())
			{
				m.setVelocity(CD_Vector(m.getVelocity().x + m.getAcceleration(), m.getVelocity().y));
				if (m.getVelocity().x > m.getMaxVelocity())
				{
					m.setVelocity(CD_Vector(m.getMaxVelocity(), m.getVelocity().y));
				}
			}
			else
			{
				if (m.getVelocity().x < m.getMinVelocity())
				{
					m.setVelocity(CD_Vector(0, m.getVelocity().y));
				}
				else
				{
					m.setVelocity(CD_Vector(m.getVelocity().x * m.getDeceleration(), m.getVelocity().y));
				}
			}
		}
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

	bool getRemoved() override { return m_removed; };
	void setRemove(bool value) override { m_removed = value; };
};