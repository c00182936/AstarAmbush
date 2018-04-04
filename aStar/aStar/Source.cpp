#include <iostream>
#include "SDL2-2.0.7\include\SDL.h"
#include "SDL2-2.0.7\include\SDL_image.h"
#include "SDL2-2.0.7\include\SDL_system.h"
#include "SDL2-2.0.7\include\SDL_ttf.h"
#include "SDL2-2.0.7\include\SDL_timer.h"
#include "Game.h"

int main()
{
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_Init(IMG_INIT_PNG);
	Game game;
	
	int FRAME_DELAY = 1000 / game.fps;
	Uint32 START_FRAME;
	int FRAME_TIME;


	//game.init(762, 762);
	while (game.isRunning)
	{
		START_FRAME = SDL_GetTicks();

		game.Update();
		game.Draw();

		FRAME_TIME = SDL_GetTicks() - START_FRAME;
		FRAME_DELAY = 1000 / game.fps;
		if (FRAME_DELAY > FRAME_TIME)
		{
			SDL_Delay(FRAME_DELAY - FRAME_TIME);
		}
	}
	return 0;
}