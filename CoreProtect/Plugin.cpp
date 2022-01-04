#include "pch.h"
#include "Events.h"
#include "Command.h"


void plugin()
{
	Event::ServerStartedEvent::subscribe(serverStarted);
	Event::PlayerDestroyBlockEvent::subscribe(destroyBlock);
	Event::PlayerPlaceBlockEvent::subscribe(placeBlock);

	Event::RegCmdEvent::subscribe([](Event::RegCmdEvent ev)
		{
			CoreProtect::setup(ev.mCommandRegistry);
			return true;
		}
	);
}