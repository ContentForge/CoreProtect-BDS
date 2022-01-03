#pragma once
#include "pch.h"


enum CommandParameterOption;

class CoreProtect : public Command
{
	enum class OPTION : int option;
	enum class HELP_CMD : int help_cmd;

	int time;
	std::string action;

public:
	void execute(CommandOrigin const& ori, CommandOutput& outp) const override;
	static void setup(CommandRegistry* r);
};