// <summary>root/engine game class that handles frame loops</summary>
// <author>barkausa</author>

#ifndef Game_h
#define Game_h

#include "SDL.h"
#include "SDL_image.h"
#include "Models.h"
#include <iostream>

enum State { MainMenu, Pause, InGame, GasStation, Market, UpgradesShop, Save };

class Game {
public:
	static SDL_Renderer *renderer;

	// __________ Preparation __________
	Game();
	void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen, int player_id);

	// __________ Setters __________
	void setState(State s);
	
	// __________ Getters __________
	inline State getState() { return gameState; }
	inline char getXpress() { return x_key_pressed; }
	inline char getYpress() { return y_key_pressed; }
	inline bool running() { return isRunning; };
	
	// __________ Looping funcs __________
	void handleEvents();
	void update();
	void render(int fps);
	void clean();
	
	// __________ Text printing funcs __________
	void printText(std::string text, int x, int y); // prints given text
	void printText(std::string text, int font_size, int x, int y); // prints given text
	void printToolbar(int fps);
private:
	bool isRunning;
	State gameState = InGame;
	bool haltForInGame = false;
	SDL_Window *window;

	char x_key_pressed = '*'; // * - stand still, l - left, r - right
	char y_key_pressed = '*'; // * - stand still, u - up, d - down
};
#endif /* Game_hpp */

