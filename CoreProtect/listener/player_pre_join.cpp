#include "../pch.h"
#include "../listener.h"


bool Listener::playerPreJoin(Event::PlayerPreJoinEvent ev)
{
	Utils::sqlExecute(std::string("INSERT INTO co_user(nick) SELECT '" + ev.mPlayer->getName() + "' WHERE NOT EXISTS(SELECT * FROM co_user WHERE nick = '" + ev.mPlayer->getName() + "');").c_str());
	return true;
}