#include "Models.h"
//#include "C:\Dev\Motherload\Motherload\Models.h"

/* null, it will be initialized on first call */
Models* Models::instance = 0;

Models* Models::getInstance() {
	if (instance == 0)
		instance = new Models(); // Constructor
	return instance;
}

Models::Models() {
	// Constructor
	qResult = sqlite3_open(Winfo::db_name.c_str(), &db);
	if (qResult)
		fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
	else
		fprintf(stderr, "Opened database successfully\n");
}

Models::~Models() {
	sqlite3_close(db); // closing database
	fprintf(stderr, "Database closed\n");
}

int Models::callback(void *data, int argc, char **argv, char **azColName) {
	// print one query feedback row
	for (int i = 0; i < argc; i++)
		printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
	printf("\n");
	return 0;
}

bool Models::queryFile(std::string query_file) {
	std::ifstream fd;
	try {
		fd.open(query_file);
		if (fd.is_open()) {
			std::string content((std::istreambuf_iterator<char>(fd)), std::istreambuf_iterator<char>());
			return queryString(content);
		}
	}
	catch (const std::exception& e) {
		printf(e.what());
	}
	// if it came to here -> then fail occured
	fd.close();
	return false;
}

bool Models::queryString(std::string sql) {
	// REFERENCE BEGIN: https://www.tutorialspoint.com/sqlite/sqlite_c_cpp.htm
	char *errorMsg = "Query error";
	qResult = sqlite3_exec(db, sql.c_str(), Models::callback, 0, &errorMsg); // execution
	if (qResult != SQLITE_OK) {
		fprintf(stderr, "SQL error: %s\n", errorMsg);
		sqlite3_free(errorMsg);
	}
	else {
		fprintf(stdout, "Query established successfully\n");
		return true;
	}
	// REFERENCE END;
	return false;
}

UpgradeModel Models::getUpgradeById(std::string upgradeTable, int id) {
	try {
		sqlite::sqlite mdb(Winfo::db_name.c_str());
		std::string query = "SELECT * FROM " + upgradeTable + " WHERE level = " + std::to_string(id) + ";";
		auto cur = mdb.get_statement();
		int price;
		double value;
		std::string name;

		cur->set_sql(query);
		cur->prepare();

		while (cur->step()) {
			name = cur->get_text(1);
			price = cur->get_int(2);
			value = cur->get_double(3);
		}
		return UpgradeModel(id, name, price, (float)value);
	}
	catch (sqlite::exception e) {
		std::cerr << e.what() << std::endl;
		return UpgradeModel(id, upgradeTable, 0, 0.0f);
	}
}

PlayerModel Models::getPlayerById(int id) {
	try {
		sqlite::sqlite mdb(Winfo::db_name.c_str());
		std::string query = "SELECT * FROM (Player INNER JOIN Map ON Player.player_id=Map.player_id) WHERE Player.player_id=" + std::to_string(id) + ";";
		auto cur = mdb.get_statement();

		int *upgrades = new int[5];
		int balance = 0, health = 0;
		std::string name, json_map;

		cur->set_sql(query);
		cur->prepare();

		while (cur->step()) {
			for (int i = 0; i < 5; i++) {
				upgrades[i] = cur->get_int(i + 1);
			}
			balance = cur->get_int(6);
			name = cur->get_text(7);
			health = cur->get_int(8);
			json_map = cur->get_text(10);
		}
		PlayerModel p1(id, upgrades, balance, name, health, json_map);
		p1.setInventory(getInventoryById(id));
		return p1;
	}
	catch (sqlite::exception e) {
		std::cerr << e.what() << std::endl;
		return PlayerModel(0, new int[1], 0, "undefined", 0, "[]");
	}
}

MineralModel Models::getMineralById(int id) {
	try {
		sqlite::sqlite mdb(Winfo::db_name.c_str());
		std::string query = "SELECT * FROM Mineral WHERE mineral_id = " + std::to_string(id) + ";";
		auto cur = mdb.get_statement();

		std::string name, tex_path;
		int *attr = new int[4]; // price, weight, frequency, strength

		cur->set_sql(query);
		cur->prepare();

		while (cur->step()) {
			name = cur->get_text(1); // mineral_name
			for (int i = 0; i < 4; i++)
				attr[i] = cur->get_int(i + 2);
		}
		return MineralModel(id, name, attr[0], attr[1], attr[2], attr[3], tex_path);
	}
	catch (sqlite::exception e) {
		std::cerr << e.what() << std::endl;
		return MineralModel(id, "undefined", 0, 0, 0, 0, "undefined");
	}
}

MineralModel Models::getMineralByName(std::string name) {
	name[0] = toupper(name[0]);
	try {
		sqlite::sqlite mdb(Winfo::db_name.c_str());
		std::string query = "SELECT * FROM Mineral WHERE mineral_name = '" + name + "';";
		auto cur = mdb.get_statement();
		int id = 0;
		bool hasResults = false;

		cur->set_sql(query);
		cur->prepare();

		while (cur->step()) {
			id = cur->get_int(0); // id
			hasResults = true;
		}
		if (hasResults)
			return this->getMineralById(id);
		else
			return MineralModel(0, "undefined", 0, 0, 0, 0, "undefined");
	}
	catch (sqlite::exception e) {
		std::cerr << e.what() << std::endl;
		return MineralModel(0, "undefined", 0, 0, 0, 0, "undefined");
	}
}

BuildingModel Models::getBuildingById(int id) {
	try {
		sqlite::sqlite mdb(Winfo::db_name.c_str());
		std::string query = "SELECT * FROM Building WHERE building_id = " + std::to_string(id) + ";";
		auto cur = mdb.get_statement();
		bool hasResults = false;
		std::string name, tex_path;
		int bX, bY, width;

		cur->set_sql(query);
		cur->prepare();

		while (cur->step()) {
			name = cur->get_text(1);
			tex_path = cur->get_text(2);
			bX = cur->get_int(3);
			bY = cur->get_int(4);
			width = cur->get_int(5);
			hasResults = true;
		}
		if (hasResults)
			return BuildingModel(id, name, tex_path, bX, bY, width);
		else
			return BuildingModel();
	}
	catch (sqlite::exception e) {
		std::cerr << e.what() << std::endl;
		return BuildingModel();
	}
}

std::vector<InventoryItemModel> Models::getInventoryById(int player_id) {
	std::vector<InventoryItemModel> items;
	try {
		sqlite::sqlite mdb(Winfo::db_name.c_str());
		std::string query = "SELECT mineral_id, quantity FROM InventoryItems WHERE player_id = "
			+ std::to_string(player_id) + ";";
		auto cur = mdb.get_statement();
		int mineral_id, quantity; // vars to save row results

		cur->set_sql(query);
		cur->prepare();

		while (cur->step()) {
			mineral_id = cur->get_int(0);
			quantity = cur->get_int(1);
			items.push_back(InventoryItemModel(player_id, mineral_id, quantity));
		}
		return items;
	}
	catch (sqlite::exception e) {
		std::cerr << e.what() << std::endl;
		return items;
	}
}