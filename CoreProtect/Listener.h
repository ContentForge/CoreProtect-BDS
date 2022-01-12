#pragma once
#include "pch.h"
#include "Dependencies.h"
#include "Utils.h"


namespace Listener
{
	bool playerPreJoin(Event::PlayerPreJoinEvent);
	bool playerPlaceBlock(Event::PlayerPlaceBlockEvent);
	bool playerDestroyBlock(Event::PlayerDestroyBlockEvent);
}