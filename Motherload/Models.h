#pragma once
#include "sqlite3.h"
#include "mysqlite.hpp"
#include "StaticVars.h"
#include "ModelObjects.h"
#include <fstream>
#include <streambuf>
#include <stdio.h>
#include <iostream>
#include <vector>

// summary:
//		Class that acts like PROXY(only DB access point) as well as 
//		SINGLETON(single object) and handles database queries
// remarks:
//		Every request(get method) returns Model Object(s)
// author:
//		barkausa
class Models {
public:
	// ----------- Singleton based instance -----------
	static Models *getInstance();
	// ----------- Deconstructor -----------
	~Models();

	// ----------- Basic query excutions -----------

	// summary:
	//		Executes SQL from given file
	bool queryFile(std::string query_file);

	// summary:
	//		Executes SQL from given string(arg)
	bool queryString(std::string sql);

	// ----------- Getters (funcs grabs data from database) -----------
	UpgradeModel getUpgradeById(std::string upgradeTable, int id);
	PlayerModel getPlayerById(int id);
	MineralModel getMineralById(int id);
	MineralModel getMineralByName(std::string name);
	BuildingModel getBuildingById(int id);
	std::vector<InventoryItemModel> getInventoryById(int player_id);

	inline void savePlayerAndInventory(PlayerModel *p) { 
		savePlayer(p);
		saveInventory(p);
	};

	// summary:
	//		Saves player status/upgrades to DB
	// param:
	//		p: Player to save
	void savePlayer(PlayerModel *p);

	// summary:
	//		Saves player inventory to DB
	// param:
	//		p: Player to save
	void saveInventory(PlayerModel *p);
private:
	Models();
	static Models* instance;
	sqlite3 *db;
	int qResult;	// query status

	// summary:
	//		Prints in Console SELECT output
	// remarks:
	//		Works only with funcs: queryFile or queryString
	static int callback(void *data, int argc, char **argv, char **azColName);
};