#include "../pch.h"
#include "../command.h"


void CoreProtect::execute(CommandOrigin const& ori, CommandOutput& outp) const
{
	ServerPlayer* pl = ori.getPlayer();

	switch (option)
	{
	case Option::HELP:     // co help...
		pl->sendText(tr("coreprotect.help"));
		break;
	case Option::INSPECT:  // co inspect...
		inspectCommand(pl);
		break;
	case Option::ROLLBACK: // co rollback...
		pl->sendText("rollback?");
		break;
	case Option::LOOKUP:   // co lookup...
		isSetLookupPage ? lookupCommand(pl) : (void)0;
		break;
	}
}
