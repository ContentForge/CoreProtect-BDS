#pragma once
#include "pch.h"


namespace Utils
{
	static SQLite::Database db = SQLite::Database("./plugins/CoreProtect/database.db", SQLite::OPEN_READWRITE + SQLite::OPEN_CREATE);

	void sqlExecute(const char*, std::function<void(SQLite::Statement&)> = NULL);
	int pagesCalculate(int);
	float getHoursAgo(float hours);
}
