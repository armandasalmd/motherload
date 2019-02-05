#include "GameObject.h"
#include "TextureManager.h"

GameObject::GameObject(const char *texturesheet, int x, int y) {
	objTexture = TextureManager::LoadTexture(texturesheet);
	xpos = x;
	ypos = y;
}


void GameObject::Update() {
	srcRect.h = height;
	srcRect.w = width;
	srcRect.x = 0/*srcRect.w * static_cast<int>((SDL_GetTicks() / 250) % 4)*/;
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

int GameObject::getX() {
	return xpos;
}

int GameObject::getY() {
	return ypos;
}


void GameObject::SetDimentions(const int w, const int h) {
	width = w;
	height = h;
}