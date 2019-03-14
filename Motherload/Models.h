// <summary>Class that acts like PROXY(only DB access point) as well as 
//		SINGLETON(single object) and handles database queries</summary>
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
	// __________ Singleton based instance __________
	static Models *getInstance();
	// __________ Deconstructor __________
	~Models();

	// __________ Basic query excutions __________
	/* <summary>Executes SQL from given file</summary> */
	bool queryFile(std::string query_file);
	/* <summary>Executes SQL from given string(arg)</summary> */
	bool queryString(std::string sql);

	// __________ Getters (funcs grabs data from database) __________
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
	/*
	<summary>Saves player status/upgrades to DB</summary>
	<param name="p">Player to save</param>
	*/
	void savePlayer(PlayerModel *p);
	/*
	<summary>Saves player inventory to DB</summary>
	<param name="p">Player to save</param>
	*/
	void saveInventory(PlayerModel *p);
private:
	Models();
	static Models* instance;
	sqlite3 *db;
	int qResult;	// query status
	/* 
	<summary>Prints in Console SELECT output</summary>
	<remarks>Works only with funcs: queryFile or queryString</remarks>
	*/
	static int callback(void *data, int argc, char **argv, char **azColName);
};