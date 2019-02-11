#pragma once
#include "Camera.h"
#include <iostream>

Camera::Camera(Game *game,  Player *player, TextureObject *background) {
	this->game = game;
	this->player = player;
	this->background = background;
}

void Camera::UpdateAll() {
	// this function calculates coordinates for required objects
	int *cCoords = calcCameraCoordinates();
	int new_player_x = (Winfo::width - Winfo::block_size) / 2, new_player_y = Winfo::height / 5 + Winfo::block_size / 2;

	if (cCoords[0] <= 0)
		new_player_x = player->PosX();
	else if (cCoords[0] >= WorldInfo::world_width - Winfo::width)
		new_player_x = Winfo::width + player->PosX() - WorldInfo::world_width;
	if (cCoords[1] - 64 <= 0)
		new_player_y = player->PosY();
	else if (cCoords[1] >= WorldInfo::world_height - Winfo::height)
		new_player_y = Winfo::height + player->PosY() - WorldInfo::world_height + Winfo::block_size;
	// TODO: and need to add y axis bottom border!
	player->SetDrawCoords(new_player_x, new_player_y);
	player->Update();
	background->SetOffset(cCoords[0], cCoords[1]);
	background->Update();
}

void Camera::RenderBg() {
	background->Render();
}
void Camera::RenderPlayer() {
	player->Render();
}

int *Camera::calcCameraCoordinates() {
	// Definitions
	int *coords = new int[2]{ 0, 0 };
	// Solving part
	// x-axis player is in the middle
	// y-axis player is in 1/5 of the top
	int *playerCoords = new int[2]{player->PosX() + Winfo::block_size / 2, player->PosY() + Winfo::block_size / 2 };
	coords[0] = playerCoords[0] - Winfo::width / 2;
	coords[1] = playerCoords[1] - Winfo::height / 5;
	if (coords[0] < 0)
		coords[0] = 0;
	if (coords[0] > WorldInfo::world_width - Winfo::width)
		coords[0] = WorldInfo::world_width - Winfo::width;
	if (coords[1] < 0)
		coords[1] = 0;
	if (coords[1] > WorldInfo::world_height - Winfo::height)
		coords[1] = WorldInfo::world_height - Winfo::height;
	// End of function
	//cam.x = coords[0];\cam.y = coords[1];
	return coords;
}
