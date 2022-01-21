#include "../../pch.h"
#include "../../listener.h"


bool Listener::playerDestroyBlock(Event::PlayerDestroyBlockEvent ev)
{
	Player* pl = ev.mPlayer;
	Block* bl = ev.mBlockInstance.getBlock();
	BlockPos pos = ev.mBlockInstance.getPosition();
	std::string coords = "x" + std::to_string(pos.x) + "/y" + std::to_string(pos.y) + "/z" + std::to_string(pos.z);
	int isInspector = -1;
	int pageCount = -1;
	std::string userId;

	Utils::sqlExecute(std::string("SELECT * FROM co_user WHERE nick = '" + pl->getName() + "';").c_str(), [&isInspector, &userId](SQLite::Statement& user) {
		user.executeStep();
		isInspector = user.getColumn("inspect").getInt();
		userId = user.getColumn("id").getString();
	});

	if (!isInspector)
	{
		Utils::sqlExecute(std::string("INSERT INTO co_block(user, xyz, block, action) VALUES('" + userId + "', '" + coords + "', '" + bl->getTypeName().erase(0, 10) + "', 0);").c_str());
		return true;
	}
	else
	{
		Utils::sqlExecute(std::string("SELECT COUNT(user) FROM co_block WHERE xyz = '" + coords + "';").c_str(), [&pageCount](SQLite::Statement& count) {
			count.executeStep();
			pageCount = Utils::pagesCalculate(count.getColumn("COUNT(user)").getInt());
		});

		Utils::sqlExecute(std::string("SELECT * FROM co_block WHERE xyz = '" + coords + "' ORDER BY time DESC LIMIT 0, 7;").c_str(), [&](SQLite::Statement& block) {
			if (block.executeStep())
			{
				std::chrono::system_clock sc;
				if (pageCount == 1)
				{
					pl->sendText(tr("INSPECT_HEADER") + coords + ")\n");
					do {
						Utils::sqlExecute(std::string("SELECT nick FROM co_user WHERE id = " + block.getColumn("user").getString() + ";").c_str(), [&block, &pl, &sc](SQLite::Statement& userNick) {
							userNick.executeStep();
							if (!block.getColumn("action").getInt()) pl->sendText(CG + Utils::timestampFormat(sc, block.getColumn("time").getInt()) + " ago" + CR + " - " + CB + userNick.getColumn("nick").getString() + CR + " removed " + CB + block.getColumn("block").getString() + CR + ".");
							else pl->sendText(CG + Utils::timestampFormat(sc, block.getColumn("time").getInt()) + " ago" + CR + " - " + CB + userNick.getColumn("nick").getString() + CR + " placed " + CB + block.getColumn("block").getString() + CR + ".");
						});
					} while (block.executeStep());
				}
				else if (pageCount > 1)
				{
					pl->sendText(tr("INSPECT_HEADER") + coords + ")\n");
					do {
						Utils::sqlExecute(std::string("SELECT nick FROM co_user WHERE id = " + block.getColumn("user").getString() + ";").c_str(), [&block, &pl, &sc](SQLite::Statement& userNick) {
							userNick.executeStep();
							if (!block.getColumn("action").getInt()) pl->sendText(CG + Utils::timestampFormat(sc, block.getColumn("time").getInt()) + " ago" + CR + " - " + CB + userNick.getColumn("nick").getString() + CR + " removed " + CB + block.getColumn("block").getString() + CR + ".");
							else pl->sendText(CG + Utils::timestampFormat(sc, block.getColumn("time").getInt()) + " ago" + CR + " - " + CB + userNick.getColumn("nick").getString() + CR + " placed " + CB + block.getColumn("block").getString() + CR + ".");
						});
					} while (block.executeStep());
					Utils::sqlExecute(std::string("UPDATE co_user SET l_xyz = '" + coords + "' WHERE nick = '" + pl->getName() + "'; ").c_str());
					pl->sendText(tr("LOOKUP_VIEW_PAGE", "1/" + std::to_string(pageCount) + tr("SYMBOL_ARROW_RIGHT"), "/co l <page>"));
				};
			}
			else pl->sendText(tr("NO_DATA_LOCATION", "data"));
		});
		return false;
	}
}
