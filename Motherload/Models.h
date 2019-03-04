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


#ifndef MODEL_DATABASE_FILENAME
#define MODEL_DATABASE_FILENAME Winfo::db_name
#endif

class Models {

public:
	static Models *getInstance();
	~Models();

	bool queryFile(std::string query_file);
	bool queryString(std::string sql);

	UpgradeModel getUpgradeById(std::string upgradeTable, int id);
	PlayerModel getPlayerById(int id);
	MineralModel getMineralById(int id);
	MineralModel getMineralByName(std::string name);
	BuildingModel getBuildingById(int id);
	std::vector<InventoryItemModel> getInventoryById(int player_id);

private:
	Models();
	static Models* instance;
	sqlite3 *db;
	int qResult; // query result

	static int callback(void *data, int argc, char **argv, char **azColName);
};

//
//#define MODELS_DATABASE_FILENAME "mockdatabase.sqlite"
//#include "Models.h"
//
//
//TEST_CASE()
//{
//	Models( "mockdatabase.sqlite" )
//	{}
//}