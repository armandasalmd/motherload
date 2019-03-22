#include "BuildingObject.h"

BuildingObject::BuildingObject(BuildingModel model) : TextureObject(model.getTexturePath().c_str()) {
	mModel = model;
	// Setting object absolute(px) coordinates
	posx = model.getBuildingX() * Winfo::block_size;
	posy = model.getBuildingY() * Winfo::block_size;
}