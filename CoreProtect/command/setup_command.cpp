#include "../pch.h"
#include "../command.h"


void CoreProtect::setup(CommandRegistry* r)
{
    using RegisterCommandHelper::makeMandatory;
    using RegisterCommandHelper::makeOptional;

    r->registerCommand("coreprotect", "CoreProtect", CommandPermissionLevel::Any, DEFAULT_COMMAND_FLAGS); // coreprotect
    r->registerAlias("coreprotect", "co");                                                                // co (alias)

    ///////////////////////////////////////////////////////////////////////// Options //////////////////////////////////////////////////////////////////////
    r->addEnum<Option>("help", { {"help", Option::HELP} });                                                                                                  // help option enum
    r->addEnum<Option>("inspect", { {"inspect", Option::INSPECT} });                                                                                         // inspect option enum
    r->addEnum<Option>("i", { {"i", Option::INSPECT} });                                                                                                     // i (inspect) option enum
    r->addEnum<Option>("rollback", { {"rollback", Option::ROLLBACK} });                                                                                      // rollback option enum
    r->addEnum<Option>("lookup", { {"lookup", Option::LOOKUP} });                                                                                            // lookup option enum
    r->addEnum<Option>("l", { {"l", Option::LOOKUP} });                                                                                                      // l (lookup) option enum
    auto helpOption = makeMandatory<CommandParameterDataType::ENUM>(&CoreProtect::option, "help", "help").addOptions((CommandParameterOption)1);             // help option
    auto inspectOption = makeMandatory<CommandParameterDataType::ENUM>(&CoreProtect::option, "inspect", "inspect").addOptions((CommandParameterOption)1);    // inspect option
    auto iOption = makeMandatory<CommandParameterDataType::ENUM>(&CoreProtect::option, "i", "i").addOptions((CommandParameterOption)1);                      // i (inspect) option
    auto rollbackOption = makeMandatory<CommandParameterDataType::ENUM>(&CoreProtect::option, "rollback", "rollback").addOptions((CommandParameterOption)1); // rollback option
    auto lookupOption = makeMandatory<CommandParameterDataType::ENUM>(&CoreProtect::option, "lookup", "lookup").addOptions((CommandParameterOption)1);       // lookup option
    auto lOption = makeMandatory<CommandParameterDataType::ENUM>(&CoreProtect::option, "l", "l").addOptions((CommandParameterOption)1);                      // l (lookup) option

    ///////////////////////////////////////////////////////// Lookup & Rollback parameters ////////////////////////////////////////////////////////
    r->addSoftEnum("action", { {"+block"}, {"-block"}, {"chat"}, {"kill"} });                                                                       // action enum
    r->addSoftEnum("include", { {"stone"}, {"wood"}, {"glass"}, {"wool"} });                                                                        // include enum
    r->addSoftEnum("exclude", { {"stone"}, {"wood"}, {"glass"}, {"wool"} });                                                                        // exclude enum
    auto userParam = makeMandatory(&CoreProtect::user, "user");                                                                                     // user <>
    auto timeParam = makeMandatory(&CoreProtect::time, "time");                                                                                     // time <>
    auto radiusParam = makeMandatory(&CoreProtect::radius, "radius");                                                                               // radius <>
    auto actionParam = makeOptional<CommandParameterDataType::SOFT_ENUM>(&CoreProtect::action, "action", "action", &CoreProtect::isSetAction);      // action []
    auto includeParam = makeOptional<CommandParameterDataType::SOFT_ENUM>(&CoreProtect::include, "include", "include", &CoreProtect::isSetInclude); // include []
    auto excludeParam = makeOptional<CommandParameterDataType::SOFT_ENUM>(&CoreProtect::exclude, "exclude", "exclude", &CoreProtect::isSetExclude); // exclude []

    ////////////////////////////////////////////////////////////////////// Other ///////////////////////////////////////////////////////////////////
    r->addSoftEnum("helpParam", { {"help"}, {"inspect"}, {"rollback"}, {"lookup"} });                                                                // help enum
    auto helpParam = makeOptional<CommandParameterDataType::SOFT_ENUM>(&CoreProtect::helpParam, "param", "helpParam", &CoreProtect::isSetHelpParam); // help param []
    auto lookupPageParam = makeMandatory(&CoreProtect::lookupPage, "page", &CoreProtect::isSetLookupPage);                                           // lookup page param <>

    ///////////////////////////////////////////////////////// Command Overloads ///////////////////////////////////////////////////////
    r->registerOverload<CoreProtect>("co", helpOption, helpParam);                                                                      // co help [param:string]
    r->registerOverload<CoreProtect>("co", inspectOption);                                                                              // co inspect
    r->registerOverload<CoreProtect>("co", iOption);                                                                                    // co i
    r->registerOverload<CoreProtect>("co", rollbackOption, userParam, timeParam, radiusParam, actionParam, includeParam, excludeParam); // co rollback <user:target> <time:string> <radius:int> [action:string] [include:string] [exclude:string]
    r->registerOverload<CoreProtect>("co", lookupOption, lookupPageParam);                                                              // co lookup <page: int>
    r->registerOverload<CoreProtect>("co", lookupOption, userParam, timeParam, radiusParam, actionParam, includeParam, excludeParam);   // co lookup <user:target> <time:string> <radius:int> [action:string] [include:string] [exclude:string]
    r->registerOverload<CoreProtect>("co", lOption, lookupPageParam);                                                                   // co l <page: int>
    r->registerOverload<CoreProtect>("co", lOption, userParam, timeParam, radiusParam, actionParam, includeParam, excludeParam);        // co l <user:target> <time:string> <radius:int> [action:string] [include:string] [exclude:string]
}
