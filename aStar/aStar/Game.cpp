#include "Game.h"
#include "SDL2-2.0.7\include\SDL.h"


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
	float tileW, tileH;
	tileW = width / smallTile;
	tileH = height / smallTile;

	for (int i = 0; i < smallTile; i++)
	{
		for (int o = 0; o < smallTile; o++)
		{
			for (int w = 0,countW=0; w < lilgridDimensions;countW++)
			{
				if(countW<2)
				{
					countW = 0;
					w++;
				}
				for (int h = 0,countH=0; h < lilgridDimensions;countH++)
				{
					if (countH < 2)
					{
						countH = 0;
						h++;
					}
					smallTileGrid[i][o] = Tile(i, o, tileW, tileH, lilgrid[w][h]);
				}
			}
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
	for (int i = 0; i < smallTile; i++)
	{
		for (int o = 0; o < smallTile; o++)
		{
			if (smallTileGrid[i][o].m_active)
			{
				SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			}
			else
			{
				SDL_SetRenderDrawColor(renderer, 69, 69, 69, 255);//change drawing colour if the tile is blocked or not
			}
			SDL_RenderDrawRect(renderer, &smallTileGrid[i][o].rectangle);//draw rectangle
			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 200);
			//draw outlines
			SDL_RenderDrawLine(renderer, smallTileGrid[i][o].rectangle.x, smallTileGrid[i][o].rectangle.y, smallTileGrid[i][o].rectangle.w + smallTileGrid[i][o].rectangle.x, smallTileGrid[i][o].rectangle.y);
			SDL_RenderDrawLine(renderer, smallTileGrid[i][o].rectangle.w+ smallTileGrid[i][o].rectangle.x, smallTileGrid[i][o].rectangle.y, smallTileGrid[i][o].rectangle.w + smallTileGrid[i][o].rectangle.x, smallTileGrid[i][o].rectangle.y+ smallTileGrid[i][o].rectangle.h);
			SDL_RenderDrawLine(renderer, smallTileGrid[i][o].rectangle.x, smallTileGrid[i][o].rectangle.y+ smallTileGrid[i][o].rectangle.h, smallTileGrid[i][o].rectangle.w + smallTileGrid[i][o].rectangle.x, smallTileGrid[i][o].rectangle.y+ smallTileGrid[i][o].rectangle.h);
			SDL_RenderDrawLine(renderer, smallTileGrid[i][o].rectangle.x, smallTileGrid[i][o].rectangle.y, smallTileGrid[i][o].rectangle.x, smallTileGrid[i][o].rectangle.y+ smallTileGrid[i][o].rectangle.w);
		}
	}
}

void Game::PollEvents()
{
}
