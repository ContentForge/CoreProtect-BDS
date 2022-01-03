#pragma once
#include "pch.h"
#include "Events.h"

bool DestroyBlock(Event::PlayerDestroyBlockEvent ev)
{
	Player* pl = ev.mPlayer;
	Block* bl = ev.mBlockInstance.getBlock();

	if (!pl->hasTag("inspector"))
	{
		std::string command = "INSERT INTO `blocks`(`BlockType`, `PlayerNick`, `Action`) VALUES('" + bl->getTypeName() + "', '" + pl->getName() + "', '" + "removed');";
		//ExecuteSQL("core_protect", command.c_str());

		return true;
	}
	else
	{
		return false;
	}
}


bool PlaceBlock(Event::PlayerPlaceBlockEvent ev)
{
	Player* pl = ev.mPlayer;
	Block* bl = ev.mBlockInstance.getBlock();

	if (!pl->hasTag("inspector"))
	{
		std::string command = "INSERT INTO `blocks`(`BlockType`, `PlayerNick`, `Action`) VALUES('" + bl->getTypeName() + "', '" + pl->getName() + "', '" + "placed');";
		//ExecuteSQL("core_protect", command.c_str());

		return true;
	}
	else
	{
		return false;
	}
}