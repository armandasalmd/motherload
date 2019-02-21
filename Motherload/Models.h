#pragma once
#include "sqlite3.h"
#include "StaticVars.h"
#include <fstream>
#include <streambuf>
#include <stdio.h>

class Models {

public:
	static Models *getInstance();
	~Models();

	bool queryFile(std::string query_file);
	bool queryString(std::string sql);

	template <typename T> // Model class
	bool insert(std::string table_name, T model);

private:
	Models();
	static Models* instance;
	sqlite3 *db;
	int qResult; // query result

	static int callback(void *data, int argc, char **argv, char **azColName);
};