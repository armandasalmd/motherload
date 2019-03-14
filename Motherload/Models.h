// <summary>Class that acts like proxy and handles database queries</summary>
// <remarks>Every request(get method) returns Model Object(s)</remarks>
// <author>barkausa</author>

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

class Models {

public:
	// Singleton based instance
	static Models *getInstance();
	// Deconstructor
	~Models();

	// Basic query excutions
	bool queryFile(std::string query_file);
	bool queryString(std::string sql);

	// Getters (funcs grabs data from database)
	UpgradeModel getUpgradeById(std::string upgradeTable, int id);
	PlayerModel getPlayerById(int id);
	MineralModel getMineralById(int id);
	MineralModel getMineralByName(std::string name);
	BuildingModel getBuildingById(int id);
	std::vector<InventoryItemModel> getInventoryById(int player_id);

	/// TODO: void savePlayerAndInventory();
private:
	Models();
	static Models* instance;
	sqlite3 *db;
	int qResult;	// query status
	// Function: Console print out SELECT output
	static int callback(void *data, int argc, char **argv, char **azColName);
};