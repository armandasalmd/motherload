#pragma once
#include "Game.h"
#include "StaticVars.h"

// summary:
//		Class holds main info about object 
//		drawing(size, coordinates...)
// remarks:
//		This class is parent(inherited) for 
//		Player, Block, Building objects
// author:
//		barkausa
class TextureObject {
public:
	// ------------ Constructors ------------
	TextureObject(const char *path, int x, int y, bool anim);
	TextureObject(const char *path);

	// ------------ Setters ------------
	void SetDrawCoords(const int x, const int y);
	void SetOffset(const int dx, const int dy);		// shift camera
	void SetDimentions(const int w, const int h);	// set object width, height

	// ------------ Getters ------------
	int getX();
	int getY();
	
	// ------------ Render funcs ------------
	void Update();
	void Render();
	
	// ------------ Texture manipulation ------------
	void Move(const int dx, const int dy);			// moves texture on the screen
	void DeltaOffset(const int dx, const int dy);	// move offset
	void ChangeTexture(const char *path);
protected:
	int mx = 0;			// Drawing on the screen x(px)
	int my = 0;			// Drawing on the screen y(px)
	int width = Winfo::block_size;
	int height = Winfo::block_size;
	int offsetX = 0;	// camera offset
	int offsetY = 0;	// camera offset

	bool animated = false;
	int anim_speed = 250;
	int anim_frames = 4;

	SDL_Texture *objTexture;
	SDL_Rect srcRect, destRect;
};