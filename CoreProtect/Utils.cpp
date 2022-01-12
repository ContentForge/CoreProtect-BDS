#include "pch.h"
#include "utils.h"


void Utils::sqlExecute(const char* query, std::function<void(SQLite::Statement&)> callback)
{
	try
	{
		SQLite::Statement sm = SQLite::Statement(Utils::db, query);
		if (callback != NULL) callback(sm);
		else db.exec(query);
	}
	catch (SQLite::Exception ex)
	{
		std::cout << "Error: " << ex.getErrorStr() << " (" << ex.getErrorCode() << ")." << std::endl;
		std::cout << "Query: " << query << std::endl;
	}
}


int Utils::pagesCalculate(int maxId)
{
	int rem = maxId % 7;
	int pageCount = (maxId - rem) / 7;
	if (rem) pageCount += 1;
	return pageCount;
}


float Utils::getHoursAgo(float hours)
{
	int temp = hours * (10 * 10);
	return (float)temp / (10 * 10);
}