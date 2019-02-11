#pragma once

#include "Game.h"

class TextureManager {
public:
	static SDL_Texture *LoadTexture(std::string fileName);
	static SDL_Texture *LoadTexture(char *texture);
	static void Draw(SDL_Texture *tex, SDL_Rect src, SDL_Rect dest);
	//static void ApplySurface(int x, int y, SDL_Surface* source, SDL_Surface* destination);
};