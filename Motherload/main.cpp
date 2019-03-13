#include "SDL.h"
#include "Game.h"
#include "StaticVars.h"
#include "sqlite3.h"
#include "Models.h"

Game *game = nullptr;

void RenderGame(int fps);

int main(int argc, char *argv[]) {	
	Uint32 frameStart;
	int frameTime;
	int fps = Winfo::FPS;

	if (Gsettings::step > Winfo::block_size) {
		std::cout << "Step size cannot be bigger than block size!" << std::endl;
		return 1;
	}

	game = new Game();
	game->init(Winfo::title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
		Winfo::width, Winfo::height, Winfo::full_screen, 2); // init game window!

	while (game->running()) {
		frameStart = SDL_GetTicks();

		RenderGame(fps);

		frameTime = SDL_GetTicks() - frameStart;
		if (Winfo::frameDelay > frameTime) // if frame loads to fast, delay to hold required FPS
		{
			SDL_Delay(Winfo::frameDelay - frameTime);
			fps = Winfo::FPS;
		}
		else
			fps = 1000 / frameTime;
		// else: computer is slow and it is lagging - do not delay
	}
	game->clean(); // destroy the Game
	
	delete Models::getInstance();
	//delete game;

	return 0;
}


void RenderGame(int fps) {
	game->handleEvents(); // handle any user input
	game->update(); // update all objects eg. positions etc.
	game->render(fps); // render changes to the display
}