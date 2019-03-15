#pragma once
#include "Player.h"

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

void Player::loadPlayerModel(int player_id) {
	pModel = Models::getInstance()->getPlayerById(player_id);
}

void Player::savePlayerModel() { // save to database
	Models::getInstance()->savePlayerAndInventory(&pModel);
}

PlayerModel Player::getPlayerModel() {
	return pModel;
}

void Player::addMineralToInv(Mineral item) {	
	// temp solution: string[] - block id has to be Mineral class
	std::string blocks[] = {"sky", "grass", "dirt", "stone", "bronze", "silver", "iron", "gold", "ruby", "emerald", "diamond"};
	int minId = -1; // mineralId
	for (int i = 0; i < 11; i++)
		if (blocks[i] == item.getName()) {
			minId = i; // match found
			break; // stop for loop
		}
	if (minId >= 3 && minId <= 10) { // if not sky, grass, dirt
		InventoryItemModel iModel(pModel.getPlayerId(), minId, 1);
		std::cout << "Adding: " << iModel.getMineralId() << std::endl;
		pModel.addItem(iModel);
		//std::cout << pModel.getItemsCount() << std::endl;
	}
}