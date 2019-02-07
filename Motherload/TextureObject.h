#pragma once
#include "Game.h"
#include "StaticVars.h"

class TextureObject {

public:
	TextureObject(const char *path, int x, int y, bool anim);
	TextureObject(const char *path);
	// ~TextureObject();

	void Update();
	void Render();
	void Move(const int dx, const int dy); // moves texture on the screen
	void SetDrawCoords(const int x, const int y);

	void SetOffset(const int dx, const int dy); // camera ofset
	void DeltaOffset(const int dx, const int dy); // move offset

	void ChangeTexture(const char *path);
	void SetDimentions(const int w, const int h);
	int getX();
	int getY();

protected:
	int mx = 0;
	int my = 0;
	int width = Winfo::block_size;
	int height = Winfo::block_size;
	int offsetX = 0; // camera offset
	int offsetY = 0; // camera offset

	bool animated = false;
	int anim_speed = 250;
	int anim_frames = 4;

	SDL_Texture *objTexture;
	SDL_Rect srcRect, destRect;
};