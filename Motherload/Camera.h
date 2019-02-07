#pragma once
#include "Map.h"
#include "Player.h"
#include "TextureObject.h"
#include "SDL.h"
#include "SDL_image.h"

class Camera {
public:
	// this class performs rendering all objects together
	// but it does not perform object movement

	Camera(Game *game, Map *map, Player *player, TextureObject *background);
	//~Camera();
	void RenderAll();
	void UpdateAll();
	int *calcCameraCoordinates();

private:
	Game *game;
	Map *map;
	Player *player;
	TextureObject *background;
	SDL_Rect cam = { 0, 0, Winfo::width, Winfo::height };
};