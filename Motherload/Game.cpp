#include "Game.h"
#include "TextureManager.h"
#include "GameObject.h"
#include "Map.h"
#include "SDL_ttf.h"
#include <iostream>

Map *map;
GameObject *player;
SDL_Renderer *Game::renderer = nullptr;
double gravity_speed = 0;

Game::Game() {

}

Game::~Game() {

}

void Game::init(const char *title, int xpos, int ypos, int width, int height, bool fullscreen) {
	int flags = 0;

	if (fullscreen) {
		flags = SDL_WINDOW_FULLSCREEN;
	}

	if (TTF_Init() == -1) {
		std::cout << "TTF init failed!" << std::endl;
		isRunning = false;
	}

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) { // success
		std::cout << "Subsystems Initialized" << std::endl;

		window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
		if (window) {
			std::cout << "Window created!" << std::endl;
		}

		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer) {
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			std::cout << "Renderer created!" << std::endl;
		}
		isRunning = true;
	}
	else {
		isRunning = false;
	}

	player = new GameObject("assets/player.png", 0, 0);
	map = new Map();

	player->Update(); // temp
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
}
void Game::printText(std::string text, int x, int y) {
	printText(text, Winfo::text_size, x, y); // function overload
}

void Game::printMenu() {
	printText("Heha", 5, 0);
	printText("Heha2", 5, Winfo::text_size);
	std::string line3 = "x:" + std::to_string(player->getX()) + " y:" + std::to_string(player->getY());
	printText(line3, 15, 5, Winfo::text_size * 2);
}

void Game::update() {
	gravity_speed += Gsettings::gravity * (1 + gravity_speed);
	if (Gsettings::max_gravity_speed < gravity_speed)
		gravity_speed = Gsettings::max_gravity_speed;


	int move_x = 0;
	int move_y = 0;
	
	if (x_key_pressed != '*')
		move_x = x_key_pressed == 'l' ? -Gsettings::step : Gsettings::step;
	if (y_key_pressed != '*')
		move_y = y_key_pressed == 'u' ? -Gsettings::step : Gsettings::step;
	if (y_key_pressed == 'u')
		if (gravity_speed < Gsettings::gravity)
			gravity_speed = 1;
		else
			gravity_speed /= 2;

	player->Step(move_x, move_y + (int)gravity_speed);

	player->Update();
}

void Game::render() {
	SDL_RenderClear(renderer);
	
	map->DrawMap();
	player->Render();
	printMenu();

	SDL_RenderPresent(renderer);
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