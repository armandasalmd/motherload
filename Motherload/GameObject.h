#pragma once
#include "Game.h"
#include "StaticVars.h"

class GameObject {


public:
	GameObject(const char *texturesheet, int x, int y);
	~GameObject();
	
	void Update();
	void Render();
	void Step(const int dx, const int dy); // only for player object, it allow to move it
	int getX();
	int getY();

	void SetDimentions(const int w, const int h);

private:
	int xpos;
	int ypos;
	bool isBackground = true;

	int width = Winfo::block_size;
	int height = Winfo::block_size;

	SDL_Texture *objTexture;
	SDL_Rect srcRect, destRect;



};


