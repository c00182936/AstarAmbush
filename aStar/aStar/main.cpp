#include "Game.h"
#include <SDL.h>
#include <SDL_image.h>

int main(int argc, char* argv[])
{
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_Init(IMG_INIT_PNG);

	const int FRAMES_PER_SECOND = 60;
	const int FRAME_DELAY = 1000 / FRAMES_PER_SECOND;
	Uint32 START_FRAME;
	int FRAME_TIME;

	Game game;
	game.init(762,762);
	while (game.isRunning)
	{
		START_FRAME = SDL_GetTicks();

		game.Update();
		game.Draw();

		FRAME_TIME = SDL_GetTicks() - START_FRAME;

		if (FRAME_DELAY > FRAME_TIME)
		{
			SDL_Delay(FRAME_DELAY - FRAME_TIME);
		}
	}

	return 0;
}