#pragma once
#include "ECS.h"
#include "PositionComponent.h"
#include "SDL.h"

class MovementComponent : public Component
{
public:
	/// <summary>
	/// Default constructor for MovementComponent
	/// </summary>
	MovementComponent() {};

	/// <summary>
	/// Default destructor for MovementComponent
	/// </summary>
	~MovementComponent() {};

	/// <summary>
	/// Overload constructor for Movement Component
	/// </summary>
	/// <param name="acceleration">float variable to select change rate of velocity</param>
	/// <param name="maxVelocity">float variable to determine the max velocity</param>
	MovementComponent(float acceleration = 0.5f, float maxVelocity = 5.0f)
	{
		m_velocity = CD_Vector(0, 0);
		m_acceleration = acceleration;
		m_maxVelocity = maxVelocity;
	}

	/// <summary>
	/// Default initializer. Can I get away with not using this?
	/// </summary>
	void init() override
	{
		m_velocity = CD_Vector(0, 0);
		pos = &m_owner->getComponent<PositionComponent>();
	}

	/// <summary>
	/// Moves the entity based on the current velocity.
	/// </summary>
	void update()
	{
		move();

		pos->setPosition(CD_Vector(pos->GetPosition() + m_velocity));
	}

	void move()
	{
		/// <summary>
		/// There should not be logic in a .h file. Use a .cpp for logic.
		/// </summary>
		if (movingUp)
		{
			m_velocity.y -= m_acceleration;
			if (m_velocity.y < -m_maxVelocity)
			{
				m_velocity.y = -m_maxVelocity;
			}
		}
		else if (movingDown)
		{
			m_velocity.y += m_acceleration;
			if (m_velocity.y > m_maxVelocity)
			{
				m_velocity.y = m_maxVelocity;
			}
		}
		else
		{
			if (m_velocity.y < m_minVelocity)
			{
				m_velocity.y = 0;
			}
			else
			{
				m_velocity.y *= m_deceleration;
			}
		}

		if (movingLeft)
		{
			m_velocity.x -= m_acceleration;
			if (m_velocity.x < m_maxVelocity)
			{
				m_velocity.x = -m_maxVelocity;
			}
		}
		else if (movingRight)
		{
			m_velocity.x += m_acceleration;
			if (m_velocity.x > m_maxVelocity)
			{
				m_velocity.x = m_maxVelocity;
			}
		}
		else
		{
			if (m_velocity.x < m_minVelocity)
			{
				m_velocity.x = 0;
			}
			else
			{
				m_velocity.x *= m_deceleration;
			}
		}
	}

	/// <summary>
	/// Movement functions only add acceleration and do not directly move the entity.
	/// Velocity is increased in the given direction by acceleration, and then limited by the maximum velocity.
	/// Almost certainly need to change these later once things come together and add deceleration.
	/// </summary>
	void setUp(bool moving)
	{
		movingUp = moving;
	}

	void setDown(bool moving)
	{
		movingDown = moving;
	}

	void setLeft(bool moving)
	{
		movingLeft = moving;
	}

	void setRight(bool moving)
	{
		movingRight = moving;
	}

	/// <summary>
	/// Change base acceleration.
	/// </summary>
	/// <param name="acceleration">New acceleration value.</param>
	void setAcceleration(float acceleration)
	{ m_acceleration = acceleration; }

	/// <summary>
	/// Returns maximum possible velocity in any direction.
	/// </summary>
	/// <param name="maxVelocity">New maximum speed.</param>
	void setMaxVelocity(float maxVelocity)
	{ m_maxVelocity = maxVelocity; }

	/// <summary>
	/// allows the setting of the velocity value.
	/// </summary>
	/// <param name="value">the new velocity value</param>
	void setVelocity(CD_Vector value)
	{
		if (value.x > m_maxVelocity)
		{
			value.x = m_maxVelocity;
		}

		if (value.x < -m_maxVelocity)
		{
			value.x = -m_maxVelocity;
		}

		if (value.y > m_maxVelocity)
		{
			value.y = m_maxVelocity;
		}

		if (value.y < -m_maxVelocity)
		{
			value.y = -m_maxVelocity;
		}

		m_velocity = value;
	}

	/// <summary>
	/// Returns current X/Y velocity.
	/// </summary>
	/// <returns></returns>
	CD_Vector getVelocity()
	{ return m_velocity; }

	/// <summary>
	/// Returns base acceleration value.
	/// </summary>
	/// <returns></returns>
	float getAcceleration()
	{ return m_acceleration; }

	/// <summary>
	/// Returns maximum possible velocity in any direction.
	/// </summary>
	/// <returns></returns>
	float getMaxVelocity()
	{ return m_maxVelocity; }

	/// <summary>
	/// Returns whether or not the entity is moving upward.
	/// </summary>
	/// <returns></returns>
	bool isMovingUp()
	{ return movingUp; }

	/// <summary>
	/// Returns whether or not the entity is moving downward.
	/// </summary>
	/// <returns></returns>
	bool isMovingDown()
	{ return movingDown; }

	/// <summary>
	/// Returns whether or not the entity is moving leftward.
	/// </summary>
	/// <returns></returns>
	bool isMovingLeft()
	{ return movingLeft; }

	/// <summary>
	/// Returns whether or not the entity is moving rightward.
	/// </summary>
	/// <returns></returns>
	bool isMovingRight()
	{ return movingRight; }

	/// <summary>
	/// Returns rate at which the entity slows down when movement input stops.
	/// </summary>
	/// <returns></returns>
	float getDeceleration()
	{
		return m_deceleration;
	}

	/// <summary>
	/// Returns threshold at which the entity's velocity is nullified.
	/// If the entity is moving slower than this value, it might as well not move.
	/// </summary>
	/// <returns></returns>
	float getMinVelocity()
	{ return m_minVelocity; }

private:
	PositionComponent* pos; //Pointer that allows reading of current position.
	CD_Vector m_velocity; //Speed of movement and direction. 

	float m_acceleration; //Rate of change in velocity. 
	float m_maxVelocity; //Maximum velocity in either X/Y direction.
	float m_deceleration = 0.8f; //Rate at which velocity decreases when input ends. Higher value means slower deceleration.
	float m_minVelocity = 0.2f; //When below this value, velocity is set to 0.

	float m_orientation; //Angle the object is facing, in radians. 0 is up/north. Not needed?

	bool movingUp = false;
	bool movingDown = false;
	bool movingLeft = false;
	bool movingRight = false;
};