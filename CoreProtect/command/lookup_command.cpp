#include "../pch.h"
#include "../command.h"


void CoreProtect::lookupCommand(ServerPlayer* pl) const
{
	Utils::sqlExecute(std::string("SELECT * FROM co_user WHERE nick = '" + pl->getName() + "';").c_str(), [&](SQLite::Statement& user) {
		user.executeStep();
		if (user.getColumn("inspect").getInt() && user.getColumn("l_xyz").getString() != "-")
		{
			int pageCount = -1;
			Utils::sqlExecute(std::string("SELECT COUNT(user) FROM co_block WHERE xyz = '" + user.getColumn("l_xyz").getString() + "';").c_str(), [&pageCount](SQLite::Statement& count) {
				count.executeStep();
				pageCount = Utils::pagesCalculate(count.getColumn("COUNT(user)").getInt());
			});
			if (lookupPage <= pageCount && lookupPage > 0)
			{
				std::string coords = user.getColumn("l_xyz").getString();
				Utils::sqlExecute(std::string("SELECT * FROM co_block WHERE xyz = '" + coords + "' ORDER BY time DESC LIMIT " + std::to_string(lookupPage * 7 - 7) + ", 7;").c_str(), [&](SQLite::Statement& sm) {
					std::chrono::system_clock sc;
					pl->sendText(tr("INSPECT_HEADER") + coords + ")\n");
					while (sm.executeStep())
					{
						Utils::sqlExecute(std::string("SELECT nick FROM co_user WHERE id = " + sm.getColumn("user").getString() + ";").c_str(), [&](SQLite::Statement& smNick) {
							smNick.executeStep();
							if (!sm.getColumn("action").getInt()) pl->sendText(CG + Utils::timestampFormat(sc, sm.getColumn("time").getInt()) + " ago" + CR + " - " + CB + smNick.getColumn("nick").getString() + CR + " removed " + CB + sm.getColumn("block").getString() + CR + ".");
							else pl->sendText(CG + Utils::timestampFormat(sc, sm.getColumn("time").getInt()) + " ago" + CR + " - " + CB + smNick.getColumn("nick").getString() + CR + " placed " + CB + sm.getColumn("block").getString() + CR + ".");
						});
					}
					if (lookupPage == 1) pl->sendText(tr("LOOKUP_VIEW_PAGE", std::to_string(lookupPage) + "/" + std::to_string(pageCount) + tr("SYMBOL_ARROW_RIGHT"), "/co l <page>"));               // Page 1/3 ►.
					else if (!(pageCount - lookupPage)) pl->sendText(tr("LOOKUP_VIEW_PAGE", tr("SYMBOL_ARROW_LEFT") + std::to_string(lookupPage) + "/" + std::to_string(pageCount), "/co l <page>")); // Page ◄ 3/3.
					else pl->sendText(tr("LOOKUP_VIEW_PAGE", tr("SYMBOL_ARROW_LEFT") + std::to_string(lookupPage) + "/" + std::to_string(pageCount) + tr("SYMBOL_ARROW_RIGHT"), "/co l <page>"));	  // Page ◄ 2/3 ►.
				});
			}
			else pl->sendText(tr("NO_RESULTS_PAGE", "data"));
		}
		else pl->sendText(tr("NO_RESULTS_PAGE", "data"));
	});
}
