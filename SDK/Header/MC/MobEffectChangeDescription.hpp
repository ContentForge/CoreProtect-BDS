// This Header is auto generated by BDSLiteLoader Toolchain
#pragma once
#define AUTO_GENERATED
#include "../Global.h"
#include "Json.hpp"

#define BEFORE_EXTRA
// Include Headers or Declare Types Here

#undef BEFORE_EXTRA

class MobEffectChangeDescription {

#define AFTER_EXTRA
// Add Member There

#undef AFTER_EXTRA

#ifndef DISABLE_CONSTRUCTOR_PREVENTION_MOBEFFECTCHANGEDESCRIPTION
public:
    class MobEffectChangeDescription& operator=(class MobEffectChangeDescription const&) = delete;
    MobEffectChangeDescription(class MobEffectChangeDescription const&) = delete;
    MobEffectChangeDescription() = delete;
#endif

public:
    /*0*/ virtual char const* getJsonName() const;
    /*1*/ virtual ~MobEffectChangeDescription();
    /*2*/ virtual void deserializeData(struct DeserializeDataParams);
    /*3*/ virtual void serializeData(class Json::Value&) const;
    /*
    inline  ~MobEffectChangeDescription(){
         (MobEffectChangeDescription::*rv)();
        *((void**)&rv) = dlsym("??1MobEffectChangeDescription@@UEAA@XZ");
        return (this->*rv)();
    }
    */

protected:

private:

};