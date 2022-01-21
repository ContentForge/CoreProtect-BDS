#include "../../pch.h"
#include "../../listener.h"


bool Listener::playerPlaceBlock(Event::PlayerPlaceBlockEvent ev)
{
	Player* pl = ev.mPlayer;
	Block* bl = ev.mBlockInstance.getBlock();
	BlockPos pos = ev.mBlockInstance.getPosition();
	std::string coords = "x" + std::to_string(pos.x) + "/y" + std::to_string(pos.y) + "/z" + std::to_string(pos.z); // «x0/y0/z0» (co_block.xyz)
	int isInspector = -1;
	std::string userId;

	Utils::sqlExecute(std::string("SELECT * FROM co_user WHERE nick = '" + pl->getName() + "';").c_str(), [&](SQLite::Statement& sm) {
		sm.executeStep();
		isInspector = sm.getColumn("inspect").getInt();
		userId = sm.getColumn("id").getString();
	});

	if (!isInspector)
	{
		Utils::sqlExecute(std::string("INSERT INTO co_block(user, xyz, block, action) VALUES('" + userId + "', '" + coords + "', '" + bl->getTypeName().erase(0, 10) + "', 1);").c_str());
		return true;
	}
	else
	{
		Utils::sqlExecute(std::string("UPDATE co_user SET l_xyz = '-', l_id = -1, l_idn = -1, l_pages = -1, l_page = 1 WHERE nick = '" + pl->getName() + "';").c_str());
		Utils::sqlExecute(std::string("SELECT id FROM co_block WHERE xyz = '" + coords + "' ORDER BY id DESC;").c_str(), [&](SQLite::Statement& sm) {
			if (sm.executeStep())
			{
				int descId = sm.getColumn("id").getInt(); // first received id (descending)
				int rowCount = 0;
				do rowCount++; while (sm.executeStep());
				int pageCount = Utils::pagesCalculate(rowCount); // 25 rows = 4 pages (3 pages + 1 (remainder))
				
				Utils::sqlExecute(std::string("SELECT * FROM co_block WHERE xyz = '" + coords + "' AND id <= " + std::to_string(descId) + " ORDER BY id DESC LIMIT 7;").c_str(), [&](SQLite::Statement& sm) {
					if (pageCount == 1)
					{
						pl->sendText(tr("INSPECT_HEADER") + coords + ")\n"); // ----- CoreProtect ----- (x0/y0/z0)
						while (sm.executeStep())
						{
							Utils::sqlExecute(std::string("SELECT nick FROM co_user WHERE id = " + sm.getColumn("user").getString() + ";").c_str(), [&](SQLite::Statement& smUser) {
								smUser.executeStep();
								if (!sm.getColumn("action").getInt())
								{				                            // 0.00/h ago — KocTu4eK removed Diamond Block.
									pl->sendText(G + "0.00/h ago" + R + " - " + B + smUser.getColumn("nick").getString() + R + " removed " + B + sm.getColumn("block").getString() + R + ".");
								}
								else
								{				                            // 0.00/h ago — KocTu4eK placed Netherite Block.
									pl->sendText(G + "0.00/h ago" + R + " - " + B + smUser.getColumn("nick").getString() + R + " placed " + B + sm.getColumn("block").getString() + R + ".");
								}
							});
						}
					}
					else if (pageCount > 1)
					{
						int nowId = -1;
						pl->sendText(tr("INSPECT_HEADER") + coords + ")\n"); // ----- CoreProtect ----- (x0/y0/z0)
						while (sm.executeStep())
						{
							Utils::sqlExecute(std::string("SELECT nick FROM co_user WHERE id = " + sm.getColumn("user").getString() + ";").c_str(), [&](SQLite::Statement& smUser) {
								smUser.executeStep();
								if (!sm.getColumn("action").getInt())
								{				                            // 0.00/h ago — KocTu4eK removed Diamond Block.
									pl->sendText(G + "0.00/h ago" + R + " - " + B + smUser.getColumn("nick").getString() + R + " removed " + B + sm.getColumn("block").getString() + R + ".");
								}
								else
								{				                            // 0.00/h ago — KocTu4eK placed Netherite Block.
									pl->sendText(G + "0.00/h ago" + R + " - " + B + smUser.getColumn("nick").getString() + R + " placed " + B + sm.getColumn("block").getString() + R + ".");
								}
								nowId = sm.getColumn("id").getInt();
							});
						}
						Utils::sqlExecute(std::string("UPDATE co_user SET l_xyz = '" + coords + "', l_id = " + std::to_string(descId) + ", l_idn = " + std::to_string(nowId) + ", l_pages = " + std::to_string(pageCount) + ", l_pages = " + std::to_string(pageCount) + " WHERE nick = '" + pl->getName() + "'; ").c_str());
						pl->sendText(tr("LOOKUP_VIEW_PAGE", "1/" + std::to_string(pageCount) + tr("SYMBOL_ARROW_RIGHT"), "/co l <page>")); // ————— Page 1/1 ►. View older typing "/co l <page>".
					};
				});
			}
			else pl->sendText(tr("NO_DATA_LOCATION", "data"));
		});
		return false;
	}
}
