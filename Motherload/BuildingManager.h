#pragma once
#include "Models.h"
#include "ModelObjects.h"
#include "BuildingObject.h"
#include <array>

// summary:
//		handles drawing of all buildings
// author:
//		barkausa
class BuildingManager {
public:
	const int BUILDINGS_COUNT = 4;
	// ----------------- Constructors --------------
	BuildingManager();
	// ----------------- Rendering -----------------
	void UpdateAll();
	void RenderAll();
	// summary:
	//		calculates drawing coords.(on screen) for every building
	// param:
	//		cCoords: camera coords.
	void SetDrawCoordinates(int *cCoords);
private:
	std::array<BuildingObject, 4> buildings;
};