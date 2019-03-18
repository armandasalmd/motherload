#pragma once
#include "Player.h"

void Player::SetCoords(int x, int y) {
	// summary:
	//		allows to set x and y coordinate if it dont exceed map limits
	//		if fails, then sets closiest possible.
	//		this function always keeps player in the map
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
	// send request to database, and save player information
	pModel = Models::getInstance()->getPlayerById(player_id);
}

void Player::savePlayerModel() { 
	// save player and inventory to database
	Models::getInstance()->savePlayerAndInventory(&pModel);
}

PlayerModel Player::getPlayerModel() {
	return pModel;
}

void Player::addMineralToInv(Mineral item) {	
	// temp solution: string[] - block id has to be Mineral class
	std::string blocks[] = {"sky", "grass", "dirt", "stone", "bronze", "silver", 
							"iron", "gold", "ruby", "emerald", "diamond"};
	int minId = -1; // mineralId
	for (int i = 0; i < 11; i++)
		if (blocks[i] == item.getName()) {
			minId = i; // match found
			break;	   // stop the loop
		}
	if (minId >= 3 && minId <= 10) { 
		// if not sky, grass, dirt: add it to inventory
		InventoryItemModel iModel(pModel.getPlayerId(), minId, 1); // object to add
		std::cout << "Adding: " << iModel.getMineralId() << std::endl;
		pModel.addItem(iModel);
	}
}