#pragma once
#include <string>
#include "ModelObjects.h"
#include "TextureObject.h"
#include "StaticVars.h"

class BuildingObject : public TextureObject {

public:


	BuildingObject();

	BuildingObject(BuildingModel model) : TextureObject(model.getTexturePath().c_str()) {
		mModel = model;
		posx = model.getBuildingX() * Winfo::block_size;
		posy = model.getBuildingY() * Winfo::block_size;

	}



private:
	BuildingModel mModel;
	int posx, posy; // coordinates on the map

};


