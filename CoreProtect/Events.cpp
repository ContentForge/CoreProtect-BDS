#include "pch.h"
#include "Events.h"


bool serverStarted(Event::ServerStartedEvent ev)
{
	CreateDirs("./plugins/CoreProtect/databases/");
	executeSql("blocks", "CREATE TABLE IF NOT EXISTS blocks(ID INTEGER PRIMARY KEY AUTOINCREMENT, BlockType VARCHAR(255), PlayerNick VARCHAR(255), Action VARCHAR(255), Date DATE NOT NULL DEFAULT(date('now', 'localtime')), Time TIME NOT NULL DEFAULT(time('now', 'localtime')));");
	return true;
}


bool destroyBlock(Event::PlayerDestroyBlockEvent ev)
{
	Player* pl = ev.mPlayer;
	Block* bl = ev.mBlockInstance.getBlock();

	if (!pl->hasTag("inspect"))
	{
		std::string command = "INSERT INTO `blocks`(`BlockType`, `PlayerNick`, `Action`) VALUES('" + bl->getTypeName() + "', '" + pl->getName() + "', '" + "removed');";
		executeSql("blocks", command.c_str());
		return true;
	}
	else
	{
		return false;
	}
}

bool placeBlock(Event::PlayerPlaceBlockEvent ev)
{
	Player* pl = ev.mPlayer;
	Block* bl = ev.mBlockInstance.getBlock();

	if (!pl->hasTag("inspect"))
	{
		std::string command = "INSERT INTO `blocks`(`BlockType`, `PlayerNick`, `Action`) VALUES('" + bl->getTypeName() + "', '" + pl->getName() + "', '" + "placed');";
		executeSql("blocks", command.c_str());
		return true;
	}
	else
	{
		return false;
	}
}