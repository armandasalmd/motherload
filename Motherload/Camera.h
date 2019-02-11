#pragma once
#ifndef Camera_h
#define Camera_h

#include "Player.h"
#include "TextureObject.h"
#include "SDL.h"
#include "SDL_image.h"

class Camera {
public:
	// this class performs rendering all objects together
	// but it does not perform object movement

	Camera(Game *game, Player *player, TextureObject *background);
	//~Camera();
	void RenderAll();
	void RenderBg();
	void RenderPlayer();

	void UpdateAll();
	int *calcCameraCoordinates();

private:
	Game *game;
	Player *player;
	TextureObject *background;
};

#endif