#pragma once
#include <string>
#include "ModelObjects.h"
#include "TextureObject.h"
#include "StaticVars.h"
//#include <iostream>

class BuildingObject : public TextureObject {

public:


	BuildingObject() : TextureObject("") { };

	BuildingObject(BuildingModel model) : TextureObject(model.getTexturePath().c_str()) {
		//std::cout << model.getTexturePath().c_str() << std::endl;
		mModel = model;
		posx = model.getBuildingX() * Winfo::block_size;
		posy = model.getBuildingY() * Winfo::block_size;

	}


	void SetPosCoords(int x, int y) { posx = x, posy = y; }
	void SetX(int x) { posx = x; }
	void SetY(int y) { posy = y; }
	int PosX() { return posx; }
	int PosY() { return posy; }
	BuildingModel GetModel() { return mModel; }

private:
	BuildingModel mModel;
	int posx, posy; // coordinates on the map

};


