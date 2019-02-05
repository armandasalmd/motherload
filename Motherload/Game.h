#ifndef Game_h

#define Game_h
#include "SDL.h"
#include "SDL_image.h"
#include <iostream>

class Game {

public:
	Game();
	~Game();

	void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
	
	void handleEvents();
	void update();
	void render();
	void clean();
	void printText(std::string text, int x, int y); // prints given text
	void printText(std::string text, int font_size, int x, int y); // prints given text
	void printToolbar();

	bool running() { return isRunning; };

	static SDL_Renderer *renderer;

private:
	bool isRunning;
	SDL_Window *window;

	char x_key_pressed = '*'; // * - stand still, l - left, r - right
	char y_key_pressed = '*'; // * - stand still, u - up, d - down

};

#endif /* Game_hpp */

