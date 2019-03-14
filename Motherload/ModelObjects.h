// <summary>every class represents a table in database - table models</summary>
// <remarks>all models has custom printing func (operator<<)</remarks>
// <author>barkausa</author>

#pragma once
#include <string>
#include <vector>

// (prototype) Cyclic dependency between Models and ModelObjects
class Models;

class InventoryItemModel {
public:
	// __________ Constructors __________
	InventoryItemModel();
	InventoryItemModel(int m_player_id, int m_mineral_id, int m_quantity);
	
	// __________ COUT class __________
	friend std::ostream& operator<<(std::ostream& os, const InventoryItemModel& obj)
	{
		os << obj.mineral_id << " (qty " << obj.quantity << ")";
		return os;
	}

	// __________ Getters __________
	inline int getPlayerId() { return player_id; }
	inline int getMineralId() { return mineral_id; }
	inline int getQuantity() { return quantity; }

private:
	// Table attributes
	int player_id;
	int mineral_id;
	int quantity;
};

class PlayerModel {
public:
	// __________ Constructors __________
	PlayerModel();
	PlayerModel(int id, int drill, int engine, int hull, int fuel_tank, int backpack, 
		int balance, std::string name, int health, std::string json_map);
	PlayerModel(int id, int *upgrades, int balance, std::string name, int health, std::string json_map);

	// __________ Setters __________
	void setInventory(std::vector<InventoryItemModel> items) { inventory = items; }

	// __________ Getters __________
	inline int getPlayerId() { return player_id; }
	inline int getBalance() { return balance; }
	inline std::string getPlayerName() { return player_name; }
	inline int getHealth() { return health; }
	inline std::string getMapJson() { return json_map; }
	int getItemsCount();	// Current inventory item count
	std::vector<InventoryItemModel> *getInventory();
	
	/* 
	<param name="upgrade_name">selecting specific upgrade</param>
	<returns>Returns requested upgrade level(int)</returns> 
	*/
	int getUpgrade(const std::string upgrade_name) {
		if (upgrade_name == "drill") return drill_level;
		else if (upgrade_name == "hull") return hull_level;
		else if (upgrade_name == "engine") return engine_level;
		else if (upgrade_name == "fuel tank" || upgrade_name == "fuel_tank") return fuel_tank_level;
		else if (upgrade_name == "backpack") return backpack_level;
		return 0;
	}

	// __________ Control funcs __________
	/* 
	<summary>adds mined block to player's inventory</summary>
	<param name="item">mined block model</param> 
	*/
	void addItem(InventoryItemModel item);
private:
	// Table attributes
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
	// __________ Constructors __________
	MapModel(int player_id, std::string json_value);

	// __________ Getters __________
	inline int getPlayerId() { return player_id; }
	inline std::string getJsonValue() { return json_value; }

	/// TODO: Need backward converstion to map
	// std::vector<std::vector<Mineral>> getMap() { return new std::vector<std::vector<Mineral>>() }
private:
	// Table attributes
	int player_id;
	std::string json_value;
};

class BuildingModel {
public:
	// __________ Constructors __________
	BuildingModel();
	BuildingModel(int id, std::string name, std::string texture_path, int bX, int bY, int width);

	// __________ COUT class __________
	friend std::ostream& operator<<(std::ostream& os, const BuildingModel& obj)
	{
		os << obj.building_name << " (" << obj.building_id << ")";
		return os;
	}

	// __________ Getters __________
	inline int getId() { return building_id; }
	inline std::string getName() { return building_name; }
	inline std::string getTexturePath() { return texture_path; }
	inline int getBuildingX() { return buildingX; }
	inline int getBuildingY() { return buildingY; }
	inline int getWidth() { return width; }
private:
	// Table attributes
	int building_id;
	std::string building_name;
	std::string texture_path;
	int buildingX, buildingY, width;
};

class UpgradeModel {
	// This model is being used by:
	// FuelTank, Backpack, Engine, Hull and Drill tables
public:
	// __________ Constructors __________
	UpgradeModel();
	UpgradeModel(int mLevel, std::string mName, int mPrice, float mValue);

	// __________ COUT class __________
	friend std::ostream& operator<<(std::ostream& os, const UpgradeModel& obj)
	{
		os << obj.name << " (" << obj.level << ")";
		return os;
	}

	// __________ Getters __________
	inline int getLevel() { return level; };
	inline std::string getName() { return name; };
	inline int getPrice() { return price; };
	inline float getValue() { return value; };
private:
	// Table attributes
	int level;
	std::string name;
	int price;
	float value;
};

class MineralModel {
public:
	// __________ Constructors __________
	MineralModel();
	MineralModel(int id, std::string name, int price, int weight, int frequency, int strength, std::string texture_path);
	
	// __________ COUT class __________
	friend std::ostream& operator<<(std::ostream& os, const MineralModel& obj)
	{
		os << obj.mineral_name << " (" << obj.mineral_id << ")";
		return os;
	}

	// __________ Getters __________
	inline int getId() { return mineral_id; }
	inline std::string getName() { return mineral_name; }
	inline int getPrice() { return price; }
	inline int getWeight() { return weight; }
	inline int getFrequency() { return frequency; }
	inline int getStrength() { return strength; }
	inline std::string getTexturePath() { return texture_path; }
private:
	// Table attributes
	int mineral_id;
	std::string mineral_name;
	int price;
	int weight;
	int frequency;
	int strength;
	std::string texture_path;
};
