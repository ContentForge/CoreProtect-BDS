// This Header is auto generated by BDSLiteLoader Toolchain
#pragma once
#define AUTO_GENERATED
#include "../Global.h"
#include "ScriptApi.hpp"

#define BEFORE_EXTRA
// Include Headers or Declare Types Here

#undef BEFORE_EXTRA

class ScriptBlockStateComponent {

#define AFTER_EXTRA
// Add Member There

#undef AFTER_EXTRA

#ifndef DISABLE_CONSTRUCTOR_PREVENTION_SCRIPTBLOCKSTATECOMPONENT
public:
    class ScriptBlockStateComponent& operator=(class ScriptBlockStateComponent const&) = delete;
    ScriptBlockStateComponent(class ScriptBlockStateComponent const&) = delete;
    ScriptBlockStateComponent() = delete;
#endif

public:
    /*0*/ virtual ~ScriptBlockStateComponent();
    /*1*/ virtual void __unk_vfn_0();
    /*2*/ virtual bool applyComponentTo(class ScriptApi::ScriptVersionInfo const&, class ScriptEngine&, class ScriptServerContext&, class Block const&, class BlockSource&, class BlockPos const&, class ScriptApi::ScriptObjectHandle const&) const;
    /*3*/ virtual void __unk_vfn_1();
    /*4*/ virtual void __unk_vfn_2();
    /*5*/ virtual void __unk_vfn_3();
    /*6*/ virtual bool retrieveComponentFrom(class ScriptApi::ScriptVersionInfo const&, class ScriptEngine&, class ScriptServerContext&, class Block const&, class BlockSource&, class BlockPos const&, class ScriptApi::ScriptObjectHandle&) const;
    /*7*/ virtual void __unk_vfn_4();
    /*8*/ virtual void __unk_vfn_5();
    /*9*/ virtual void __unk_vfn_6();
    /*10*/ virtual bool hasComponent(class ScriptApi::ScriptVersionInfo const&, class ScriptEngine&, class ScriptServerContext&, class Block const&, class BlockSource&, class BlockPos const&, bool&) const;
    /*11*/ virtual void __unk_vfn_7();
    /*12*/ virtual bool hasComponent(class ScriptApi::ScriptVersionInfo const&, class ScriptEngine&, class ScriptServerContext&, class Actor&, bool&) const;

protected:

private:
    MCAPI static class HashedString const mHash;

};