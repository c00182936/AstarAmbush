//Author: John McGrath
#include "EnemyWaveManager.h"
#include <time.h>

EnemyWaveManager::EnemyWaveManager()
{

}
/// <summary>
/// Initialise the spawner
/// </summary>
/// <param name="man">Entity manager</param>
/// <param name="handler">Pointer to texture handler</param>
/// <param name="target">Pointer to entity they wish to shoot</param>
/// <param name="factory">Pointer to the factory</param>
/// <param name="aisys">Pointer to the AI System</param>
/// <param name="movesys">Pointer to the movement system</param>
///  <param name="collsys">Pointer to the collision system</param>
void EnemyWaveManager::init(EntityManager * man, TextureHandler* handler, Entity * target, Factory * factory,
	AISystem * aisys, MovementSystem * movesys, Collisions * collsys)
{
	srand(time(NULL));
	m_manager = man;
	m_handler = handler;
	m_target = target;
	m_factory = factory;
	m_aisys = aisys;
	m_movesys = movesys;
	m_collsys = collsys;

	m_enemyBullets = new BulletHandler();

	m_previousTime = SDL_GetTicks();

	spawnEnemies(m_numOfEnem);
}

/// <summary>
/// Function to spawn the enemies
/// </summary>
/// <param name="num">Number of enemies to spawn</param>
void EnemyWaveManager::spawnEnemies(int num)
{
	CD_Vector pos;
	//If the amount of enemies is less than the max
	if (m_manager->getGroup(Groups::EnemyGroup).size() < MAX_NUM_ENEMIES)
	{
		for (int i = 0; i < num; i++)
		{
			{
				//spawn in a random position
				pos.x = rand() % 500 + 100;
				pos.y = rand() % 500 + 100;
				Entity * e = m_factory->CreatePistolEntity(pos, m_handler, m_manager, m_target);
				m_aisys->addEntity(e);
				m_movesys->addEntity(e);
				m_collsys->addEntity(e);
			}
		}
	}
}

/// <summary>
/// Update loop
/// </summary>
void EnemyWaveManager::update()
{
	m_waveTimer = SDL_GetTicks();
	if (m_waveTimer > m_previousTime + m_timeBetwWaves)
	{
		m_previousTime = SDL_GetTicks();
		spawnEnemies(m_numOfEnem);
	}
}