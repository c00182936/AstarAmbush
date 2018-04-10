#include "Game.h"


//Game::Game() : loader(std::string("GeneralGameData.json"))
//{
//	//TextureManager = TextureHandler::Instance();
//
//	//if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 4, 4096) < 0)
//	//{
//	//	cout << "Error : " << Mix_GetError() << endl;
//	//}
//}

Game::Game()
{
}

Game::~Game()
{
	smallTileGrid.clear();
}


void Game::init(int width, int height)
{
	smallTile = 30;
	medTile = 100;
	largeTile = 1000;
	smallTileGrid.reserve(smallTile);
	std::vector<Tile> tempTileVec;
	Tile tempTile;
	tempTileVec.reserve(30);
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		window = SDL_CreateWindow("ARGO_D", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);
		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer)
		{
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		}
		isRunning = true;
	}
	float tileW, tileH;
	tileW = width / smallTile;
	tileH = height / smallTile;
	int boolGridX=0, boolGridY=0, boolGridCountX=0, boolGridCountY=0;
	for (int i = 0; i < smallTile; i++)
	{
		for (int o = 0; o < smallTile; o++)
		{

				if (boolGridCountX>2)
				{
					boolGridCountX = 0;
					boolGridX++;
				}
				if (boolGridX > 9)
				{
					boolGridX = 0;
				}
				if (boolGridCountY > 2)
				{
						boolGridCountY = 0;
						boolGridY++;
				}
				if (boolGridY >= 9)
				{
					boolGridY = 0;
				}
					//smallTileGrid[i][o] = Tile(i, o, tileW, tileH, lilgrid[w][h]);
					tempTile = Tile(i, o, tileW, tileH, lilgrid[boolGridX][boolGridY]);
					tempTileVec.push_back(tempTile);
		boolGridCountX++;

		}
		boolGridCountY++;
		smallTileGrid.push_back(tempTileVec);
		tempTileVec.clear();
	}
	tempTileVec.clear();
	for (int i = 0; i < medTile; i++)
	{
		for (int o = 0; o < medTile; o++)
		{

		}
	}
	for (int i = 0; i < largeTile; i++)
	{
		for (int o = 0; o < largeTile; o++)
		{

		}
	}
	//loader.LoadAll();

	//factory = new EntityFactory();
	//CollisionSystem = new Collisions;

	//BackgroundMusic = new Music;

	//manager = EntityManager();
	//if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	//{
	//	window = SDL_CreateWindow("ARGO_D", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);
	//	renderer = SDL_CreateRenderer(window, -1, 0);
	//	if (renderer)
	//	{
	//		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	//	}
	//	isRunning = true;
	//}

	//for (map<string, string>::iterator iter = GameData::m_sprites.begin(); iter != GameData::m_sprites.end(); iter++)
	//{
	//	TextureManager->addTexture(iter->first, iter->second, renderer);
	//}

	//bulletHandler = BulletHandler();
	//enemyBulletHandler = BulletHandler();
	//inputSys = InputSystem();
	//moveSys = MovementSystem();
	//aiSys = AISystem();
	//m_sceneManager = new SceneManager();

	//TestWorld = new World;
	//TestWorld->init(0);


	//Player = &manager.addEntity(factory->CreatePlayerEntity(CD_Vector(500,500), "characterSpecOps",TextureManager, manager));
	//Player->addComponent<WeaponComponent>();
	//Player->addComponent<AnimationComponent>();
	//Player->getComponent<WeaponComponent>().setGunValues(100, 40, 25, 300, 600, 0, true);


	//lvlManager = new LevelManager();
	//lvlManager->setWorld(TestWorld);
	//Player = factory->CreatePlayerEntity(CD_Vector(500, 500), "characterSpecOps", TextureManager, manager);
	//Player2 = factory->CreatePlayerEntity(CD_Vector(400, 300), "characterSpecOps", TextureManager, manager);
	//CollisionSystem->addEntity(Player);

	//inputSys.SetBulletHandler(&bulletHandler);
	//moveSys.addEntity(Player);
	//moveSys.addEntity(Player2);

	//onlineClient.Init("Yuri", "149.153.106.167");
	//onlineClient.people[0].active;
	//onlineClient.people[1].active;
	//onlineClient.InitPlayer(Player, Player2);

	//Enemy creation.

	/*auto& enemy(manager.CreateEntity());
	enemy.addComponent<PositionComponent>(320, 480);
	enemy.addComponent<RenderComponent>();
	enemy.addComponent<AIComponent>(AISystem::aiTypes::ALLY);
	enemy.getComponent<AIComponent>().setTarget(Player);
	enemy.addComponent<MovementComponent>(0.1f, 0.8f);
	enemy.addComponent<SpriteComponent>(TextureManager->getTexture("characterSpecOps"), SDL_Rect{ 0, 0, 136, 136 }, 32.0f, 32.0f);
	enemy.addComponent<WeaponComponent>();
	enemy.getComponent<WeaponComponent>().setGunValues(1000, 50, 30, 500, 1000, 0, true);
	enemy.addComponent<StatComponent>(100, 25, 50);
	enemy.addGroup(Groups::EnemyGroup);
	enemy.getComponent<PositionComponent>().setRotation(180);

	Enemy = &enemy;
	aiSys.addEntity(Enemy);
	aiSys.SetBulletHandler(&enemyBulletHandler);
	aiSys.InitializePathfinder();
	moveSys.addEntity(Enemy);
	CollisionSystem->addEntity(Enemy);

	m_menuHandler = new MenuSystemHandler(TextureManager, renderer,&inputSys);
	m_menuHandler->init(TextureManager);


	float tempPortalX=TestWorld->getDimentions().w;
	tempPortalX /= 2;
	float portalRad = tempPortalX;
	tempPortalX *= 11;

	tempPortal1 = &manager.CreateEntity();
	tempPortal1->addComponent<PositionComponent>(0, 0);
	tempPortal1->addComponent<RenderComponent>();
	tempPortal1->getComponent<PositionComponent>().setCircleDimensions(CD_Vector{ tempPortalX-portalRad, portalRad }, portalRad*2, 0);
	tempPortal1->addComponent<SpriteComponent>(TextureManager->getTexture("Portal"), SDL_Rect{ 0,0,800,800 }, 128, 128);
	tempPortal1->addGroup(Groups::PortalGroup);
	lvlManager->addEntity(tempPortal1);

	tempPortal2 = &manager.CreateEntity();
	tempPortal2->addComponent<PositionComponent>(0,0);
	tempPortal2->addComponent<RenderComponent>();
	tempPortal2->getComponent<PositionComponent>().setCircleDimensions(CD_Vector{ tempPortalX*2 - portalRad*3,tempPortalX - portalRad }, portalRad*2, 0);
	tempPortal2->addComponent<SpriteComponent>(TextureManager->getTexture("Portal"), SDL_Rect{ 0,0,800,800 }, 128, 128);
	tempPortal2->addGroup(Groups::PortalGroup);
	lvlManager->addEntity(tempPortal2);

	tempPortal3 = &manager.CreateEntity();
	tempPortal3->addComponent<PositionComponent>(0,0);
	tempPortal3->addComponent<RenderComponent>();
	tempPortal3->getComponent<PositionComponent>().setCircleDimensions(CD_Vector{ portalRad,tempPortalX - portalRad }, portalRad*2, 0);
	tempPortal3->addComponent<SpriteComponent>(TextureManager->getTexture("Portal"), SDL_Rect{ 0,0,800,800 }, 128, 128);
	tempPortal3->addGroup(Groups::PortalGroup);
	lvlManager->addEntity(tempPortal3);

	tempPortal4 = &manager.CreateEntity();
	tempPortal4->addComponent<PositionComponent>(0, 0);
	tempPortal4->addComponent<RenderComponent>();
	tempPortal4->getComponent<PositionComponent>().setCircleDimensions(CD_Vector{ tempPortalX - portalRad,(tempPortalX*2) - portalRad*3 }, portalRad*2, 0);
	tempPortal4->addComponent<SpriteComponent>(TextureManager->getTexture("Portal"), SDL_Rect{ 0,0,800,800 }, 128, 128);
	tempPortal4->addGroup(Groups::PortalGroup);
	lvlManager->addEntity(tempPortal4);

	m_enemWaveMan = new EnemyWaveManager();
	m_enemWaveMan->init(&manager, TextureManager, Player, factory, &aiSys, &moveSys, CollisionSystem);*/
}

