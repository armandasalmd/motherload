#pragma once
#include "TextureObject.h"

class Player: public TextureObject {
public:



	Player(const char *path) : TextureObject(path) {

	}

	Player(const char *path, int x, int y, bool anim) : TextureObject(path, x, y, anim) {

	}


};