#include "Game.h"
#include "TextureManager.h"
#include "GameObject.h"
#include "Map.h"

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
		//if (key == 1073741903 || key == 1073741904) { // left or right arrow pressed
		//	x_key_pressed = '*';
		//}		
		//if (key == 1073741905 || key == 1073741906) { // top or bottom arrow pressed
		//	y_key_pressed = '*';
		//}
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

	//if (ev.key.keysym.sym > 1000) { // not alphabet char
	//	int key = ev.key.keysym.sym - 1073741902;
	//	if (key == 1) // arrow right
	//		player->Step(Gsettings::step, 0);
	//	else if (key == 2) // arrow left
	//		player->Step(-Gsettings::step, 0);
	//	else if (key == 3) // arrow down
	//		player->Step(0, Gsettings::step);
	//	else if (key == 4) // arrow up
	//		player->Step(0, -Gsettings::step);
	//}
	//else if (ev.key.keysym.sym >= 97 && ev.key.keysym.sym <= 122) // smaller alphabet letters in ASCII
	//	std::cout << (char)ev.key.keysym.sym << std::endl;
	//else if (ev.key.keysym.sym >= 48 && ev.key.keysym.sym <= 57) // numbers in ASCII
	//	std::cout << (char)ev.key.keysym.sym << std::endl;
}

void Game::clean() {
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	std::cout << "Game cleaned" << std::endl;
}