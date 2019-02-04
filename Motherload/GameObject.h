#pragma once
#include "Game.h"
#include "StaticVars.h"

class GameObject {


public:
	GameObject(const char *texturesheet, int x, int y);
	GameObject(const char *texturesheet, int x, int y, bool is_background);
	~GameObject();
	
	void Update();
	void Render();
	void Step(const int dx, const int dy); // only for player object, it allow to move it
	int getX();
	int getY();

private:
	int xpos;
	int ypos;
	bool isBackground = true;

	SDL_Texture *objTexture;
	SDL_Rect srcRect, destRect;



};


