#pragma once
#include "Game.h"

// summary:
//		Main class responsible for image 
//		loading/drawing on the screen
// author:
//		barkausa
class TextureManager {
public:
	// ------------- Drawing funcs -------------
	static SDL_Texture *LoadTexture(std::string fileName);
	static SDL_Texture *LoadTexture(char *texture);
	static void Draw(SDL_Texture *tex, SDL_Rect src, SDL_Rect dest);
};