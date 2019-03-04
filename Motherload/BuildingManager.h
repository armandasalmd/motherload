#pragma once
#include "Models.h"
#include "ModelObjects.h"
#include "BuildingObject.h"

class BuildingManager {


public:
	const int BUILDINGS_COUNT = 4;

	BuildingManager() {
		buildings = new BuildingObject[4];
		for (int i = 0; i < BUILDINGS_COUNT; i++) {
			BuildingModel model = Models::getInstance()->getBuildingById(i);
			buildings[i] = BuildingObject(model);
		}
	}




private:

	BuildingObject *buildings;


};