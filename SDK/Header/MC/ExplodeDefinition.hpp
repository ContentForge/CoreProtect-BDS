// This Header is auto generated by BDSLiteLoader Toolchain
#pragma once
#define AUTO_GENERATED
#include "../Global.h"
#include "Json.hpp"
#include "JsonUtil.hpp"

#define BEFORE_EXTRA
// Include Headers or Declare Types Here

#undef BEFORE_EXTRA

class ExplodeDefinition {

#define AFTER_EXTRA
// Add Member There

#undef AFTER_EXTRA

#ifndef DISABLE_CONSTRUCTOR_PREVENTION_EXPLODEDEFINITION
public:
    class ExplodeDefinition& operator=(class ExplodeDefinition const&) = delete;
    ExplodeDefinition(class ExplodeDefinition const&) = delete;
#endif

public:
    MCAPI ExplodeDefinition();
    MCAPI void deserializeData(class Json::Value&, class SemVersion const&);
    MCAPI void initialize(class EntityContext&, class ExplodeComponent&) const;
    MCAPI void serializeData(class Json::Value&) const;
    MCAPI void uninitialize(class EntityContext&) const;
    MCAPI static void buildSchema(class std::shared_ptr<class JsonUtil::JsonSchemaObjectNode<class JsonUtil::EmptyClass, class ExplodeDefinition> >&);

protected:

private:

};