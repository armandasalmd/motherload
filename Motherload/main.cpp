#include "SDL.h"
#include "Game.h"
#include "StaticVars.h"
#include "sqlite3.h"

Game *game = nullptr;

int main(int argc, char *argv[]) {	
	Uint32 frameStart;
	int frameTime;

	game = new Game();
	game->init(Winfo::title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
		Winfo::width, Winfo::height, Winfo::full_screen); // init game window!
	
	while (game->running()) {
		frameStart = SDL_GetTicks();

		game->handleEvents(); // handle any user input
		game->update(); // update all objects eg. positions etc.
		game->render(); // render changes to the display

		frameTime = SDL_GetTicks() - frameStart;

		if (Winfo::frameDelay > frameTime) // if frame loads to fast, delay to hold required FPS
			SDL_Delay(Winfo::frameDelay - frameTime);
		// else: computer is slow and it is lagging - do not delay
	}
	game->clean(); // destroy the Game

	return 0;
}