// <summary>this class calculates final drawing coordinates and the renders all objects</summary>
// <author>barkausa</author>

#pragma once
#include "Player.h"
#include "TextureObject.h"
#include "BuildingManager.h"
#include "SDL.h"
#include "SDL_image.h"

class Camera {
public:
	// this class performs rendering all objects together except Map rendering
	// but it does not perform object movement

	// __________ Constructors __________
	Camera(Game *game, Player *player, TextureObject *background, BuildingManager *buildings);

	// __________ Rendering __________
	void RenderAll();
	void RenderBg();
	void RenderPlayer();
	void RenderBuildings();
	void UpdateAll();
	int *calcCameraCoordinates();
private:
	Game *game;
	Player *player;
	TextureObject *background;
	BuildingManager *buildings;
};