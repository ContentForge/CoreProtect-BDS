#include "Command.h"

#define DEFAULT_COMMAND_FLAGS { (CommandFlagValue)0 }, { (CommandFlagValue)0x80 }


enum class CoreProtect::OPTION : int
{
	help = 1,
	inspect = 2,
	rollback = 3
} option;


enum class CoreProtect::HELP_CMD : int
{
	help = 1,
	inspect = 2,
	rollback = 3
} help_cmd;


void CoreProtect::execute(CommandOrigin const& ori, CommandOutput& outp) const
{
	switch (option)
	{
	case OPTION::help:
		ori.getPlayer()->sendText(tr("coreprotect.help"));
		ori.getPlayer()->sendText(std::to_string(ori.getPlayer()->getAttackTime()));
		break;
	case OPTION::inspect:
		ori.getPlayer()->sendText("inspect?");
		break;
	case OPTION::rollback:
		ori.getPlayer()->sendText("rollback?");
		break;
	}
	/*if (option == "help")
	{
		ori.getPlayer()->sendText(tr("coreprotect.help"));
	}
	else if (option == "inspect")
	{
		std::cout << option << std::endl;
	}*/
}


void CoreProtect::setup(CommandRegistry* r)
{
	using RegisterCommandHelper::makeMandatory;
	using RegisterCommandHelper::makeOptional;

	r->registerCommand("coreprotect", "CoreProtect", CommandPermissionLevel::Any, DEFAULT_COMMAND_FLAGS);
	r->registerAlias("coreprotect", "co");

	r->addEnum<OPTION>("help", { {"help", OPTION::help} });
	r->addEnum<OPTION>("inspect", { {"inspect", OPTION::inspect} });
	r->addEnum<OPTION>("rollback", { {"rollback", OPTION::rollback} });
	r->addEnum<HELP_CMD>("help_cmd", { {"help", HELP_CMD::help}, {"inspect", HELP_CMD::inspect}, {"rollback", HELP_CMD::rollback} });

	auto helpOption = makeMandatory<CommandParameterDataType::ENUM>(&CoreProtect::option, "help", "help").addOptions((CommandParameterOption)1);
	auto inspectOption = makeMandatory<CommandParameterDataType::ENUM>(&CoreProtect::option, "inspect", "inspect").addOptions((CommandParameterOption)1);
	auto rollbackOption = makeMandatory<CommandParameterDataType::ENUM>(&CoreProtect::option, "rollback", "rollback").addOptions((CommandParameterOption)1);
	auto helpCommand = makeMandatory<CommandParameterDataType::ENUM>(&CoreProtect::help_cmd, "command", "help_cmd");
	auto rollbackTime = makeMandatory(&CoreProtect::time, "time");
	auto rollbackAction = makeOptional(&CoreProtect::action, "action");

	r->registerOverload<CoreProtect>("co", helpOption, helpCommand);
	r->registerOverload<CoreProtect>("co", inspectOption);
	r->registerOverload<CoreProtect>("co", rollbackOption, rollbackTime, rollbackAction);
}