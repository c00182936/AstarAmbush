#pragma once
#include <iostream>
#include "ECS.h"

/// <class>StatComponent</class>
/// <summary>
/// This component is to keep track
/// of an entities stats. These stats
/// include health, power and defence.
/// </summary>
/// <author>Jack Keogh</author>

using namespace std;

class StatComponent : public Component
{
private:
	int m_health;
	int m_defense;
	int m_power;

public:
	/// <summary>
	/// Default constructor with overloaded values.
	/// </summary>
	/// <param name="health">int define the health value.</param>
	/// <param name="defense">int define the defense value.</param>
	/// <param name="power">int define the power value.</param>
	StatComponent(int health = 10, int defense = 0, int power = 0) :
		m_health(health),
		m_defense(defense),
		m_power(power)
	{
	};

	void update() override
	{
		if (m_health <= 0)
		{
			m_owner->destroy();
			//m_owner = nullptr;
		}
	}

	/// <summary>
	/// Getter functions
	/// </summary>
	int getHealth() { return m_health; };
	int getPower() { return m_power; };
	int getDefense() { return m_defense; };

	/// <summary>
	/// setter functions
	/// </summary>
	void setHealth(int value) { m_health = value; };
	void setPower(int value) { m_power = value; };
	void setDefense(int value) { m_defense = value; };
};