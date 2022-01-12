#include "../pch.h"
#include "../Command.h"


void CoreProtect::setup(CommandRegistry* r)
{
	using RegisterCommandHelper::makeMandatory;
	using RegisterCommandHelper::makeOptional;

	r->registerCommand("coreprotect", "CoreProtect", CommandPermissionLevel::Any, DEFAULT_COMMAND_FLAGS); // coreprotect
	r->registerAlias("coreprotect", "co");                                                                // co (alias)

	r->addEnum<Option>("help", { {"help", Option::HELP} });                           // help
	r->addSoftEnum("helpParam", { {"help"}, {"inspect"}, {"rollback"}, {"lookup"} }); // help param
	r->addEnum<Option>("inspect", { {"inspect", Option::INSPECT} });                  // inspect
	r->addEnum<Option>("i", { {"i", Option::I} });                                    // i (inspect)
	r->addEnum<Option>("rollback", { {"rollback", Option::ROLLBACK} });               // rollback
	r->addEnum<Option>("lookup", { {"lookup", Option::LOOKUP} });                     // lookup
	r->addEnum<Option>("l", { {"l", Option::L} });                                    // l (list)

	auto helpOption = makeMandatory<CommandParameterDataType::ENUM>(&CoreProtect::option, "help", "help").addOptions((CommandParameterOption)1);			 // help
	auto helpParam = makeOptional<CommandParameterDataType::SOFT_ENUM>(&CoreProtect::helpParam, "param", "helpParam", &CoreProtect::isSetHelpParam);         // help param
	auto inspectOption = makeMandatory<CommandParameterDataType::ENUM>(&CoreProtect::option, "inspect", "inspect").addOptions((CommandParameterOption)1);    // inspect
	auto iOption = makeMandatory<CommandParameterDataType::ENUM>(&CoreProtect::option, "i", "i").addOptions((CommandParameterOption)1);						 // i (inspect)
	auto rollbackOption = makeMandatory<CommandParameterDataType::ENUM>(&CoreProtect::option, "rollback", "rollback").addOptions((CommandParameterOption)1); // rollback
	auto lookupOption = makeMandatory<CommandParameterDataType::ENUM>(&CoreProtect::option, "lookup", "lookup").addOptions((CommandParameterOption)1);       // lookup
	auto lOption = makeMandatory<CommandParameterDataType::ENUM>(&CoreProtect::option, "l", "l").addOptions((CommandParameterOption)1);                      // l (list)
	auto lPageParam = makeMandatory(&CoreProtect::lookupPage, "page");																						 // lookup page
	auto rollbackTimeParam = makeMandatory(&CoreProtect::rollbackTime, "time");																				 // rollback time
	auto rollbackActionParam = makeOptional(&CoreProtect::rollbackAction, "action", &CoreProtect::isSetRollbackAction);									     // rollback action

	r->registerOverload<CoreProtect>("co", helpOption, helpParam);                                  // co help [param: string]
	r->registerOverload<CoreProtect>("co", inspectOption);                                          // co inspect
	r->registerOverload<CoreProtect>("co", iOption);                                                // co i
	r->registerOverload<CoreProtect>("co", rollbackOption, rollbackTimeParam, rollbackActionParam); // co rollback <time: int> [action: string]
	r->registerOverload<CoreProtect>("co", lookupOption);                                           // co lookup
	r->registerOverload<CoreProtect>("co", lOption, lPageParam);                                    // co l <page: int>
}