#pragma once
#include "SDL2-2.0.7\include\SDL.h"
#include "Tile.h"
#include <vector>
#include "GridTemplate.h"
class Game
{
private:


public:
	Game();
	~Game();
	void init(int width, int height);

	void Update();
	void Draw();
	void PollEvents();
	bool isRunning;
	int fps;
	SDL_Renderer* renderer;
	SDL_Window* window;
	const int smallTile = 30;
	const int medTile = 100;
	const int largeTile = 1000;

	Tile smallTileGrid[30][30];
	Tile medTileGrid[100][100];
	Tile largeTileGrid[1000][1000];
};

