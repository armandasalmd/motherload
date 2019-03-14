#include "TextureObject.h"
#include "TextureManager.h"

TextureObject::TextureObject(const char *path, int x, int y, bool anim) {
	ChangeTexture(path);
	mx = x; // real drawing coordinates on the screen
	my = y;
	animated = anim;
}

TextureObject::TextureObject(const char *path) {
	ChangeTexture(path);
	mx = 0; my = 0;
	animated = false;
}

void TextureObject::Update() {
	srcRect.h = height; // object height
	srcRect.w = width; // object width
	destRect.h = height;
	destRect.w = width;
	if (animated)
		srcRect.x = srcRect.w * static_cast<int>((SDL_GetTicks() / anim_speed) % anim_frames);
	else
		srcRect.x = offsetX; // moving image texture inside the object box X
	srcRect.y = offsetY; // moving image texture inside the object box Y
	destRect.x = mx; // texture on the map cordinate x
	destRect.y = my; // texture on the map cordinate y
}

void TextureObject::SetDimentions(const int w, const int h) {
	width = w;
	height = h;
}

void TextureObject::Render() {
	SDL_RenderCopy(Game::renderer, objTexture, &srcRect, &destRect);
}

void TextureObject::Move(const int dx, const int dy) {
	mx += dx;
	my += dy;
}

void TextureObject::SetDrawCoords(const int x, const int y) {
	mx = x; my = y;
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

void TextureObject::SetOffset(const int x, const int y) {
	if (x >= 0 && x <= WorldInfo::world_width - Winfo::width)
		offsetX = x; 
	if (y >= 0 && y <= WorldInfo::world_height - Winfo::height)
		offsetY = y;
}

void TextureObject::DeltaOffset(const int dx, const int dy) {
	offsetX += dx; offsetY += dy;
}