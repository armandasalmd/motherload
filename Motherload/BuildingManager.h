#pragma once
#include "Models.h"
#include "ModelObjects.h"
#include "BuildingObject.h"
#include <array>
class BuildingManager {


public:
	const int BUILDINGS_COUNT = 4;

	BuildingManager() {
		for (int i = 0; i < BUILDINGS_COUNT; i++) {
			BuildingModel model = Models::getInstance()->getBuildingById(i);
			buildings[i] = BuildingObject(model);
			// setting the texture dimentions:
			buildings[i].SetDimentions(model.getWidth() * Winfo::block_size, 2 * Winfo::block_size); 
		}
	}

	void UpdateAll() {
		for (int i = 0; i < BUILDINGS_COUNT; i++)
			buildings[i].Update();
	}

	void RenderAll() {
		for (int i = 0; i < BUILDINGS_COUNT; i++)
		{
			buildings[i].Render();
		}
	}

	void SetDrawCoordinates(int *cCoords) {
		for (int i = 0; i < BUILDINGS_COUNT; i++)
			buildings[i].SetDrawCoords(buildings[i].PosX() - cCoords[0], buildings[i].PosY() - cCoords[1]);
	}



private:
	//BuildingObject *buildings;
	std::array<BuildingObject, 4> buildings;
};