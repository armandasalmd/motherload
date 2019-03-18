#include "TextureManager.h"

SDL_Texture *TextureManager::LoadTexture(std::string texture) {
	// ------------------ START Reference -----------------
	//	source:  YouTube 
	//	author:  Let's Make Games
	//	comment: Game preparation
	//	href:	 https://www.youtube.com/watch?v=44tO977slsU
	SDL_Surface *tempSurface = IMG_Load(texture.c_str());
	SDL_Texture *tex = SDL_CreateTextureFromSurface(Game::renderer, tempSurface);
	SDL_FreeSurface(tempSurface);
	return tex;
	// ------------------ END reference -------------------
}

SDL_Texture *TextureManager::LoadTexture(char *texture) {
	std::string temp(texture);
	return TextureManager::LoadTexture(temp);
}

void TextureManager::Draw(SDL_Texture * tex, SDL_Rect src, SDL_Rect dest)
{
	SDL_RenderCopy(Game::renderer, tex, &src, &dest); // draw call
}