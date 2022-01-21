#include "pch.h"
#include "dependencies.h"
#include "listener.h"
#include "command.h"
#include "utils.h"


void plugin()
{
	CreateDirs("./plugins/CoreProtect/");
	Translation::load("./plugins/CoreProtect/language.json");

	Utils::sqlExecute("CREATE TABLE IF NOT EXISTS co_block(time INT DEFAULT(strftime('%s', 'now')), user INT, wid INT, xyz VARCHAR(255), block VARCHAR(255), action INT);");
	Utils::sqlExecute("CREATE TABLE IF NOT EXISTS co_user(id INTEGER PRIMARY KEY AUTOINCREMENT, nick VARCHAR(255), inspect INT DEFAULT 0, l_xyz VARCHAR(255) DEFAULT '-');");

	Event::PlayerPreJoinEvent::subscribe(Listener::playerPreJoin);           // Listener/PlayerPreJoin
	Event::PlayerPlaceBlockEvent::subscribe(Listener::playerPlaceBlock);     // Listener/Block/PlayerPlaceBlock
	Event::PlayerDestroyBlockEvent::subscribe(Listener::playerDestroyBlock); // Listener/Block/PlayerDestroyBlock

	Event::RegCmdEvent::subscribe([](Event::RegCmdEvent ev) {
		CoreProtect::setup(ev.mCommandRegistry);
		return true;
	});
}
