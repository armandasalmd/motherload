// <summary>root/engine game class that handles frame loops</summary>
// <author>barkausa</author>

#ifndef Game_h
#define Game_h

#include "SDL.h"
#include "SDL_image.h"
#include "Models.h"
#include <iostream>

/* <summary>Unit to track game state</summary> */
enum State { MainMenu, Pause, InGame, GasStation, Market, UpgradesShop, Save };

class Game {
public:
	static SDL_Renderer *renderer;

	// __________ Preparation __________
	Game();
	/*
	<summary>Loads start-up classes, prepares for game start</summary>
	<param name="xpos">SDL align flag</param>
	<param name="ypos">SDL align flag</param>
	<param name="width">Windows width</param>
	<param name="height">Windows height</param>
	<param name="player_id">For selection of player from database</param>
	*/
	void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen, int player_id);

	// __________ Setters __________
	void setState(State s);
	
	// __________ Getters __________
	inline State getState() { return haltForInGame ? State::InGame : gameState;	}
	inline char getXpress() { return x_key_pressed; }
	inline char getYpress() { return y_key_pressed; }
	inline bool running() { return isRunning; }
	
	// __________ Looping funcs __________
	/* <summary>Reads keyboard inputs</summary> */
	void handleEvents();
	/* <summary>Calls funcs to calculate drawable objects coords.</summary>	*/
	void update();
	/* <summary>Calls funcs to draw objects on the screen</summary>	*/
	void render(int fps);
	/* <summary>Destroys objects, saves, quits game</summary> */
	void clean();
	
	// __________ Text printing funcs __________
	/*
	<summary>renders text on the screen</summary>
	<param name="x">absolute x drawing position</param>
	<param name="y">absolute y drawing position</param>
	*/
	void printText(std::string text, int x, int y);
	void printText(std::string text, int font_size, int x, int y);
	/* <summary>renders toolbar using printText func</summary> */
	void printToolbar(int fps);
private:
	bool isRunning;
	State gameState = InGame;
	bool haltForInGame = false;
	SDL_Window *window;
	
	/* <summary>tracks current key pressed on keyboard</summary> */
	char x_key_pressed = '*'; // * - stand still, l - left, r - right
	char y_key_pressed = '*'; // * - stand still, u - up, d - down
};
#endif /* Game_hpp */
