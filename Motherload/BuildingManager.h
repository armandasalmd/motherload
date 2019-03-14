// <summary>handles drawing of all buildings</summary>
// <author>barkausa</author>

#pragma once
#include "Models.h"
#include "ModelObjects.h"
#include "BuildingObject.h"
#include <array>

class BuildingManager {
public:
	const int BUILDINGS_COUNT = 4;
	// __________ Constructors __________
	BuildingManager();
	// __________ Rendering __________
	void UpdateAll();
	void RenderAll();
	void SetDrawCoordinates(int *cCoords);
private:
	std::array<BuildingObject, 4> buildings;
};