#include "GameObject.h"
#include "TextureManager.h"

GameObject::GameObject(const char *texturesheet, int x, int y) {
	objTexture = TextureManager::LoadTexture(texturesheet);
	xpos = x;
	ypos = y;
}

GameObject::GameObject(const char *texturesheet, int x, int y, bool is_background) {
	objTexture = TextureManager::LoadTexture(texturesheet);
	xpos = x;
	ypos = y;
	isBackground = is_background;
}

void GameObject::Update() {
	/* xpos++;
	   ypos++; */

	srcRect.h = Winfo::block_size;
	srcRect.w = Winfo::block_size;
	srcRect.x = 0;
	srcRect.y = 0;

	destRect.x = xpos;
	destRect.y = ypos;
	destRect.w = srcRect.w;
	destRect.h = srcRect.h;
}


void GameObject::Step(const int dx, const int dy) {
	xpos += dx;
	ypos += dy;
}


void GameObject::Render() {

	SDL_RenderCopy(Game::renderer, objTexture, &srcRect, &destRect);

}