#include "pch.h"
#include "SQLite.h"


void executeSql(std::string const& database, const char* command)
{
	sqlite3* db;
	std::string path = "./plugins/CoreProtect/databases/" + database + ".db";
	sqlite3_open(path.c_str(), &db);
	sqlite3_exec(db, command, 0, 0, 0);
	sqlite3_close(db);
}