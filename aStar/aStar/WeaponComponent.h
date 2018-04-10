#pragma once
#include "ECS.h"
#include "SDL.h"
//Author: John McGrath
class WeaponComponent : public Component
{
public:
	/// <summary>
	/// Initialisation function for the weapon componet
	/// </summary>
	void init() override
	{
		m_timeBetweenShot = 0;

		m_maxDamage = 0;
		m_minDamage = 0;

		m_maxRange = 0;
		m_minRange = 0;

		m_angleDeviation = 0;
	}

	/// <summary>
	/// Setting up the values of each weapon
	/// </summary>
	/// <param name="time">The amount of time between shots (ms)</param>
	/// <param name="maxD">The maximum amount of damage per shot</param>
	/// <param name="minD">The minimum amount of damage per shot</param>
	/// <param name="maxR">The range before damage drops</param>
	/// <param name="minR">The range at which bullets stop to drop off</param>
	/// <param name="dev">The amount of deviation the bullet will have</param>
	void setGunValues(float time, float maxD, float minD, float maxR, float minR, float dev, bool pyrOrEnem)
	{
		m_timeBetweenShot = time;

		m_maxDamage = maxD;
		m_minDamage = minD;

		m_maxRange = maxR;
		m_minRange = minR;

		m_angleDeviation = dev;

		m_playerOrEnemy = pyrOrEnem;
	}

	/// <summary>
	/// Setter method for the time between shots
	/// </summary>
	/// <param name="t">The new value for m_timeBetweenShot</param>
	void setTimeBetweenShots(float t) { m_timeBetweenShot = t; }

	/// <summary>
	/// Setter method for the max damage
	/// </summary>
	/// <param name="maxDam">The new value for m_maxDamage</param>
	void setMaxDamage(float maxDam) { m_maxDamage = maxDam; }

	/// <summary>
	/// Setter method for the min damage
	/// </summary>
	/// <param name="minDam">The new value for m_minDamage</param>
	void setMinDamage(float minDam) { m_minDamage = minDam; }

	/// <summary>
	/// Setter method for the max range
	/// </summary>
	/// <param name="maxRang">The new value for m_maxRange</param>
	void setMaxRange(float maxRang) { m_maxRange = maxRang; }

	/// <summary>
	/// Setter method for the min range
	/// </summary>
	/// <param name="minRang">The new value for m_minRange</param>
	void setMinRange(float minRang) { m_minRange = minRang; }

	/// <summary>
	/// Setter method for the angle of deviation from the barrel
	/// </summary>
	/// <param name="angle">The new value for m_angleDeviation</param>
	void setAngleDeviation(float angle) { m_angleDeviation = angle; }

	/// <summary>
	/// Setter method for the time to reload
	/// </summary>
	/// <param name="time">The new value for m_timeToReload</param>
	void setReloadTime(float time) { m_timeToReload = time; }

	/// <summary>
	/// Setter method for the magazine size
	/// </summary>
	/// <param name="mag">The new value for m_magSize</param>
	void setMagSize(int mag) { m_magSize = mag; }

	/// <summary>
	/// Setter method for player or enemy bullet
	/// </summary>
	/// <param name="pyrOrEnem">Was the bullet fired by a friendly</param>
	void setIsPlayerOrEnemy(bool pyrOrEnem) { m_playerOrEnemy = pyrOrEnem; }

	/// <summary>
	/// Getter method for the time between shots
	/// </summary>
	float getTimeBetweenShots() { return m_timeBetweenShot; }

	/// <summary>
	/// Getter method for the max damage
	/// </summary>
	int getMaxDamage() { return m_maxDamage; }

	/// <summary>
	/// Getter method for the min damage
	/// </summary>
	int getMinDamage() { return m_minDamage; }

	/// <summary>
	/// Getter method for the max range
	/// </summary>
	int getMaxRange() { return m_maxRange; }

	/// <summary>
	/// Getter method for the min range
	/// </summary>
	int getMinRange() { return m_minRange; }

	/// <summary>
	/// Getter method for the angle of deviation between shots
	/// </summary>
	float getAngleDeviation() { return m_angleDeviation; }

	/// <summary>
	/// Getter method for the time to reload
	/// </summary>
	float getReloadTime() { return m_timeToReload; }

	/// <summary>
	/// Getter method for the magazine size
	/// </summary>
	int getMagSize() { return m_magSize; }

	/// <summary>
	/// Getter method for player or enemy bullet
	/// </summary>
	bool getIsPlayerOrEnemy() { return m_playerOrEnemy; }

private:
	//The amount of time between shots
	float m_timeBetweenShot = 0;

	//The damage of the weapon before losing damage over range
	int m_maxDamage = 0;
	//The minimum value can damage can reach
	int m_minDamage = 0;

	//The range at which a bullet will between losing damage
	float m_maxRange = 0;
	//The range at which a bullet will stop losing damage
	float m_minRange = 0;

	//The deviation at which a bullet may spawn from the barrel
	float m_angleDeviation = 0;

	//The amount of shots that can be fired before reloading
	int m_magSize = 0;
	//The amount of time the player must wait for a reload to complete
	float m_timeToReload = 0;

	//Whether a friendly or enemy bullet
	bool m_playerOrEnemy = true;
};
