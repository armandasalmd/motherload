#pragma once
#include "TextureManager.h"
#include "SDL_ttf.h"
#include <iostream>
#include "TextureObject.h"
#include "Player.h"
#include "Collision.h"
#include "Map.h"
#include "Camera.h"
#include "Game.h"
#include "BuildingManager.h"

//  Global, main game objects
BuildingManager *buildings;
Camera *cam;
Map *map;
Player *player;
TextureObject *background;
SDL_Renderer *Game::renderer = nullptr;

Game::Game() {}

// -------------------- START Reference -------------------
//	source:  YouTube 
//	author:  Let's Make Games
//	comment: Game preparation
//	href:	 https://www.youtube.com/watch?v=44tO977slsU
void Game::init(const char *title, int xpos, int ypos, int width, int height, bool fullscreen, int player_id) {
	// Preparing game objects:
	int flags = 0;
	if (fullscreen)
		flags = SDL_WINDOW_FULLSCREEN;
	if (TTF_Init() == -1) {
		std::cout << "TTF init failed!" << std::endl;
		isRunning = false;
	}
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) { // success
		std::cout << "Subsystems Initialized" << std::endl;
		window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
		if (window)
			std::cout << "Window created!" << std::endl;
		renderer = SDL_CreateRenderer(window, 0, 0); // Main renderer init
		if (renderer) {
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			std::cout << "Renderer created!" << std::endl;
		}
		isRunning = true;
	}
	else
		isRunning = false;
	// ------------------ END reference -------------------

	// Initializing/loading textures of game objects:
	background = new TextureObject("assets/background.png");
	player = new Player("assets/player.png", 0, 0, false);
	player->loadPlayerModel(player_id); // loading player model information from db

	buildings = new BuildingManager();
	cam = new Camera(this, player, background, buildings);
	map = new Map();

	// buildings->UpdateAll();
	background->SetDimentions(Winfo::width, Winfo::height);
	background->DeltaOffset(Winfo::block_size * Gsettings::spawn_x, 
							Winfo::block_size * Gsettings::spawn_y);
	// setting default player spawn coordinates
	player->SetCoords(Winfo::block_size * Gsettings::spawn_x, 
					  Winfo::block_size * Gsettings::spawn_y);
	player->Move(Winfo::block_size * Gsettings::spawn_x, 
				 Winfo::block_size * Gsettings::spawn_y);
	player->Update(); // preparing for rendering
}

void Game::printText(std::string text, int text_size, int x, int y) {
	// -------------------- START Reference -------------------
	//	source:  Stack overflow 
	//	author:  jpw
	//	comment: Text rendering
	//	href:	 https://stackoverflow.com/questions/22886500/how-to-render-text-in-sdl2
	TTF_Font* font = TTF_OpenFont("Sans.ttf", text_size);
	SDL_Color textColor = { 255, 255, 255, 0 };
	SDL_Surface* textSurface = TTF_RenderText_Solid(font, text.c_str(), textColor);
	SDL_Texture* textt = SDL_CreateTextureFromSurface(renderer, textSurface);
	int text_width = textSurface->w;  // gets generated text width
	int text_height = textSurface->h; // get generated text height
	SDL_FreeSurface(textSurface);
	SDL_Rect renderQuad = { x, y, text_width, text_height };
	SDL_RenderCopy(renderer, textt, NULL, &renderQuad);
	SDL_DestroyTexture(textt);
	// --------------------- END reference ---------------------
	TTF_CloseFont(font);
}

void Game::printText(std::string text, int x, int y) {
	// function overloading:
	// text size is not defined, use default size
	printText(text, Winfo::text_size, x, y);
}

void Game::printToolbar(int fps) {
	// getting player coords to print
	int *mCord = Map::GetGridCordinates(player->PosX() 
		+ Winfo::block_size / 2, player->PosY() + Winfo::block_size / 2);
	// making absolute coordinates string
	std::string line1 = "x:" + std::to_string(mCord[0]) 
		+ " y:" + std::to_string(mCord[1]);
	// printing absolute coordinates
	printText(line1, 15, 5, 0);
	// making grid coordinates string
	std::string line2 = "X:" + std::to_string(player->PosX()) 
		+ " Y:" + std::to_string(player->PosY());
	// printing grid coordinates
	printText(line2, 15, 5, Winfo::text_size);
	// making FPS string to show
	std::string line3 = "FPS:" + std::to_string(fps);
	// printing FPS
	printText(line3, 15, 5, Winfo::text_size * 2);
	
	printText("Balance: " + std::to_string(player->getPlayerBalance()), 15, 5, Winfo::text_size * 3);
	printText("Fuel: " + std::to_string(player->getPlayerFuel()), 15, 5, Winfo::text_size * 4);
}

void Game::update() {
	// Check key pressed and assigns movement size
	int move_x = 0, 
		move_y = 0;
	if (x_key_pressed != '*')
		move_x = x_key_pressed == 'l' ? -Gsettings::step : Gsettings::step;
	if (y_key_pressed != '*')
		move_y = y_key_pressed == 'u' ? -Gsettings::step : Gsettings::step;
	// gravity adjustments
	move_y = y_key_pressed == 'u' ? 
		-Gsettings::step : (int)((double)Gsettings::step * Gsettings::gravity);

	// performs player movement(changes coordinates)
	Collision::MovePlayer(this, map, player, move_x, move_y); 
	// Updates all view objects
	cam->UpdateAll();
}

void Game::render(int fps) {
	// clear old rendered screen
	SDL_RenderClear(Game::renderer);
	// renders all objects:
	cam->RenderBg();
	map->DrawMap(*cam);
	cam->RenderBuildings();
	cam->RenderPlayer();
	printToolbar(fps);
	// commits rendering
	SDL_RenderPresent(Game::renderer);
}

void Game::handleEvents() {
	SDL_Event ev;
	SDL_PollEvent(&ev);
	int key = ev.key.keysym.sym;

	if (ev.type == SDL_QUIT) 
		isRunning = false;

	if (ev.type == SDL_KEYUP) {
		if ((x_key_pressed == 'r' && key == 1073741903) || 
			(x_key_pressed == 'l' && key == 1073741904))
				x_key_pressed = '*';
		if ((y_key_pressed == 'd' && key == 1073741905) || 
			(y_key_pressed == 'u' && key == 1073741906))
				y_key_pressed = '*';
	}
	/* **** TODO: trenary operator possible for improvement **** */
	if (ev.type == SDL_KEYDOWN) {
		switch (key)
		{
		case 1073741903:
			x_key_pressed = 'r';
			break;
		case 1073741904:
			x_key_pressed = 'l';
			break;
		case 1073741905:
			y_key_pressed = 'd';
			break;
		case 1073741906:
			y_key_pressed = 'u';
			break;
		default:
			break;
		}
	}
}

void Game::clean() {
	// Saves player progress
	player->savePlayerModel();
	std::cout << "Player saved to database" << std::endl;
	// Clears memory
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	std::cout << "Game cleaned" << std::endl;
}

void Game::setState(State s) {
	// bool: wait for InGame state to be set
	if (haltForInGame && s == State::InGame)
		haltForInGame = false;
	else 
		gameState = s;
}