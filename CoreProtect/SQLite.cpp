#include "pch.h"
//#include "SQLite.h"
//
//
//void executeSql(std::string const& database, const char* command, int(*callback)(void*, int, char**, char**), Player* player)
//{
//	sqlite3* db;
//	std::string path = "./plugins/CoreProtect/databases/" + database + ".db";
//	sqlite3_open(path.c_str(), &db);
//
//	if (callback != nullptr)
//	{
//		sqlite3_exec(db, command, callback, (void*)player, 0);
//	}
//	else sqlite3_exec(db, command, 0, 0, 0);
//
//	sqlite3_close(db);
//}