#pragma once
#include "TextureObject.h"

class Player: public TextureObject {
public:
	Player(const char *path) : TextureObject(path) {}

	Player(const char *path, int x, int y, bool anim) : TextureObject(path, x, y, anim) {}

	// camera position regulation on the screen function
	void Step(const int dx, const int dy);

	// player map coordinates
	int PosX() { return positionX; }
	int PosY() { return positionY; }
	
	// player map coordinates function
	void SetCoords(int x, int y);
	void SetX(int x) { positionX = x; };
	void SetY(int y) { positionY = y; };
	
	// player map coordinates function
	void DeltaCoords(int dx, int dy) { SetCoords(positionX + dx, positionY + dy); }
	void DeltaX(int dx) { SetCoords(positionX + dx, positionY); }
	void DeltaY(int dy) { SetCoords(positionX, positionY + dy); }

private:
	int positionX = 0; // player x position in pixels on the map
	int positionY = 0; // player y position in pixels on the map
};