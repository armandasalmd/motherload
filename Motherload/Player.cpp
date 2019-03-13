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

void Player::loadPlayerModel(int player_id) {
	pModel = Models::getInstance()->getPlayerById(player_id);
}

void Player::savePlayerModel() { // save to database
	Models::getInstance()->queryString("DELETE FROM Inventory WHERE player_id = " 
		+ std::to_string(pModel.getPlayerId()) + ";"); // deletes old values
	if (pModel.getItemsCount() > 0) { // if inventory not empty
		std::string sql = "INSERT INTO Inventory VALUES ";
		std::vector<InventoryItemModel> *newItems = pModel.getInventory();
		std::vector<InventoryItemModel>::iterator end = newItems->end();
		for (std::vector<InventoryItemModel>::iterator it = newItems->begin(); it != end; it++)
			sql += "(" + std::to_string(it->getPlayerId()) + "," + std::to_string(it->getMineralId()) + ","
				+ std::to_string(it->getQuantity()) + "),";
		sql.pop_back(); // pop last comma
		sql.push_back(';'); // add ;
		Models::getInstance()->queryString(sql);
		//std::cout << sql << std::endl;
	}
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