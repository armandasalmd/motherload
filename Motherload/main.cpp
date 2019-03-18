// summary:
//		startup file, counts fps, runs main loop
// author:
//		barkausa

#include "SDL.h"
#include "Models.h"
#include "Game.h"
#include "StaticVars.h"
#include "sqlite3.h"

Game *game = nullptr;

void RenderGame(int fps);

// -------------------- START Reference -------------------
//		source:  YouTube
//		author:  Let's Make Games
//		comment: Game loop, fps limitation
//		href:	 https://www.youtube.com/channel/UCAM9ZPgEIdeHAsmG50wqL1g">
int main(int argc, char *argv[]) {
	Uint32 frameStart;
	int frameTime;
	int fps = Winfo::FPS;
	// possible overstep, collision errors!
	if (Gsettings::step > Winfo::block_size) {
		std::cout << "Step size cannot be bigger than block size!" << std::endl;
		return 1;
	}
	// preparing game object
	game = new Game();
	game->init(Winfo::title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
		Winfo::width, Winfo::height, Winfo::full_screen, 2); // init game window!
	// main game loop
	while (game->running()) {
		frameStart = SDL_GetTicks();
		RenderGame(fps);
		frameTime = SDL_GetTicks() - frameStart;

		// if frame loads to fast, delay to hold required FPS
		if (Winfo::frameDelay > frameTime) 
		{
			SDL_Delay(Winfo::frameDelay - frameTime);
			fps = Winfo::FPS;
		}
		else
			fps = 1000 / frameTime;
		// else: computer fall behind - do not delay
	}
	game->clean(); // destroy the Game
	
	delete Models::getInstance();
	return 0;	   // game closed
}
// ------------------ END reference -------------------


void RenderGame(int fps) {
	game->handleEvents();	// handle any user input
	game->update();			// update all objects eg. positions etc.
	game->render(fps);		// render changes to the display
}