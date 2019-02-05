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
	void ChangeTexture(const char *path);
	void SetDimentions(const int w, const int h);
	int getX();
	int getY();

private:
	int mx;
	int my;
	int width = Winfo::block_size;
	int height = Winfo::block_size;

	bool animated = false;
	int anim_speed = 250;
	int anim_frames = 4;

	SDL_Texture *objTexture;
	SDL_Rect srcRect, destRect;
};