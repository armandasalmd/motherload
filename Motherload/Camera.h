// <summary>this class calculates final drawing coordinates and the renders all objects</summary>
// <remarks>map rendering is excluded because anglissb does it separately</remarks>
// <author>barkausa</author>

#pragma once
#include "Player.h"
#include "TextureObject.h"
#include "BuildingManager.h"
#include "SDL.h"
#include "SDL_image.h"

class Camera {
public:
	// __________ Constructors __________
	/*
	<summary>Initializes camera object</summary> 
	*/
	Camera(Game *game, Player *player, TextureObject *background, BuildingManager *buildings);

	// __________ Rendering __________
	void RenderAll();
	void RenderBg();
	void RenderPlayer();
	void RenderBuildings();
	void UpdateAll();
	/*
	<summary>calculates camera coords according to player position</summary>
	<returns>int array(size 2) - camera x, y</returns> 
	*/
	int *calcCameraCoordinates();
private:
	Game *game;
	Player *player;
	TextureObject *background;
	BuildingManager *buildings;
};