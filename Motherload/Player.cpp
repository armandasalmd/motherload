#pragma once
#include "Player.h"

void Player::Step(const int dx, const int dy) {
	if (mx + dx >= 0 && mx + dx + Winfo::block_size < WorldInfo::world_width)
		Move(dx, 0); // camera position regulation on the screen function
	if (my + dy >= 0 && my + dy + Winfo::block_size < WorldInfo::world_height)
		Move(0, dy); // camera position regulation on the screen function
}

void Player::SetCoords(int x, int y) {
	// function do not let to pass the edge
	if (x <= (WorldInfo::b_world_width - 1) * Winfo::block_size && x >= 0)
		positionX = x;
	else if (x < 0)
		positionX = 0;
	else if (x > (WorldInfo::b_world_width - 1) * Winfo::block_size)
		positionX = (WorldInfo::b_world_width - 1) * Winfo::block_size;

	if (y <= (WorldInfo::b_world_height - 2) * Winfo::block_size && y >= 0)
		positionY = y;
	else if (y < 0)
		positionY = 0;
	else if (y > (WorldInfo::b_world_height - 2) * Winfo::block_size)
		positionY = (WorldInfo::b_world_height - 2) * Winfo::block_size;
}