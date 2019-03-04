#pragma once
#include <string>
#include <vector>
//#include "Models.h"

class InventoryItemModel {
public:
	InventoryItemModel() {
		player_id = 0;
		mineral_id = 0;
		quantity = 0;
	}

	InventoryItemModel(int m_player_id, int m_mineral_id, int m_quantity) {
		player_id = m_player_id;
		mineral_id = m_mineral_id;
		quantity = m_quantity;
	}
	
	// usually we cannot access obj private attributes, but friend allows us to do so
	friend std::ostream& operator<<(std::ostream& os, const InventoryItemModel& obj)
	{
		os << obj.mineral_id << " (qty " << obj.quantity << ")";
		return os;
	}

	// Getters
	int getPlayerId() { return player_id; }
	int getMineralId() { return mineral_id; }
	int getQuantity() { return quantity; }


	// TODO: 
	// PlayerModel *getPlayerModel() { ... from id return player model }
	// MineralModel *getMineralModel() { ... from mineral id return mineral model }

private:
	int player_id;
	int mineral_id;
	int quantity;
};

class PlayerModel {
public:
	PlayerModel() {
		player_id = 0;
		drill_level = 0;
		engine_level = 0;
		fuel_tank_level = 0;
		backpack_level = 0;
		balance = 0;
		player_name = "undefined";
		health = 0;
	}

	PlayerModel(int id, int drill, int engine, int hull, int fuel_tank, int backpack, int balance, std::string name, int health, std::string json_map) {
		player_id = id;
		drill_level = drill;
		engine_level = engine;
		fuel_tank_level = fuel_tank;
		backpack_level = backpack;
		this->balance = balance;
		player_name = name;
		this->health = health;
	}

	PlayerModel(int id, int *upgrades, int balance, std::string name, int health, std::string json_map) {
		player_id = id;
		drill_level = upgrades[0];
		hull_level = upgrades[1];
		engine_level = upgrades[2];
		fuel_tank_level = upgrades[3];
		backpack_level = upgrades[4];

		this->balance = balance;
		player_name = name;
		this->health = health;
	}

	void setInventory(std::vector<InventoryItemModel> items) { inventory = items; }

	// Getters
	int getPlayerId() { return player_id; }
	int getUpgrade(const std::string upgrade_name) {
		// Like switch
		if (upgrade_name == "drill") return drill_level;
		else if (upgrade_name == "hull") return hull_level;
		else if (upgrade_name == "engine") return engine_level;
		else if (upgrade_name == "fuel tank" || upgrade_name == "fuel_tank") return fuel_tank_level;
		else if (upgrade_name == "backpack") return backpack_level;
		return 0;
	}
	int getBalance() { return balance; }
	std::string getPlayerName() { return player_name; }
	int getHealth() { return health; }
	std::string getMapJson() { return json_map; }
	//int getItemsCount() { return inventory.size(); }

	//std::vector<InventoryItemModel> getInventory() {
	//	if (inventory.size() != 0)
	//		return inventory;
	//	else { // inventory is not loaded, request for it!
	//		inventory = Models::getInstance()->getInventoryById(player_id);
	//		return inventory;
	//	} 
	//	return inventory;
	//	return Models::getInstance()->getInventoryById(player_id);
	//}

private:
	int player_id;
	int drill_level, hull_level, engine_level, fuel_tank_level, backpack_level;
	int balance;
	std::string player_name;
	int health;
	std::string json_map;
	std::vector<InventoryItemModel> inventory;
};

class MapModel {
public:
	MapModel(int player_id, std::string json_value) {
		this->player_id = player_id;
		this->json_value = json_value;
	}

	// Getters
	int getPlayerId() { return player_id; }
	std::string getJsonValue() { return json_value; }

	/// TODO: Need backward converstion to map
	// std::vector<std::vector<Mineral>> getMap() { return new std::vector<std::vector<Mineral>>() }
private:
	int player_id;
	std::string json_value;
};

class BuildingModel {
public:
	BuildingModel() {
		building_id = -1;
		building_name = "undifined";
		texture_path = "undefined";
		buildingX = buildingY = width = -1;
	}

	BuildingModel(int id, std::string name, std::string texture_path, int bX, int bY, int width) {
		building_id = id;
		building_name = name;
		this->texture_path = texture_path;
		buildingX = bX;
		buildingY = bY;
		this->width = width;
	}

	friend std::ostream& operator<<(std::ostream& os, const BuildingModel& obj)
	{
		os << obj.building_name << " (" << obj.building_id << ")";
		return os;
	}

	// Getters
	int getId() { return building_id; }
	std::string getName() { return building_name; }
	std::string getTexturePath() { return texture_path; }
	int getBuildingX() { return buildingX; }
	int getBuildingY() { return buildingY; }
	int getWidth() { return width; }

private:
	int building_id;
	std::string building_name;
	std::string texture_path;
	int buildingX, buildingY, width;
};

class UpgradeModel {
	// This model is being used by:
	// FuelTank, Backpack, Engine, Hull and Drill tables
public:
	// Constructors
	// UpgradeModel() { level = 0; name = "undefined", price = 0; value = 0.0f; }

	UpgradeModel(int mLevel, std::string mName, int mPrice, float mValue) {
		level = mLevel;
		name = mName;
		price = mPrice;
		value = mValue;
	}

	friend std::ostream& operator<<(std::ostream& os, const UpgradeModel& obj)
	{
		os << obj.name << " (" << obj.level << ")";
		return os;
	}

	// Getters
	int getLevel() { return level; };
	std::string getName() { return name; };
	int getPrice() { return price; };
	float getValue() { return value; };

	// Setters. We dont want to allow to change values!
private:
	int level;
	std::string name;
	int price;
	float value;
};

class MineralModel {
public:
	MineralModel(int id, std::string name, int price, int weight, int frequency, int strength, std::string texture_path) {
		mineral_id = id;
		mineral_name = name;
		this->price = price;
		this->weight = weight;
		this->frequency = frequency;
		this->strength = strength;
		this->texture_path = texture_path;
	}

	friend std::ostream& operator<<(std::ostream& os, const MineralModel& obj)
	{
		os << obj.mineral_name << " (" << obj.mineral_id << ")";
		return os;
	}

	// Getters
	int getId() { return mineral_id; }
	std::string getName() { return mineral_name; }
	int getPrice() { return price; }
	int getWeight() { return weight; }
	int getFrequency() { return frequency; }
	int getStrength() { return strength; }
	std::string getTexturePath() { return texture_path; }

	// Setters. We dont want to allow to change values!
private:
	int mineral_id;
	std::string mineral_name;
	int price;
	int weight;
	int frequency;
	int strength;
	std::string texture_path;
};
