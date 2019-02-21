#include "Models.h"


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

template <typename T> // Model class
bool Models::insert(std::string table_name, T model) {
	return true;
}