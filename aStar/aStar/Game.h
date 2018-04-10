#pragma once

//#include<MenuComponentSystem.h>

#include "SDL.h"

#include "LevelLoader.h"
//#include "Client.h"
#include "AIBehaviour.h"
//#include "EntityFactory.h"
//#include "BulletHandler.h"

//#include "World.h"
#include "Collisions.h"
#include "InputSystem.h"
#include "MovementSystem.h"
#include "AISystem.h"
#include "WeaponComponent.h"
#include "AnimationComponent.h"
#include "SystemTemplate.h"
//#include "MenuSystemHandler.h"


#include "LevelManager.h"
#include "EnemyWaveManager.h"
#include "Music.h"



#include "Tile.h"
#include "GridTemplate.h"
#include <vector>
class Game
{
public:
	Game();
	~Game();
	void init(int width, int height);

	void Update();
	void Draw();
	void PollEvents();
	bool isRunning;
	int fps;
private:

	SDL_Renderer* renderer;
	SDL_Window* window;
	//Music * BackgroundMusic;
	//Uint8 you = 255;

	//PathFinder finder;
	////Client onlineClient;
	//Collisions * CollisionSystem;
	//Factory* factory;
	//LevelLoader loader;
	//SDL_Renderer* renderer;
	//SDL_Window* window;
	//EntityManager manager;
	//BulletHandler bulletHandler;
	//BulletHandler enemyBulletHandler;
	//Entity * Player;
	//Entity * Player2;
	//Entity * Enemy;
	//Entity * tempPortal1, * tempPortal2, * tempPortal3, * tempPortal4;
	//TextureHandler * TextureManager;
	//Entity * PlayerTest;
	//World* TestWorld;
	//int mouseX;
	//int mouseY;
	//InputSystem inputSys;
	//MovementSystem moveSys;
	//AISystem aiSys;
	//WeaponComponent testGun;
	//WeaponComponent testEnemyGun;
	//LevelManager* lvlManager;
	//MenuSystemHandler * m_menuHandler;
	//SceneManager* m_sceneManager;
	//

	//int m_gameState = GameStates::MainMenuState;
	//EnemyWaveManager * m_enemWaveMan;
	int smallTile;
	int medTile;
	int largeTile;

	//Tile smallTileGrid[30][30];
	//Tile medTileGrid[100][100];
	//Tile largeTileGrid[1000][1000];
	std::vector<std::vector<Tile>> smallTileGrid;
	std::vector<std::vector<Tile>> medTileGrid;
	std::vector<std::vector<Tile>> largeTileGrid;
};


