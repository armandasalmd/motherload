#include "TextureObject.h"
#include "TextureManager.h"


TextureObject::TextureObject(const char *path, int x, int y, bool anim) {
	ChangeTexture(path);
	mx = x;
	my = y;
	animated = anim;
}

TextureObject::TextureObject(const char *path) {
	TextureObject(path, 0, 0, false); // constructor function overloading
}

void TextureObject::Update() {
	srcRect.h = height; // object height
	srcRect.w = width; // object width
	destRect.h = height;
	destRect.w = width;

	if (animated)
		srcRect.x = srcRect.w * static_cast<int>((SDL_GetTicks() / anim_speed) % anim_frames);
	else
		srcRect.x = 0; // moving image texture inside the object box X
	srcRect.y = 0; // moving image texture inside the object box Y
	destRect.x = mx; // texture on the map cordinate x
	destRect.y = my; // texture on the map cordinate y
}

void TextureObject::Render() {
	SDL_RenderCopy(Game::renderer, objTexture, &srcRect, &destRect);
}

void TextureObject::Move(const int dx, const int dy) {
	mx += dx;
	my += dy;
}

void TextureObject::ChangeTexture(const char *path) {
	objTexture = TextureManager::LoadTexture(path);
}

int TextureObject::getX() {
	return mx;
}

int TextureObject::getY() {
	return my;
}

void TextureObject::SetDimentions(const int w, const int h) {
	width = w;
	height = h;
}
