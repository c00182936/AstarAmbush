#include "Game.h"



Game::Game()
{
}


Game::~Game()
{
}

void Game::init(int width, int height)
{
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
	for (int i = 0; i < smallTile; i++)
	{
		for (int o = 0; o < smallTile; o++)
		{
			
		}
	}
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
}

void Game::Update()
{
}

void Game::Draw()
{
	SDL_SetRenderDrawColor(renderer, 240, 240, 240, 255);
	SDL_RenderClear(renderer);
}

void Game::PollEvents()
{
}
