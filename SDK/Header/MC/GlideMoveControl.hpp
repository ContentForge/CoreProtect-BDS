// This Header is auto generated by BDSLiteLoader Toolchain
#pragma once
#define AUTO_GENERATED
#include "../Global.h"
#include "MoveControl.hpp"

#define BEFORE_EXTRA
// Include Headers or Declare Types Here

#undef BEFORE_EXTRA

class GlideMoveControl : public MoveControl {

#define AFTER_EXTRA
// Add Member There

#undef AFTER_EXTRA

#ifndef DISABLE_CONSTRUCTOR_PREVENTION_GLIDEMOVECONTROL
public:
    class GlideMoveControl& operator=(class GlideMoveControl const&) = delete;
    GlideMoveControl(class GlideMoveControl const&) = delete;
#endif

public:
    /*0*/ virtual ~GlideMoveControl();
    /*1*/ virtual void initializeInternal(class Mob&, struct MoveControlDescription*);
    /*2*/ virtual void tick(class MoveControlComponent&, class Mob&);
    MCAPI GlideMoveControl();

protected:

private:

};