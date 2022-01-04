#pragma once
#include "pch.h"
#include "SQLite.h"


bool destroyBlock(Event::PlayerDestroyBlockEvent ev);
bool placeBlock(Event::PlayerPlaceBlockEvent ev);
bool serverStarted(Event::ServerStartedEvent ev);