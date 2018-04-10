////Author: John McGrath
//#pragma once
//#include "EntityFactory.h"
//#include "ComponentList.h"
//#include "AISystem.h"
//#include "Collisions.h"
//#include "MovementSystem.h"
//
//#define MAX_NUM_ENEMIES 7
//
//class EnemyWaveManager
//{
//public:
//
//	EnemyWaveManager();
//
//	//function to initalise the spawner
//	void init(EntityManager * man, TextureHandler* handler, Entity * target, Factory * factory,
//		AISystem * aisys, MovementSystem * movesys, Collisions * collsys);
//
//	//Update loop
//	void update();
//
//	//Spawns the enemies
//	void spawnEnemies(int num);
//
//	//Returns the bullet handler
//	BulletHandler * getBullets() { return m_enemyBullets; }
//private:
//	//Values for waves
//	int m_numOfEnem = 3;
//	int m_wave = 0;
//
//	//Pointers to the systems
//	EntityManager * m_manager;
//	TextureHandler * m_handler;
//	Entity * m_target;
//	Factory * m_factory;
//	AISystem * m_aisys;
//	MovementSystem * m_movesys;
//	Collisions * m_collsys;
//	Entity * protoEnemy;
//	BulletHandler * m_enemyBullets;
//
//	//Timers for waves
//	Uint32 m_waveTimer = 0;
//	Uint32 m_previousTime = 0;
//
//	//Time between waves (ms)
//	Uint32 m_timeBetwWaves = 7000;
//};
