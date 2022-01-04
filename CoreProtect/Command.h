#pragma once
#include "pch.h"


enum CommandParameterOption;

class CoreProtect : public Command
{
	enum class Option : int option;

	std::string helpParam;
	std::string rollbackAction;

	int rollbackTime;
	int lookupPage;

	bool isSetHelpParam;
	bool isSetRollbackAction;

public:
	void execute(CommandOrigin const& ori, CommandOutput& outp) const override;
	static void setup(CommandRegistry* r);
};