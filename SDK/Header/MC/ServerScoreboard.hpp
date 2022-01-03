// This Header is auto generated by BDSLiteLoader Toolchain
#pragma once
#define AUTO_GENERATED
#include "../Global.h"

#define BEFORE_EXTRA
// Include Headers or Declare Types Here
#include "Scoreboard.hpp"

#undef BEFORE_EXTRA

class ServerScoreboard {

#define AFTER_EXTRA
// Add Member There

#undef AFTER_EXTRA

#ifndef DISABLE_CONSTRUCTOR_PREVENTION_SERVERSCOREBOARD
public:
    class ServerScoreboard& operator=(class ServerScoreboard const&) = delete;
    ServerScoreboard(class ServerScoreboard const&) = delete;
    ServerScoreboard() = delete;
#endif

public:
    /*0*/ virtual ~ServerScoreboard();
    /*1*/ virtual class DisplayObjective const* setDisplayObjective(std::string const&, class Objective const&, enum ObjectiveSortOrder);
    /*2*/ virtual class Objective* clearDisplayObjective(std::string const&);
    /*3*/ virtual struct ScoreboardId const& createScoreboardId(class Player const&);
    /*4*/ virtual struct ScoreboardId const& createScoreboardId(class Actor const&);
    /*5*/ virtual struct ScoreboardId const& createScoreboardId(std::string const&);
    /*6*/ virtual void onObjectiveAdded(class Objective const&);
    /*7*/ virtual void onObjectiveRemoved(class Objective&);
    /*8*/ virtual void onScoreChanged(struct ScoreboardId const&, class Objective const&);
    /*9*/ virtual void onPlayerScoreRemoved(struct ScoreboardId const&, class Objective const&);
    /*10*/ virtual void onPlayerJoined(class Player const&);
    /*11*/ virtual void onPlayerIdentityUpdated(struct PlayerScoreboardId const&);
    /*12*/ virtual void tick();
    /*13*/ virtual void setPacketSender(class PacketSender*);
    /*14*/ virtual void writeToLevelStorage();
    /*15*/ virtual bool isClientSide() const;
    /*
    inline  ~ServerScoreboard(){
         (ServerScoreboard::*rv)();
        *((void**)&rv) = dlsym("??1ServerScoreboard@@UEAA@XZ");
        return (this->*rv)();
    }
    */
    MCAPI ServerScoreboard(class CommandSoftEnumRegistry, class LevelStorage*);
    MCAPI void deserialize(std::unique_ptr<class CompoundTag>);
    MCAPI std::unique_ptr<class CompoundTag> serialize() const;
    MCAPI void setClearDisplayObjectiveCallback(class std::function<void (std::string const& , class DisplayObjective const& )>);
    MCAPI void setIdentityUpdatedCallback(class std::function<void (struct ScoreboardId const& )>);
    MCAPI void setScoreChangedCallback(class std::function<void (struct ScoreboardId const& )>);
    MCAPI void setScoreRemovedCallback(class std::function<void (struct ScoreboardId const& )>);
    MCAPI void setSetDisplayObjectiveCallback(class std::function<void (std::string const& , class DisplayObjective const& )>);

protected:

private:
    MCAPI void _stopTrackingObjective(class Objective const&);
    MCAPI struct ScorePacketInfo _unpackIdentityDefToScorePacket(class ScoreboardIdentityRef const&, std::string const&, int);

};