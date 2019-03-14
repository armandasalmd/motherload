#include "ModelObjects.h"
#include "Models.h" // Dont move to header!

/*
___________ START Model Constructors __________
*/
InventoryItemModel::InventoryItemModel() {
	player_id = 0;
	mineral_id = 0;
	quantity = 0;
}

InventoryItemModel::InventoryItemModel(int m_player_id, int m_mineral_id, int m_quantity) {
	player_id = m_player_id;
	mineral_id = m_mineral_id;
	quantity = m_quantity;
}

PlayerModel::PlayerModel() {
	player_id = 0;
	drill_level = 0;
	engine_level = 0;
	fuel_tank_level = 0;
	backpack_level = 0;
	balance = 0;
	player_name = "undefined";
	health = 0;
}

PlayerModel::PlayerModel(int id, int drill, int engine, int hull, int fuel_tank, int backpack, int balance, std::string name, int health, std::string json_map) {
	player_id = id;
	drill_level = drill;
	engine_level = engine;
	fuel_tank_level = fuel_tank;
	backpack_level = backpack;
	this->balance = balance;
	player_name = name;
	this->health = health;
}

PlayerModel::PlayerModel(int id, int *upgrades, int balance, std::string name, int health, std::string json_map) {
	player_id = id;
	drill_level = upgrades[0];
	hull_level = upgrades[1];
	engine_level = upgrades[2];
	fuel_tank_level = upgrades[3];
	backpack_level = upgrades[4];
	this->json_map = json_map;
	this->balance = balance;
	player_name = name;
	this->health = health;
}

MapModel::MapModel(int player_id, std::string json_value) {
	this->player_id = player_id;
	this->json_value = json_value;
}

BuildingModel::BuildingModel() {
	building_id = -1;
	building_name = "undifined";
	texture_path = "undefined";
	buildingX = buildingY = width = -1;
}
BuildingModel::BuildingModel(int id, std::string name, std::string texture_path, int bX, int bY, int width) {
	building_id = id;
	building_name = name;
	this->texture_path = texture_path;
	buildingX = bX;
	buildingY = bY;
	this->width = width;
}

UpgradeModel::UpgradeModel() { level = 0; name = "undefined", price = 0; value = 0.0f; }
UpgradeModel::UpgradeModel(int mLevel, std::string mName, int mPrice, float mValue) {
	level = mLevel;
	name = mName;
	price = mPrice;
	value = mValue;
}

MineralModel::MineralModel() {}
MineralModel::MineralModel(int id, std::string name, int price, int weight, int frequency, int strength, std::string texture_path) {
	mineral_id = id;
	mineral_name = name;
	this->price = price;
	this->weight = weight;
	this->frequency = frequency;
	this->strength = strength;
	this->texture_path = texture_path;
}
/*
___________ END Model Constructors __________
*/

int PlayerModel::getItemsCount() { 
	return (*getInventory()).size();
}

std::vector<InventoryItemModel> *PlayerModel::getInventory() {
	if (inventory.size() != 0)
		return &inventory;
	else { // inventory is not loaded, request for it!
		inventory = Models::getInstance()->getInventoryById(player_id);
		return &inventory;
	}
}

void PlayerModel::addItem(InventoryItemModel item) {
	if (getItemsCount() == 0)
		getInventory();		// updates if empty
	inventory.push_back(item);
}