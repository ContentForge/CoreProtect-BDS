#include "pch.h"
#include "Events.h"
#include "Command.h"

Logger logger;


void PlugInit()
{
	Translation::load("./plugins/CoreProtect/langs/en_en.json");

	Event::PlayerDestroyBlockEvent::subscribe(DestroyBlock);
	Event::PlayerPlaceBlockEvent::subscribe(PlaceBlock);

	Event::RegCmdEvent::subscribe([](Event::RegCmdEvent ev)
		{
			CoreProtect::setup(ev.mCommandRegistry);
			return true;
		}
	);
}