#include "pch.h"
#include "dependencies.h"
#include "listener.h"
#include "command.h"
#include "utils.h"


void plugin()
{
	CreateDirs("./plugins/CoreProtect/");
	Translation::load("./plugins/CoreProtect/language.json");

	Utils::sqlExecute("CREATE TABLE IF NOT EXISTS co_block(id INTEGER PRIMARY KEY AUTOINCREMENT, user INT, xyz VARCHAR(255), block VARCHAR(255), action INT, time INT);");
	Utils::sqlExecute("CREATE TABLE IF NOT EXISTS co_user(id INTEGER PRIMARY KEY AUTOINCREMENT, nick VARCHAR(255), inspect INT DEFAULT 0, l_xyz VARCHAR(255) DEFAULT '-', l_id INT DEFAULT -1, l_idn INT DEFAULT -1, l_pages INT DEFAULT -1, l_page INT DEFAULT 1);");

	Event::PlayerPreJoinEvent::subscribe(Listener::playerPreJoin);           // Listener/PlayerPreJoin
	Event::PlayerPlaceBlockEvent::subscribe(Listener::playerPlaceBlock);     // Listener/Block/PlayerPlaceBlock
	Event::PlayerDestroyBlockEvent::subscribe(Listener::playerDestroyBlock); // Listener/Block/PlayerDestroyBlock

	Event::RegCmdEvent::subscribe([](Event::RegCmdEvent ev) {
		CoreProtect::setup(ev.mCommandRegistry);
		return true;
	});
}