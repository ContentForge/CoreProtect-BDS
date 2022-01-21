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
        ROLLBACK = 3,
        LOOKUP = 4,
    } option;

    ///// Lookup & Rollback /////
    CommandSelector<Player> user; // <>
    std::string time;	          // <>
    int radius;			  // <>
    std::string action;		  // []
    std::string include;	  // []
    std::string exclude;          // []
    bool isSetAction;		  // a?
    bool isSetInclude;	          // i?
    bool isSetExclude;            // e?

    //////// Other ///////
    std::string helpParam; // []
    int lookupPage;	   // <>
    bool isSetHelpParam;   // h?
    bool isSetLookupPage;  // p?

    void inspectCommand(ServerPlayer*) const;
    void lookupCommand(ServerPlayer*) const;

public:
    void execute(CommandOrigin const& ori, CommandOutput& outp) const override;
    static void setup(CommandRegistry* r);
};
