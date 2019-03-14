// <summary>Main class responsible for image loading/drawing on the screen</summary>
// <author>barkausa</author>

#pragma once
#include "Game.h"

class TextureManager {
public:
	// __________ Drawing funcs __________
	static SDL_Texture *LoadTexture(std::string fileName);
	static SDL_Texture *LoadTexture(char *texture);
	static void Draw(SDL_Texture *tex, SDL_Rect src, SDL_Rect dest);
};