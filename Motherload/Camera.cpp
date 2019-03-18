#pragma once
#include "Camera.h"

Camera::Camera(Game *game, Player *player, TextureObject *background, BuildingManager *buildings) {
	// gathering required objects
	this->game = game;
	this->player = player;
	this->background = background;
	this->buildings = buildings;
}

void Camera::UpdateAll() {
	int *cCoords = calcCameraCoordinates(); // getting camera coords(px)
	// initializing player drawing coordinates (middle of the screen)
	int new_player_x = (Winfo::width - Winfo::block_size) / 2, 
		new_player_y = Winfo::height / 4 - Winfo::block_size / 2;

	// checking if camera touches map boundaries if so:
	// player is not going to be drawn in the middle
	if (cCoords[0] <= 0) // left bounder detection
		new_player_x = player->PosX();
	else if (cCoords[0] >= WorldInfo::world_width - Winfo::width) // right bounder detection
		new_player_x = Winfo::width + player->PosX() - WorldInfo::world_width;
	if (cCoords[1] <= 0) // top bounder detection
		new_player_y = player->PosY();
	else if (cCoords[1] >= WorldInfo::world_height - Winfo::height - Winfo::block_size) // bottom bounder detection
		new_player_y = Winfo::height + player->PosY() - WorldInfo::world_height + Winfo::block_size;

	// preparing player to be drawn(rendered)
	player->SetDrawCoords(new_player_x, new_player_y); // setting final coordinates
	player->Update(); // preparing for render
	// preparing buildings to be drawn(rendered)
	buildings->SetDrawCoordinates(cCoords); // updates draw coordinates
	buildings->UpdateAll();
	// preparing background to be drawn(rendered)
	background->SetOffset(cCoords[0], cCoords[1]);
	background->Update();
}

void Camera::RenderAll() {
	// rendersing all entities
	RenderBg();
	RenderBuildings();
	RenderPlayer();
}

void Camera::RenderBg() {
	background->Render();
}
void Camera::RenderPlayer() {
	player->Render();
}

void Camera::RenderBuildings() {
	buildings->RenderAll();
}

int *Camera::calcCameraCoordinates() {
	int *coords = new int[2]{ 0, 0 }; // Final camera coordinates
	// Calculation part:
	//		Remark: 
	//			x-axis player is in the middle
	//		Remark: 
	//			y-axis player is in 1/4 of the top
	int *playerCoords = new int[2]{player->PosX() + Winfo::block_size / 2, 
								   player->PosY() + Winfo::block_size / 2 };
	// Assuming that player is in the middle,
	// setting default camera coords
	coords[0] = playerCoords[0] - Winfo::width / 2;
	coords[1] = playerCoords[1] - Winfo::height / 4;
	
	// Case: player touches left boundary
	if (coords[0] < 0) 
		coords[0] = 0;
	// Case: player touches right boundary
	if (coords[0] > WorldInfo::world_width - Winfo::width)
		coords[0] = WorldInfo::world_width - Winfo::width;
	// Case: player touches top boundary
	if (coords[1] < 0)
		coords[1] = 0;
	// Case: player touches bottom boundary
	if (coords[1] > WorldInfo::world_height - Winfo::height)
		coords[1] = WorldInfo::world_height - Winfo::height;
	return coords; // final camera coords
}
