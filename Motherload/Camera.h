#pragma once
#include "Player.h"
#include "TextureObject.h"
#include "BuildingManager.h"
#include "SDL.h"
#include "SDL_image.h"

// summary:
//		this class calculates final drawing coordinates 
//		and the renders all objects.
// remarks:
//		map rendering is excluded because anglissb does it separately
// author:
//		barkausa
class Camera {
public:
	// --------------- Constructors --------------
	// summary:
	//		Initializes camera object
	Camera(Game *game, Player *player, TextureObject *background, BuildingManager *buildings);

	// ---------------- Rendering -----------------
	void RenderAll();
	void RenderBg();
	void RenderPlayer();
	void RenderBuildings();
	void UpdateAll();

	// summary:
	//		calculates camera coords according to player position
	// returns:
	//		int array(size 2) - camera x, y
	int *calcCameraCoordinates();
private:
	Game *game;
	Player *player;
	TextureObject *background;
	BuildingManager *buildings;
};