void Game::Update()
{
//	BackgroundMusic->Update();
	// Testing
	int DoOnce = 0;
	// Testing

	//If the gameplay is occuring
	//if (*m_sceneManager->getCurrentScene() == GameStates::GameState)
	//{
		//if (DoOnce == 0)
		//{
		//	DoOnce++;
		//	inputSys.addEntity(Player);
		//}

		//aiSys.update();
		//SDL_GetMouseState(&mouseX, &mouseY);
		//manager.update();
		//inputSys.update();
		//moveSys.update();
		//CollisionSystem->update();
		//m_enemWaveMan->update();

		//int x, y = 0;
		//if (Player != nullptr)
		//{
		//	x = Player->getComponent<PositionComponent>().GetXPosition() + (Player->getComponent<SpriteComponent>().getScreenCoords().w / 2);
		//	y = Player->getComponent<PositionComponent>().GetYPosition() + (Player->getComponent<SpriteComponent>().getScreenCoords().h / 2);
		//	bulletHandler.UpdateWithComponent(SDL_Point{ x, y }, SDL_Point{ mouseX,mouseY }, Player->getComponent<WeaponComponent>());
		//}

		//if (Enemy != nullptr)
		//{
		//	x = Enemy->getComponent<PositionComponent>().GetPosition().x + (Player->getComponent<SpriteComponent>().getScreenCoords().w / 2);
		//	y = Enemy->getComponent<PositionComponent>().GetPosition().y + (Player->getComponent<SpriteComponent>().getScreenCoords().h / 2);
		//	enemyBulletHandler.UpdateWithComponent(SDL_Point{ x, y },
		//		SDL_Point{ (int)Player->getComponent<PositionComponent>().GetPosition().x, (int)Player->getComponent<PositionComponent>().GetPosition().y },
		//		Enemy->getComponent<WeaponComponent>());
		//}

		//CollisionSystem->WallCollision(TestWorld->getWalls());

		//lvlManager->checkCollision(Player);
		//for (int i = 0; i < bulletHandler.GetBullets()->size(); i++)
		//{
		//	if (bulletHandler.GetBullets()->at(i)->m_velocity.x != 0 && bulletHandler.GetBullets()->at(i)->m_velocity.y != 0)
		//	{
		//		SDL_Rect bullet = bulletHandler.GetBullets()->at(i)->m_dst;
		//		// Wall Collision
		//		if (Collisions::BulletWall(bullet, TestWorld->getWalls()))
		//		{
		//			bulletHandler.GetBullets()->at(i)->Reset();
		//		}

		//		CollisionSystem->BulletCollision(bulletHandler.GetBullets()->at(i), "PlayerBullet");
		//	}
		//}

		//for (int i = 0; i < enemyBulletHandler.GetBullets()->size(); i++)
		//{
		//	if (enemyBulletHandler.GetBullets()->at(i)->m_velocity.x != 0 && enemyBulletHandler.GetBullets()->at(i)->m_velocity.y != 0)
		//	{
		//		SDL_Rect bullet = enemyBulletHandler.GetBullets()->at(i)->m_dst;

		//		if (Collisions::BulletWall(bullet, TestWorld->getWalls()))
		//		{
		//			enemyBulletHandler.GetBullets()->at(i)->Reset();
		//		}

		//		CollisionSystem->BulletCollision(enemyBulletHandler.GetBullets()->at(i), "EnemyBullet");
		//	}
		//}

		//// Removes enemy
		//if (aiSys.getRemoved() && moveSys.getRemoved() && CollisionSystem->getRemoved())
		//{
		//	manager.refresh();
		//	Enemy = nullptr;
		//	aiSys.setRemove(false);
		//	moveSys.setRemove(false);
		//	CollisionSystem->setRemove(false);
		//}

		//lvlManager->checkCollision(Player);

	//}

	/*if (*m_sceneManager->getCurrentScene() == GameStates::MultiPlayerState)
	{
		aiSys.update();
		SDL_GetMouseState(&mouseX, &mouseY);
		manager.update();
		inputSys.update();
		moveSys.update();
		CollisionSystem->update();
		m_enemWaveMan->update();

		int x, y = 0;
		if (Player != nullptr)
		{
			x = Player->getComponent<PositionComponent>().GetXPosition() + (Player->getComponent<SpriteComponent>().getScreenCoords().w / 2);
			y = Player->getComponent<PositionComponent>().GetYPosition() + (Player->getComponent<SpriteComponent>().getScreenCoords().h / 2);
			bulletHandler.UpdateWithComponent(SDL_Point{ x, y }, SDL_Point{ mouseX,mouseY }, Player->getComponent<WeaponComponent>());
		}

		if (Enemy != nullptr)
		{
		if (Player != nullptr)
		{
			x = Enemy->getComponent<PositionComponent>().GetPosition().x + (Player->getComponent<SpriteComponent>().getScreenCoords().w / 2);
			y = Enemy->getComponent<PositionComponent>().GetPosition().y + (Player->getComponent<SpriteComponent>().getScreenCoords().h / 2);
			enemyBulletHandler.UpdateWithComponent(SDL_Point{ x, y },
				SDL_Point{ (int)Player->getComponent<PositionComponent>().GetPosition().x, (int)Player->getComponent<PositionComponent>().GetPosition().y },
				Enemy->getComponent<WeaponComponent>());
		}
	}*/

		//onlineClient.Update();
		//When a player ID is received, add the appropriate player to the input component to give this user control.
		//if (onlineClient.GetPlayerNumber() != you)
		//{
		//	you = onlineClient.GetPlayerNumber();
		//	if (you == 0)
		//	{
		//		inputSys.addEntity(Player);
		//	}
		//	if (you == 1)
		//	{
		//		inputSys.addEntity(Player2);
		//	}
		//}

	//	CollisionSystem->WallCollision(TestWorld->getWalls());

	//	lvlManager->checkCollision(Player);
	//	for (int i = 0; i < bulletHandler.GetBullets()->size(); i++)
	//	{
	//		if (bulletHandler.GetBullets()->at(i)->m_velocity.x != 0 && bulletHandler.GetBullets()->at(i)->m_velocity.y != 0)
	//		{
	//			SDL_Rect bullet = bulletHandler.GetBullets()->at(i)->m_dst;
	//			// Wall Collision
	//			if (Collisions::BulletWall(bullet, TestWorld->getWalls()))
	//			{
	//				bulletHandler.GetBullets()->at(i)->Reset();
	//			}

	//			CollisionSystem->BulletCollision(bulletHandler.GetBullets()->at(i), "PlayerBullet");
	//		}
	//	}

	//	for (int i = 0; i < enemyBulletHandler.GetBullets()->size(); i++)
	//	{
	//		if (enemyBulletHandler.GetBullets()->at(i)->m_velocity.x != 0 && enemyBulletHandler.GetBullets()->at(i)->m_velocity.y != 0)
	//		{
	//			SDL_Rect bullet = enemyBulletHandler.GetBullets()->at(i)->m_dst;

	//			if (Collisions::BulletWall(bullet, TestWorld->getWalls()))
	//			{
	//				enemyBulletHandler.GetBullets()->at(i)->Reset();
	//			}

	//			CollisionSystem->BulletCollision(enemyBulletHandler.GetBullets()->at(i), "EnemyBullet");
	//		}
	//	}

	//	// Removes enemy
	//	if (aiSys.getRemoved() && moveSys.getRemoved() && CollisionSystem->getRemoved())
	//	{
	//		manager.refresh();
	//		Enemy = nullptr;
	//		aiSys.setRemove(false);
	//	moveSys.setRemove(false);
	//	CollisionSystem->setRemove(false);
	//}

	//if (inputSys.getRemoved() && moveSys.getRemoved() && CollisionSystem->getRemoved())
	//{
	//	manager.refresh();
	//	Player = nullptr;
	//	inputSys.setRemove(false);
	//		moveSys.setRemove(false);
	//		CollisionSystem->setRemove(false);
	//	}

	//	lvlManager->checkCollision(Player);
	//}

	////If the game isn't in gameplay
	//if (*m_sceneManager->getCurrentScene() != GameStates::GameState || *m_sceneManager->getCurrentScene() != GameStates::MultiPlayerState)
	//{
	//	inputSys.checkKeyPresses();
	//	PollEvents();
	//}
}

