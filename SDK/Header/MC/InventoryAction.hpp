// This Header is auto generated by BDSLiteLoader Toolchain
#pragma once
#define AUTO_GENERATED
#include "../Global.h"

#define BEFORE_EXTRA
// Include Headers or Declare Types Here
#undef BEFORE_EXTRA

class InventoryAction {

#define AFTER_EXTRA
// Add Member There
public:
#undef AFTER_EXTRA

#ifndef DISABLE_CONSTRUCTOR_PREVENTION_INVENTORYACTION
public:
    InventoryAction() = delete;
#endif

public:
    MCAPI InventoryAction(class InventoryAction const&);
    MCAPI class InventoryAction& operator=(class InventoryAction const&);
    MCAPI void postLoadItems(class BlockPalette&, bool);
    MCAPI ~InventoryAction();

protected:

private:

};