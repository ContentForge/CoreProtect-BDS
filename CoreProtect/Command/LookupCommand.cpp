#include "../pch.h"
#include "../Command.h"


void CoreProtect::lookupCommand(ServerPlayer* pl) const
{
	Utils::sqlExecute(std::string("SELECT * FROM co_user WHERE nick = '" + pl->getName() + "';").c_str(), [&](SQLite::Statement& smUser) {
		smUser.executeStep();

		if (smUser.getColumn("inspect").getInt() && smUser.getColumn("l_id").getInt() != -1)
		{
			int pageCount = smUser.getColumn("l_pages").getInt(); // 5
			if (lookupPage <= pageCount && lookupPage > 0)
			{
				std::string coords = smUser.getColumn("l_xyz").getString();
				int pageNow = smUser.getColumn("l_page").getInt(); // 1
				int limit = -1;
				std::string query;
				int skip = -1;

				if (lookupPage > pageNow) // 3 > 1
				{
					limit = (lookupPage - pageNow) * 7; // (3 - 1) * 7 = 14
					query = "SELECT * FROM co_block WHERE xyz = '" + coords + "' AND id < " + smUser.getColumn("l_idn").getString() + " ORDER BY id DESC LIMIT " + std::to_string(limit) + ";";
					skip = limit - 7;
				}
				else if (lookupPage < pageNow || lookupPage == pageNow)
				{
					limit = lookupPage * 7; // 3 * 7 = 21
					query = "SELECT * FROM co_block WHERE xyz = '" + coords + "' AND id <= " + smUser.getColumn("l_id").getString() + " ORDER BY id DESC LIMIT " + std::to_string(limit) + ";";
					skip = limit - 7;
				}

				Utils::sqlExecute(query.c_str(), [&](SQLite::Statement& sm) {
					if (skip > 0)
					{
						int skippedCount = 0;
						while (skippedCount < limit - 7)
						{
							sm.executeStep();
							skippedCount++;
						}
					}

					int nowId = -1;
					pl->sendText(tr("INSPECT_HEADER") + coords + ")\n"); // ----- CoreProtect ----- (x0/y0/z0)
					while (sm.executeStep())
					{
						Utils::sqlExecute(std::string("SELECT nick FROM co_user WHERE id = " + sm.getColumn("user").getString() + ";").c_str(), [&](SQLite::Statement& smNick) {
							smNick.executeStep();
							if (!sm.getColumn("action").getInt())
							{				                             // 0.00/h ago — KocTu4eK removed Diamond Block.
								pl->sendText(G + "0.00/h ago" + R + " - " + B + smNick.getColumn("nick").getString() + R + " removed " + B + sm.getColumn("block").getString() + R + ".");
							}
							else
							{				                             // 0.00/h ago — KocTu4eK placed Netherite Block.
								pl->sendText(G + "0.00/h ago" + R + " - " + B + smNick.getColumn("nick").getString() + R + " placed " + B + sm.getColumn("block").getString() + R + ".");
							}
							nowId = sm.getColumn("id").getInt();
						});
					}                                                    // Page 1/3 ►. To view a page, type "/co l <page>".
					Utils::sqlExecute(std::string("UPDATE co_user SET l_idn = " + std::to_string(nowId) + ", l_page = " + std::to_string(lookupPage) + " WHERE nick = '" + pl->getName() + "';").c_str()); 
					if (lookupPage == 1) pl->sendText(tr("LOOKUP_VIEW_PAGE", std::to_string(lookupPage) + "/" + std::to_string(pageCount) + tr("SYMBOL_ARROW_RIGHT"), "/co l <page>"));                    // Page 1/3 ►.
					else if (!(pageCount - lookupPage)) pl->sendText(tr("LOOKUP_VIEW_PAGE", tr("SYMBOL_ARROW_LEFT") + std::to_string(lookupPage) + "/" + std::to_string(pageCount), "/co l <page>"));      // Page ◄ 3/3.
					else pl->sendText(tr("LOOKUP_VIEW_PAGE", tr("SYMBOL_ARROW_LEFT") + std::to_string(lookupPage) + "/" + std::to_string(pageCount) + tr("SYMBOL_ARROW_RIGHT"), "/co l <page>"));	       // Page ◄ 2/3 ►.
				});
			}
			else pl->sendText(tr("NO_RESULTS_PAGE", "data"));
		}
		else pl->sendText(tr("NO_RESULTS_PAGE", "data"));
	});
}