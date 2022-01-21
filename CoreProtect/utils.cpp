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
	int remainder = maxId % 7;
	int pageCount = (maxId - remainder) / 7;
	if (remainder) pageCount += 1;
	return pageCount;
}


std::string Utils::timestampFormat(std::chrono::system_clock const& sc, __time64_t const timestamp)
{
	int difference = (int)(sc.to_time_t(sc.now()) - timestamp);

	if (difference < 60) return std::to_string((int)difference) + "/s";
	else if (difference < 3600)
	{
		if ((float)((int)(difference / 60.0 * 100)) / 100 == (int)(difference / 60)) return std::to_string((int)(difference / 60)) + "/m";
		else
		{
			std::string minutes = std::to_string(difference / 60.0);
			return minutes.erase(minutes.size() - (minutes.size() - (minutes.find(".") + 1)) + 2, 4) + "/m";
		}
	}
	else if (difference < 86400)
	{
		if ((float)((int)(difference / 3600.0 * 100)) / 100 == (int)(difference / 3600)) return std::to_string((int)(difference / 3600)) + "/h";
		else
		{
			std::string hours = std::to_string(difference / 3600.0);
			return hours.erase(hours.size() - (hours.size() - (hours.find(".") + 1)) + 2, 4) + "/h";
		}
	}
	else
	{
		if ((float)((int)(difference / 86400.0 * 100)) / 100 == (int)(difference / 86400)) return std::to_string((int)(difference / 86400)) + "/d";
		else
		{
			std::string hours = std::to_string(difference / 86400.0);
			return hours.erase(hours.size() - (hours.size() - (hours.find(".") + 1)) + 2, 4) + "/d";
		}
	}
}
