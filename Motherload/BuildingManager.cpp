#include "BuildingManager.h"

BuildingManager::BuildingManager() {
	for (int i = 0; i < BUILDINGS_COUNT; i++) {
		// Getting info from database for every building
		BuildingModel model = Models::getInstance()->getBuildingById(i);
		buildings[i] = BuildingObject(model);
		// setting the texture dimentions:
		buildings[i].SetDimentions(model.getWidth() * Winfo::block_size, 2 * Winfo::block_size);
	}
}

void BuildingManager::UpdateAll() {
	for (int i = 0; i < BUILDINGS_COUNT; i++) // Updating all buildings
		buildings[i].Update();
}

void BuildingManager::RenderAll() {
	for (int i = 0; i < BUILDINGS_COUNT; i++) // Rendering all buildings
		buildings[i].Render();
}

void BuildingManager::SetDrawCoordinates(int *cCoords) {
	// Setting drawing coordinates for all buildings according to camera
	for (int i = 0; i < BUILDINGS_COUNT; i++)
		buildings[i].SetDrawCoords(buildings[i].PosX() - cCoords[0], buildings[i].PosY() - cCoords[1]);
}