#pragma once
#include "pch.h"
#include "dependencies.h"
#include "utils.h"

#define DEFAULT_COMMAND_FLAGS { (CommandFlagValue)0 }, { (CommandFlagValue)0x80 }


class CoreProtect : public Command
{
	enum class Option : int
	{
		HELP = 1,
		INSPECT = 2,
		I = 3,
		ROLLBACK = 4,
		LOOKUP = 5,
		L = 6
	} option;

	std::string helpParam;
	std::string rollbackAction;
	int rollbackTime;
	int lookupPage;
	bool isSetHelpParam;
	bool isSetRollbackAction;

	void inspectCommand(ServerPlayer*) const;
	void lookupCommand(ServerPlayer*) const;

public:
	void execute(CommandOrigin const& ori, CommandOutput& outp) const override;
	static void setup(CommandRegistry* r);
};
