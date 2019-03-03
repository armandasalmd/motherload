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

Map *map;
TextureObject *background;
Player *player;
Camera *cam;

SDL_Renderer *Game::renderer = nullptr;

double gravity_speed = 1;
double acceleration = 0;

Game::Game() {}
Game::~Game() {}

void Game::init(const char *title, int xpos, int ypos, int width, int height, bool fullscreen) {
	// Preparing game objects
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
	// Initializing/loading textures of game objects
	background = new TextureObject("assets/background.png");
	player = new Player("assets/player.png", 0, 0, false);
	cam = new Camera(this, player, background);
	map = new Map(player);

	background->SetDimentions(Winfo::width, Winfo::height);
	background->DeltaOffset(Winfo::block_size * Gsettings::spawn_x, Winfo::block_size * Gsettings::spawn_y);
	player->SetCoords(Winfo::block_size * Gsettings::spawn_x, Winfo::block_size * Gsettings::spawn_y);
	player->Move(Winfo::block_size * Gsettings::spawn_x, Winfo::block_size * Gsettings::spawn_y);
	player->Update();
}

void Game::printText(std::string text, int text_size, int x, int y) {
	TTF_Font* font = TTF_OpenFont("Sans.ttf", text_size);
	SDL_Color textColor = { 255, 255, 255, 0 };
	SDL_Surface* textSurface = TTF_RenderText_Solid(font, text.c_str(), textColor);
	SDL_Texture* textt = SDL_CreateTextureFromSurface(renderer, textSurface);
	int text_width = textSurface->w; // gets generated text width
	int text_height = textSurface->h; // get generated text height
	SDL_FreeSurface(textSurface);
	SDL_Rect renderQuad = { x, y, text_width, text_height };
	SDL_RenderCopy(renderer, textt, NULL, &renderQuad);
	SDL_DestroyTexture(textt);
	TTF_CloseFont(font);
	font = nullptr;
}

void Game::printText(std::string text, int x, int y) {
	printText(text, Winfo::text_size, x, y); // function overload
}

void Game::printToolbar(int fps) {
	//printText("Health: 100hp", 5, 0);
	//printText("Fuel: 6l/10l", 5, Winfo::text_size);
	//printText("Money: 55£", 5, Winfo::text_size * 2);
	int *mCord = Map::GetGridCordinates(player->PosX() + Winfo::block_size / 2, player->PosY() + Winfo::block_size / 2);
	std::string line3 = "x:" + std::to_string(mCord[0]) + " y:" + std::to_string(mCord[1]);
	printText(line3, 15, 5, 0);
	std::string line4 = "X:" + std::to_string(player->PosX()/* + Winfo::block_size / 2*/) + " Y:" + std::to_string(player->PosY()/* + Winfo::block_size / 2*/);
	printText(line4, 15, 5, Winfo::text_size);
	std::string line5 = "FPS:" + std::to_string(fps);
	printText(line5, 15, 5, Winfo::text_size * 2);
}

void Game::update() {
	// Make player movement here and etc...
	int move_x = 0, 
		move_y = 0;

	if (x_key_pressed != '*')
		move_x = x_key_pressed == 'l' ? -Gsettings::step : Gsettings::step;
	if (y_key_pressed != '*')
		move_y = y_key_pressed == 'u' ? -Gsettings::step : Gsettings::step;
	move_y = y_key_pressed == 'u' ? -Gsettings::step : (int)((double)Gsettings::step * Gsettings::gravity);
	
	Collision::MovePlayer(map, player, move_x, move_y); // it does the movement, as well as adjustify movement coordinates!

	// Updating all view objects
	cam->UpdateAll();
	background->Update();
}

void Game::render(int fps) {
	SDL_RenderClear(Game::renderer);
	// rendering all objects
	cam->RenderBg();
	map->DrawMap(*cam);
	cam->RenderPlayer();
	printToolbar(fps);
	SDL_RenderPresent(Game::renderer);
}

void Game::handleEvents() {
	SDL_Event ev;
	SDL_PollEvent(&ev);
	int key = ev.key.keysym.sym;

	if (ev.type == SDL_QUIT) 
		isRunning = false;

	if (ev.type == SDL_KEYUP) {
		if ((x_key_pressed == 'r' && key == 1073741903) || (x_key_pressed == 'l' && key == 1073741904))
			x_key_pressed = '*';
		if ((y_key_pressed == 'd' && key == 1073741905) || (y_key_pressed == 'u' && key == 1073741906))
			y_key_pressed = '*';
	}
	/* **** trenary operator possible for improvement **** */
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
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	std::cout << "Game cleaned" << std::endl;
}