void Game::Draw()
{
	SDL_SetRenderDrawColor(renderer, 10, 10, 10, 255);
	SDL_RenderClear(renderer);

	//Checks if the menu should be drawing
	/*if (*m_sceneManager->getCurrentScene() != GameStates::MultiPlayerState)
	{
		m_menuHandler->render(m_sceneManager->getCurrentScene());
	}*/


	//if (*m_sceneManager->getCurrentScene() == GameStates::GameState || *m_sceneManager->getCurrentScene() == GameStates::MultiPlayerState)
	//{
	//	TestWorld->RenderWorld(renderer);

	//	//Bullets
	//	bulletHandler.Render(renderer);
	//	enemyBulletHandler.Render(renderer);

	//	//Player
	//	manager.Draw(renderer);
	//	lvlManager->draw(renderer);
	//}

	//else
	//{
	//	m_menuHandler->render(m_sceneManager->getCurrentScene());
	//}
	for (int i = 0; i < smallTile; i++)
	{
		for (int o = 0; o < smallTile; o++)
		{
			smallTileGrid[i][o].Render(renderer);
		}
	}



	SDL_RenderPresent(renderer);

}

void Game::PollEvents()
{
	//SDL_Event e;

	//SDL_PollEvent(&e);

	//m_menuHandler->update(m_sceneManager->getCurrentScene(), &isRunning, &e);
}
