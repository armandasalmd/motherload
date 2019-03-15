#include "TextureManager.h"

// <reference source="Github" 
//		author="Let's Make Games"
//		comment="Texture manager, main drawing class"
//		href="https://github.com/carlbirch/BirchEngine/blob/master/BirchEngine/Src/TextureManager.cpp">
SDL_Texture *TextureManager::LoadTexture(std::string texture) {
	SDL_Surface *tempSurface = IMG_Load(texture.c_str());
	SDL_Texture *tex = SDL_CreateTextureFromSurface(Game::renderer, tempSurface);
	SDL_FreeSurface(tempSurface);
	return tex;
}

SDL_Texture *TextureManager::LoadTexture(char *texture) {
	std::string temp(texture);
	return TextureManager::LoadTexture(temp);
}

void TextureManager::Draw(SDL_Texture * tex, SDL_Rect src, SDL_Rect dest)
{
	SDL_RenderCopy(Game::renderer, tex, &src, &dest);
}
// </reference>