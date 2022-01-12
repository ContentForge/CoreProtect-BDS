#pragma once
#include "pch.h"
#include "dependencies.h"
#include "utils.h"


namespace Listener
{
	bool playerPreJoin(Event::PlayerPreJoinEvent);
	bool playerPlaceBlock(Event::PlayerPlaceBlockEvent);
	bool playerDestroyBlock(Event::PlayerDestroyBlockEvent);
}
