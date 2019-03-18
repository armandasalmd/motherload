#ifndef Game_h
#define Game_h

#include "SDL.h"
#include "SDL_image.h"
#include "Models.h"
#include <iostream>

// summary:
//		Unit to track game state
enum State { MainMenu, Pause, InGame, GasStation, Market, UpgradesShop, Save };

// summary:
//		root/engine game class that handles frame loops
// author:
//		barkausa
class Game {
public:
	static SDL_Renderer *renderer;

	// -------------- Preparation --------------
	Game();

	// summary:
	//		Loads start-up classes, prepares for game start
	// param:
	//		xpos:      SDL align flag
	//		ypos:      SDL align flag
	//		width:     Windows width
	//		height:    Windows height
	//		player_id: For selection of player from database
	void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen, int player_id);

	// -------------- Setters --------------
	void setState(State s);
	
	// -------------- Getters --------------
	inline State getState() { return haltForInGame ? State::InGame : gameState;	}
	inline char getXpress() { return x_key_pressed; }
	inline char getYpress() { return y_key_pressed; }
	inline bool running() { return isRunning; }
	
	// -------------- Looping funcs --------------
	
	// summary:
	//		Reads keyboard inputs	
	void handleEvents();

	// summary:
	//		Calls funcs to calculate drawable objects coords.	
	void update();

	// summary:
	//		Calls funcs to draw objects on the screen	
	void render(int fps);

	// summary:
	//		Destroys objects, saves, quits game	
	void clean();
	
	// -------------- Text printing funcs --------------
	// summary:
	//		renders text on the screen
	// param:
	//		x: absolute x drawing position
	//		y: absolute y drawing position
	void printText(std::string text, int x, int y);
	void printText(std::string text, int font_size, int x, int y);

	// summary:
	//		renders toolbar using printText func
	void printToolbar(int fps);
private:
	bool isRunning;
	State gameState = InGame;
	bool haltForInGame = false;
	SDL_Window *window;
	
	// summary:
	//		tracks current key pressed on keyboard
	char x_key_pressed = '*'; // * - stand still, l - left, r - right
	char y_key_pressed = '*'; // * - stand still, u - up, d - down
};
#endif /* Game_hpp */
