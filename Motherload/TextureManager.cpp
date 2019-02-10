#include "TextureManager.h"

SDL_Texture *TextureManager::LoadTexture(const char *texture) {
	SDL_Surface *tempSurface = IMG_Load(texture);
	SDL_Texture *tex = SDL_CreateTextureFromSurface(Game::renderer, tempSurface);
	SDL_FreeSurface(tempSurface);
	return tex;
}

void TextureManager::Draw(SDL_Texture * tex, SDL_Rect src, SDL_Rect dest)
{

	SDL_RenderCopy(Game::renderer, tex, &src, &dest);
}

/*void TextureManager::ApplySurface(int x, int y, SDL_Surface* source, SDL_Surface* destination) {
	//Make a temporary rectangle to hold the offsets
	SDL_Rect offset;
	//Give the offsets to the rectangle
	offset.x = x;
	offset.y = y;
	//Blit the surface
	SDL_BlitSurface(source, NULL, destination, &offset);
}*/