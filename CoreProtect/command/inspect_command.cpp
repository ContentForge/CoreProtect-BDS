#include "../pch.h"
#include "../command.h"


void CoreProtect::inspectCommand(ServerPlayer* pl) const
{
	Utils::sqlExecute(std::string("SELECT * FROM co_user WHERE nick = '" + pl->getName() + "';").c_str(), [&](SQLite::Statement& sm) {
		if (sm.executeStep())
		{
			if (!sm.getColumn("inspect").getInt())
			{
				Utils::sqlExecute(std::string("UPDATE co_user SET inspect = 1 WHERE nick = '" + pl->getName() + "';").c_str());
				pl->sendText(tr("INSPECTOR_TOGGLED", "enabled"));
			}
			else
			{
				Utils::sqlExecute(std::string("UPDATE co_user SET inspect = 0, l_xyz = '-' WHERE nick = '" + pl->getName() + "';").c_str());
				pl->sendText(tr("INSPECTOR_TOGGLED", "disabled"));
			}
		}
	});
}
