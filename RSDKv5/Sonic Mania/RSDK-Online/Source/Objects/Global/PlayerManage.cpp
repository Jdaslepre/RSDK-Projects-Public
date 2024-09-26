#include "RSDK-Online.hpp"

using namespace RSDK;
using namespace GameLogic;

PlayerManage::PlayerData PlayerManage::src;

void PlayerManage::InitDataSource(Player *p) {
    std::memcpy(&src.base, p, sizeof(GameObject::Entity));

    PLAYERMANAGE_SETVAL(animator.frameID, p);
    PLAYERMANAGE_SETVAL(animator.animationID, p);
    PLAYERMANAGE_SETVAL(animator.prevAnimationID, p);
    PLAYERMANAGE_SETVAL(animator.speed, p);
    PLAYERMANAGE_SETVAL(animator.timer, p);
    PLAYERMANAGE_SETVAL(animator.frameDuration, p);
    PLAYERMANAGE_SETVAL(animator.frameCount, p);
    PLAYERMANAGE_SETVAL(animator.loopIndex, p);
    PLAYERMANAGE_SETVAL(animator.rotationStyle, p);

    PLAYERMANAGE_SETVAL(tailAnimator.frameID, p);
    PLAYERMANAGE_SETVAL(tailAnimator.animationID, p);
    PLAYERMANAGE_SETVAL(tailAnimator.prevAnimationID, p);
    PLAYERMANAGE_SETVAL(tailAnimator.speed, p);
    PLAYERMANAGE_SETVAL(tailAnimator.timer, p);
    PLAYERMANAGE_SETVAL(tailAnimator.frameDuration, p);
    PLAYERMANAGE_SETVAL(tailAnimator.frameCount, p);
    PLAYERMANAGE_SETVAL(tailAnimator.loopIndex, p);
    PLAYERMANAGE_SETVAL(tailAnimator.rotationStyle, p);

    PLAYERMANAGE_SETVAL(minJogVelocity, p);
    PLAYERMANAGE_SETVAL(minRunVelocity, p);
    PLAYERMANAGE_SETVAL(minDashVelocity, p);
    PLAYERMANAGE_SETVAL(unused, p);
    PLAYERMANAGE_SETVAL(tailRotation, p);
    PLAYERMANAGE_SETVAL(tailDirection, p);
    PLAYERMANAGE_SETVAL(aniFrames, p);
    PLAYERMANAGE_SETVAL(tailFrames, p);
    PLAYERMANAGE_SETVAL(animationReserve, p);
    PLAYERMANAGE_SETVAL(playerID, p);
    PLAYERMANAGE_SETVAL(characterID, p);
    PLAYERMANAGE_SETVAL(rings, p);
    PLAYERMANAGE_SETVAL(ringExtraLife, p);
    PLAYERMANAGE_SETVAL(shield, p);
    PLAYERMANAGE_SETVAL(lives, p);
    PLAYERMANAGE_SETVAL(score, p);
    PLAYERMANAGE_SETVAL(score1UP, p);
    PLAYERMANAGE_SETVAL(hyperRing, p);
    PLAYERMANAGE_SETVAL(timer, p);
    PLAYERMANAGE_SETVAL(outtaHereTimer, p);
    PLAYERMANAGE_SETVAL(abilityTimer, p);
    PLAYERMANAGE_SETVAL(spindashCharge, p);
    PLAYERMANAGE_SETVAL(abilityValue, p);
    PLAYERMANAGE_SETVAL(drownTimer, p);
    PLAYERMANAGE_SETVAL(invincibleTimer, p);
    PLAYERMANAGE_SETVAL(speedShoesTimer, p);
    PLAYERMANAGE_SETVAL(blinkTimer, p);
    PLAYERMANAGE_SETVAL(scrollDelay, p);
    PLAYERMANAGE_SETVAL(skidding, p);
    PLAYERMANAGE_SETVAL(pushing, p);
    PLAYERMANAGE_SETVAL(underwater, p);
    PLAYERMANAGE_SETVAL(groundedStore, p);
    PLAYERMANAGE_SETVAL(invertGravity, p);

    PLAYERMANAGE_SETVAL(isChibi, p);
#if GAME_VERSION != VER_100
    PLAYERMANAGE_SETVAL(isTransforming, p);
#endif
    PLAYERMANAGE_SETVAL(superState, p);
    PLAYERMANAGE_SETVAL(superRingLossTimer, p);
    PLAYERMANAGE_SETVAL(superBlendAmount, p);
    PLAYERMANAGE_SETVAL(superBlendState, p);
    PLAYERMANAGE_SETVAL(sidekick, p);
    PLAYERMANAGE_SETVAL(scoreBonus, p);
    PLAYERMANAGE_SETVAL(jumpOffset, p);
    PLAYERMANAGE_SETVAL(collisionFlagH, p);
    PLAYERMANAGE_SETVAL(collisionFlagV, p);
    PLAYERMANAGE_SETVAL(topSpeed, p);
    PLAYERMANAGE_SETVAL(acceleration, p);
    PLAYERMANAGE_SETVAL(deceleration, p);
    PLAYERMANAGE_SETVAL(airAcceleration, p);
    PLAYERMANAGE_SETVAL(airDeceleration, p);
    PLAYERMANAGE_SETVAL(skidSpeed, p);
    PLAYERMANAGE_SETVAL(rollingFriction, p);
    PLAYERMANAGE_SETVAL(rollingDeceleration, p);
    PLAYERMANAGE_SETVAL(gravityStrength, p);
    PLAYERMANAGE_SETVAL(abilitySpeed, p);
    PLAYERMANAGE_SETVAL(jumpStrength, p);
    PLAYERMANAGE_SETVAL(jumpCap, p);
    PLAYERMANAGE_SETVAL(flailing, p);
    PLAYERMANAGE_SETVAL(sensorX[0], p);
    PLAYERMANAGE_SETVAL(sensorX[1], p);
    PLAYERMANAGE_SETVAL(sensorX[2], p);
    PLAYERMANAGE_SETVAL(sensorX[3], p);
    PLAYERMANAGE_SETVAL(sensorX[4], p);
    PLAYERMANAGE_SETVAL(sensorY, p);
    PLAYERMANAGE_SETVAL(moveLayerPosition, p);
    PLAYERMANAGE_SETVAL(controllerID, p);
    PLAYERMANAGE_SETVAL(controlLock, p);
    PLAYERMANAGE_SETVAL(up, p);
    PLAYERMANAGE_SETVAL(down, p);
    PLAYERMANAGE_SETVAL(left, p);
    PLAYERMANAGE_SETVAL(right, p);
    PLAYERMANAGE_SETVAL(jumpPress, p);
    PLAYERMANAGE_SETVAL(jumpHold, p);
    PLAYERMANAGE_SETVAL(applyJumpCap, p);
    PLAYERMANAGE_SETVAL(jumpAbilityState, p);
    PLAYERMANAGE_SETVAL(flyCarryTimer, p);
    PLAYERMANAGE_SETVAL(flyCarrySidekickPos, p);
    PLAYERMANAGE_SETVAL(flyCarryLeaderPos, p);
    PLAYERMANAGE_SETVAL(deathType, p);
    PLAYERMANAGE_SETVAL(forceRespawn, p);
#if MANIA_USE_PLUS
    PLAYERMANAGE_SETVAL(isGhost, p);
#endif
    PLAYERMANAGE_SETVAL(abilityValues[0], p);
    PLAYERMANAGE_SETVAL(abilityValues[1], p);
    PLAYERMANAGE_SETVAL(abilityValues[2], p);
    PLAYERMANAGE_SETVAL(abilityValues[3], p);
    PLAYERMANAGE_SETVAL(abilityValues[4], p);
    PLAYERMANAGE_SETVAL(abilityValues[5], p);
    PLAYERMANAGE_SETVAL(abilityValues[6], p);
    PLAYERMANAGE_SETVAL(abilityValues[7], p);
#if MANIA_USE_PLUS
    PLAYERMANAGE_SETVAL(uncurlTimer, p);
#endif

    if (!config.useDynamicStateSystem) {
        src.state           = p->state;
        src.nextAirState    = p->nextAirState;
        src.nextGroundState = p->nextGroundState;
#if MANIA_USE_PLUS
        src.stateInputReplay = p->stateInputReplay;
#endif
        src.stateInput   = p->stateInput;
        src.stateAbility = p->stateAbility;
        src.statePeelout = p->statePeelout;
    } else {
        src.currentState = RSDK::currentState;
    }
}

void PlayerManage::ApplyDataSourceToPlayer(Player *p) {
    std::memcpy(p, &src.base, sizeof(GameObject::Entity));

    PLAYERMANAGE_GETVAL(animator.frameID, p);
    PLAYERMANAGE_GETVAL(animator.animationID, p);
    PLAYERMANAGE_GETVAL(animator.prevAnimationID, p);
    PLAYERMANAGE_GETVAL(animator.speed, p);
    PLAYERMANAGE_GETVAL(animator.timer, p);
    PLAYERMANAGE_GETVAL(animator.frameDuration, p);
    PLAYERMANAGE_GETVAL(animator.frameCount, p);
    PLAYERMANAGE_GETVAL(animator.loopIndex, p);
    PLAYERMANAGE_GETVAL(animator.rotationStyle, p);

    PLAYERMANAGE_GETVAL(tailAnimator.frameID, p);
    PLAYERMANAGE_GETVAL(tailAnimator.animationID, p);
    PLAYERMANAGE_GETVAL(tailAnimator.prevAnimationID, p);
    PLAYERMANAGE_GETVAL(tailAnimator.speed, p);
    PLAYERMANAGE_GETVAL(tailAnimator.timer, p);
    PLAYERMANAGE_GETVAL(tailAnimator.frameDuration, p);
    PLAYERMANAGE_GETVAL(tailAnimator.frameCount, p);
    PLAYERMANAGE_GETVAL(tailAnimator.loopIndex, p);
    PLAYERMANAGE_GETVAL(tailAnimator.rotationStyle, p);

    PLAYERMANAGE_GETVAL(minJogVelocity, p);
    PLAYERMANAGE_GETVAL(minRunVelocity, p);
    PLAYERMANAGE_GETVAL(minDashVelocity, p);
    PLAYERMANAGE_GETVAL(unused, p);
    PLAYERMANAGE_GETVAL(tailRotation, p);
    PLAYERMANAGE_GETVAL(tailDirection, p);
    PLAYERMANAGE_GETVAL(aniFrames, p);
    PLAYERMANAGE_GETVAL(tailFrames, p);
    PLAYERMANAGE_GETVAL(animationReserve, p);
    PLAYERMANAGE_GETVAL(playerID, p);
    PLAYERMANAGE_GETVAL(characterID, p);
    PLAYERMANAGE_GETVAL(rings, p);
    PLAYERMANAGE_GETVAL(ringExtraLife, p);
    PLAYERMANAGE_GETVAL(shield, p);
    PLAYERMANAGE_GETVAL(lives, p);
    PLAYERMANAGE_GETVAL(score, p);
    PLAYERMANAGE_GETVAL(score1UP, p);
    PLAYERMANAGE_GETVAL(hyperRing, p);
    PLAYERMANAGE_GETVAL(timer, p);
    PLAYERMANAGE_GETVAL(outtaHereTimer, p);
    PLAYERMANAGE_GETVAL(abilityTimer, p);
    PLAYERMANAGE_GETVAL(spindashCharge, p);
    PLAYERMANAGE_GETVAL(abilityValue, p);
    PLAYERMANAGE_GETVAL(drownTimer, p);
    PLAYERMANAGE_GETVAL(invincibleTimer, p);
    PLAYERMANAGE_GETVAL(speedShoesTimer, p);
    PLAYERMANAGE_GETVAL(blinkTimer, p);
    PLAYERMANAGE_GETVAL(scrollDelay, p);
    PLAYERMANAGE_GETVAL(skidding, p);
    PLAYERMANAGE_GETVAL(pushing, p);
    PLAYERMANAGE_GETVAL(underwater, p);
    PLAYERMANAGE_GETVAL(groundedStore, p);
    PLAYERMANAGE_GETVAL(invertGravity, p);

    PLAYERMANAGE_GETVAL(isChibi, p);
#if GAME_VERSION != VER_100
    PLAYERMANAGE_GETVAL(isTransforming, p);
#endif
    PLAYERMANAGE_GETVAL(superState, p);
    PLAYERMANAGE_GETVAL(superRingLossTimer, p);
    PLAYERMANAGE_GETVAL(superBlendAmount, p);
    PLAYERMANAGE_GETVAL(superBlendState, p);
    PLAYERMANAGE_GETVAL(sidekick, p);
    PLAYERMANAGE_GETVAL(scoreBonus, p);
    PLAYERMANAGE_GETVAL(jumpOffset, p);
    PLAYERMANAGE_GETVAL(collisionFlagH, p);
    PLAYERMANAGE_GETVAL(collisionFlagV, p);
    PLAYERMANAGE_GETVAL(topSpeed, p);
    PLAYERMANAGE_GETVAL(acceleration, p);
    PLAYERMANAGE_GETVAL(deceleration, p);
    PLAYERMANAGE_GETVAL(airAcceleration, p);
    PLAYERMANAGE_GETVAL(airDeceleration, p);
    PLAYERMANAGE_GETVAL(skidSpeed, p);
    PLAYERMANAGE_GETVAL(rollingFriction, p);
    PLAYERMANAGE_GETVAL(rollingDeceleration, p);
    PLAYERMANAGE_GETVAL(gravityStrength, p);
    PLAYERMANAGE_GETVAL(abilitySpeed, p);
    PLAYERMANAGE_GETVAL(jumpStrength, p);
    PLAYERMANAGE_GETVAL(jumpCap, p);
    PLAYERMANAGE_GETVAL(flailing, p);
    PLAYERMANAGE_GETVAL(sensorX[0], p);
    PLAYERMANAGE_GETVAL(sensorX[1], p);
    PLAYERMANAGE_GETVAL(sensorX[2], p);
    PLAYERMANAGE_GETVAL(sensorX[3], p);
    PLAYERMANAGE_GETVAL(sensorX[4], p);
    PLAYERMANAGE_GETVAL(sensorY, p);
    PLAYERMANAGE_GETVAL(moveLayerPosition, p);
    PLAYERMANAGE_GETVAL(controllerID, p);
    PLAYERMANAGE_GETVAL(controlLock, p);
    PLAYERMANAGE_GETVAL(up, p);
    PLAYERMANAGE_GETVAL(down, p);
    PLAYERMANAGE_GETVAL(left, p);
    PLAYERMANAGE_GETVAL(right, p);
    PLAYERMANAGE_GETVAL(jumpPress, p);
    PLAYERMANAGE_GETVAL(jumpHold, p);
    PLAYERMANAGE_GETVAL(applyJumpCap, p);
    PLAYERMANAGE_GETVAL(jumpAbilityState, p);
    PLAYERMANAGE_GETVAL(flyCarryTimer, p);
    PLAYERMANAGE_GETVAL(flyCarrySidekickPos, p);
    PLAYERMANAGE_GETVAL(flyCarryLeaderPos, p);
    PLAYERMANAGE_GETVAL(deathType, p);
    PLAYERMANAGE_GETVAL(forceRespawn, p);
#if MANIA_USE_PLUS
    PLAYERMANAGE_GETVAL(isGhost, p);
#endif
    PLAYERMANAGE_GETVAL(abilityValues[0], p);
    PLAYERMANAGE_GETVAL(abilityValues[1], p);
    PLAYERMANAGE_GETVAL(abilityValues[2], p);
    PLAYERMANAGE_GETVAL(abilityValues[3], p);
    PLAYERMANAGE_GETVAL(abilityValues[4], p);
    PLAYERMANAGE_GETVAL(abilityValues[5], p);
    PLAYERMANAGE_GETVAL(abilityValues[6], p);
    PLAYERMANAGE_GETVAL(abilityValues[7], p);
#if MANIA_USE_PLUS
    PLAYERMANAGE_GETVAL(uncurlTimer, p);
#endif

    p->animator.SetAnimation(p->aniFrames, p->animator.animationID, false, p->animator.frameID);
    p->tailAnimator.SetAnimation(p->tailFrames, p->tailAnimator.animationID, false, p->tailAnimator.frameID);

    if (!config.useDynamicStateSystem) {
        p->state           = src.state;
        p->nextAirState    = src.nextAirState;
        p->nextGroundState = src.nextGroundState;
#if MANIA_USE_PLUS
        p->stateInputReplay = src.stateInputReplay;
#endif
        p->stateInput   = src.stateInput;
        p->stateAbility = src.stateAbility;
        p->statePeelout = src.statePeelout;
    }
}

// i apologize in advance

// -------------------
// Object State System
// -------------------

void (*Player_State_Static)()          = nullptr;
void (*Player_State_Ground)()          = nullptr;
void (*Player_State_Air)()             = nullptr;
void (*Player_State_Roll)()            = nullptr;
void (*Player_State_TubeRoll)()        = nullptr;
void (*Player_State_TubeAirRoll)()     = nullptr;
void (*Player_State_LookUp)()          = nullptr;
void (*Player_State_Crouch)()          = nullptr;
void (*Player_State_Spindash)()        = nullptr;
void (*Player_State_Peelout)()         = nullptr;
void (*Player_State_OuttaHere)()       = nullptr;
void (*Player_State_Transform)()       = nullptr;
void (*Player_State_Hurt)()            = nullptr;
void (*Player_State_Death)()           = nullptr;
void (*Player_State_Drown)()           = nullptr;
void (*Player_State_DropDash)()        = nullptr;
void (*Player_State_BubbleBounce)()    = nullptr;
void (*Player_State_TailsFlight)()     = nullptr;
void (*Player_State_FlyCarried)()      = nullptr;
void (*Player_State_KnuxGlideLeft)()   = nullptr;
void (*Player_State_KnuxGlideRight)()  = nullptr;
void (*Player_State_KnuxGlideDrop)()   = nullptr;
void (*Player_State_KnuxGlideSlide)()  = nullptr;
void (*Player_State_KnuxWallClimb)()   = nullptr;
void (*Player_State_KnuxLedgePullUp)() = nullptr;
#if MANIA_USE_PLUS
void (*Player_State_MightyHammerDrop)() = nullptr;
void (*Player_State_MightyUnspin)()     = nullptr;
void (*Player_State_RayGlide)()         = nullptr;
#endif
void (*Player_State_FlyToPlayer)()    = nullptr;
void (*Player_State_ReturnToPlayer)() = nullptr;
void (*Player_State_HoldRespawn)()    = nullptr;
void (*Player_State_EncoreRespawn)()  = nullptr;
void (*Player_State_Victory)()        = nullptr;
void (*Player_State_Bubble)()         = nullptr;
void (*Player_State_WaterSlide)()     = nullptr;
void (*Player_State_TransportTube)()  = nullptr;

// No actual logic changes, just makes use of S3KO's SET_CURRENT_STATE feature
PLAYERMANAGE_DEFINE_HOOK(Player_State_Static);
PLAYERMANAGE_DEFINE_HOOK(Player_State_Ground);
PLAYERMANAGE_DEFINE_HOOK(Player_State_Air);
PLAYERMANAGE_DEFINE_HOOK(Player_State_Roll);
PLAYERMANAGE_DEFINE_HOOK(Player_State_TubeRoll);
PLAYERMANAGE_DEFINE_HOOK(Player_State_TubeAirRoll);
PLAYERMANAGE_DEFINE_HOOK(Player_State_LookUp);
PLAYERMANAGE_DEFINE_HOOK(Player_State_Crouch);
PLAYERMANAGE_DEFINE_HOOK(Player_State_Spindash);
PLAYERMANAGE_DEFINE_HOOK(Player_State_Peelout);
PLAYERMANAGE_DEFINE_HOOK(Player_State_OuttaHere);
PLAYERMANAGE_DEFINE_HOOK(Player_State_Transform);
PLAYERMANAGE_DEFINE_HOOK(Player_State_Hurt);
PLAYERMANAGE_DEFINE_HOOK(Player_State_Death);
PLAYERMANAGE_DEFINE_HOOK(Player_State_Drown);
PLAYERMANAGE_DEFINE_HOOK(Player_State_DropDash);
PLAYERMANAGE_DEFINE_HOOK(Player_State_BubbleBounce);
PLAYERMANAGE_DEFINE_HOOK(Player_State_TailsFlight);
PLAYERMANAGE_DEFINE_HOOK(Player_State_FlyCarried);
PLAYERMANAGE_DEFINE_HOOK(Player_State_KnuxGlideLeft);
PLAYERMANAGE_DEFINE_HOOK(Player_State_KnuxGlideRight);
PLAYERMANAGE_DEFINE_HOOK(Player_State_KnuxGlideDrop);
PLAYERMANAGE_DEFINE_HOOK(Player_State_KnuxGlideSlide);
PLAYERMANAGE_DEFINE_HOOK(Player_State_KnuxWallClimb);
PLAYERMANAGE_DEFINE_HOOK(Player_State_KnuxLedgePullUp);
#if MANIA_USE_PLUS
PLAYERMANAGE_DEFINE_HOOK(Player_State_MightyHammerDrop);
PLAYERMANAGE_DEFINE_HOOK(Player_State_MightyUnspin);
PLAYERMANAGE_DEFINE_HOOK(Player_State_RayGlide);
#endif
PLAYERMANAGE_DEFINE_HOOK(Player_State_FlyToPlayer);
PLAYERMANAGE_DEFINE_HOOK(Player_State_ReturnToPlayer);
PLAYERMANAGE_DEFINE_HOOK(Player_State_HoldRespawn);
PLAYERMANAGE_DEFINE_HOOK(Player_State_EncoreRespawn);
PLAYERMANAGE_DEFINE_HOOK(Player_State_Victory);
PLAYERMANAGE_DEFINE_HOOK(Player_State_Bubble);
PLAYERMANAGE_DEFINE_HOOK(Player_State_WaterSlide);
PLAYERMANAGE_DEFINE_HOOK(Player_State_TransportTube);

void PlayerManage::GetStates() {
    PubFuncAuto(NULL, Player_State_Static);
    PubFuncAuto(NULL, Player_State_Ground);
    PubFuncAuto(NULL, Player_State_Air);
    PubFuncAuto(NULL, Player_State_Roll);
    PubFuncAuto(NULL, Player_State_TubeRoll);
    PubFuncAuto(NULL, Player_State_TubeAirRoll);
    PubFuncAuto(NULL, Player_State_LookUp);
    PubFuncAuto(NULL, Player_State_Crouch);
    PubFuncAuto(NULL, Player_State_Spindash);
    PubFuncAuto(NULL, Player_State_Peelout);
    PubFuncAuto(NULL, Player_State_OuttaHere);
    PubFuncAuto(NULL, Player_State_Transform);
    PubFuncAuto(NULL, Player_State_Hurt);
    PubFuncAuto(NULL, Player_State_Death);
    PubFuncAuto(NULL, Player_State_Drown);
    PubFuncAuto(NULL, Player_State_DropDash);
    PubFuncAuto(NULL, Player_State_BubbleBounce);
    PubFuncAuto(NULL, Player_State_TailsFlight);
    PubFuncAuto(NULL, Player_State_FlyCarried);
    PubFuncAuto(NULL, Player_State_KnuxGlideLeft);
    PubFuncAuto(NULL, Player_State_KnuxGlideRight);
    PubFuncAuto(NULL, Player_State_KnuxGlideDrop);
    PubFuncAuto(NULL, Player_State_KnuxGlideSlide);
    PubFuncAuto(NULL, Player_State_KnuxWallClimb);
    PubFuncAuto(NULL, Player_State_KnuxLedgePullUp);
#if MANIA_USE_PLUS
    PubFuncAuto(NULL, Player_State_MightyHammerDrop);
    PubFuncAuto(NULL, Player_State_MightyUnspin);
    PubFuncAuto(NULL, Player_State_RayGlide);
#endif
    PubFuncAuto(NULL, Player_State_FlyToPlayer);
    PubFuncAuto(NULL, Player_State_ReturnToPlayer);
    PubFuncAuto(NULL, Player_State_HoldRespawn);
    PubFuncAuto(NULL, Player_State_EncoreRespawn);
    PubFuncAuto(NULL, Player_State_Victory);
    PubFuncAuto(NULL, Player_State_Bubble);
    PubFuncAuto(NULL, Player_State_WaterSlide);
    PubFuncAuto(NULL, Player_State_TransportTube);
}

void PlayerManage::RegisterHooks() {
    PLAYERMANAGE_REGISTER_HOOK(Player_State_Static);
    PLAYERMANAGE_REGISTER_HOOK(Player_State_Ground);
    PLAYERMANAGE_REGISTER_HOOK(Player_State_Air);
    PLAYERMANAGE_REGISTER_HOOK(Player_State_Roll);
    PLAYERMANAGE_REGISTER_HOOK(Player_State_TubeRoll);
    PLAYERMANAGE_REGISTER_HOOK(Player_State_TubeAirRoll);
    PLAYERMANAGE_REGISTER_HOOK(Player_State_LookUp);
    PLAYERMANAGE_REGISTER_HOOK(Player_State_Crouch);
    PLAYERMANAGE_REGISTER_HOOK(Player_State_Spindash);
    PLAYERMANAGE_REGISTER_HOOK(Player_State_Peelout);
    PLAYERMANAGE_REGISTER_HOOK(Player_State_OuttaHere);
    PLAYERMANAGE_REGISTER_HOOK(Player_State_Transform);
    PLAYERMANAGE_REGISTER_HOOK(Player_State_Hurt);
    PLAYERMANAGE_REGISTER_HOOK(Player_State_Death);
    PLAYERMANAGE_REGISTER_HOOK(Player_State_Drown);
    PLAYERMANAGE_REGISTER_HOOK(Player_State_DropDash);
    PLAYERMANAGE_REGISTER_HOOK(Player_State_BubbleBounce);
    PLAYERMANAGE_REGISTER_HOOK(Player_State_TailsFlight);
    PLAYERMANAGE_REGISTER_HOOK(Player_State_FlyCarried);
    PLAYERMANAGE_REGISTER_HOOK(Player_State_KnuxGlideLeft);
    PLAYERMANAGE_REGISTER_HOOK(Player_State_KnuxGlideRight);
    PLAYERMANAGE_REGISTER_HOOK(Player_State_KnuxGlideDrop);
    PLAYERMANAGE_REGISTER_HOOK(Player_State_KnuxGlideSlide);
    PLAYERMANAGE_REGISTER_HOOK(Player_State_KnuxWallClimb);
    PLAYERMANAGE_REGISTER_HOOK(Player_State_KnuxLedgePullUp);
#if MANIA_USE_PLUS
    PLAYERMANAGE_REGISTER_HOOK(Player_State_MightyHammerDrop);
    PLAYERMANAGE_REGISTER_HOOK(Player_State_MightyUnspin);
    PLAYERMANAGE_REGISTER_HOOK(Player_State_RayGlide);
#endif
    PLAYERMANAGE_REGISTER_HOOK(Player_State_FlyToPlayer);
    PLAYERMANAGE_REGISTER_HOOK(Player_State_ReturnToPlayer);
    PLAYERMANAGE_REGISTER_HOOK(Player_State_HoldRespawn);
    PLAYERMANAGE_REGISTER_HOOK(Player_State_EncoreRespawn);
    PLAYERMANAGE_REGISTER_HOOK(Player_State_Victory);
    PLAYERMANAGE_REGISTER_HOOK(Player_State_Bubble);
    PLAYERMANAGE_REGISTER_HOOK(Player_State_WaterSlide);
    PLAYERMANAGE_REGISTER_HOOK(Player_State_TransportTube);
}

// to be used on the receiver's side
void PlayerManage::HandleStates(Player *p) {
    PLAYERMANAGE_MATCHSTATE(Player_State_Static, p->state);
    PLAYERMANAGE_MATCHSTATE(Player_State_Ground, p->state);
    PLAYERMANAGE_MATCHSTATE(Player_State_Air, p->state);
    PLAYERMANAGE_MATCHSTATE(Player_State_Roll, p->state);
    PLAYERMANAGE_MATCHSTATE(Player_State_TubeRoll, p->state);
    PLAYERMANAGE_MATCHSTATE(Player_State_TubeAirRoll, p->state);
    PLAYERMANAGE_MATCHSTATE(Player_State_LookUp, p->state);
    PLAYERMANAGE_MATCHSTATE(Player_State_Crouch, p->state);
    PLAYERMANAGE_MATCHSTATE(Player_State_Spindash, p->state);
    PLAYERMANAGE_MATCHSTATE(Player_State_Peelout, p->state);
    PLAYERMANAGE_MATCHSTATE(Player_State_OuttaHere, p->state);
    PLAYERMANAGE_MATCHSTATE(Player_State_Transform, p->state);
    PLAYERMANAGE_MATCHSTATE(Player_State_Hurt, p->state);
    PLAYERMANAGE_MATCHSTATE(Player_State_Death, p->state);
    PLAYERMANAGE_MATCHSTATE(Player_State_Drown, p->state);
    PLAYERMANAGE_MATCHSTATE(Player_State_DropDash, p->state);
    PLAYERMANAGE_MATCHSTATE(Player_State_BubbleBounce, p->state);
    PLAYERMANAGE_MATCHSTATE(Player_State_TailsFlight, p->state);
    PLAYERMANAGE_MATCHSTATE(Player_State_FlyCarried, p->state);
    PLAYERMANAGE_MATCHSTATE(Player_State_KnuxGlideLeft, p->state);
    PLAYERMANAGE_MATCHSTATE(Player_State_KnuxGlideRight, p->state);
    PLAYERMANAGE_MATCHSTATE(Player_State_KnuxGlideDrop, p->state);
    PLAYERMANAGE_MATCHSTATE(Player_State_KnuxGlideSlide, p->state);
    PLAYERMANAGE_MATCHSTATE(Player_State_KnuxWallClimb, p->state);
    PLAYERMANAGE_MATCHSTATE(Player_State_KnuxLedgePullUp, p->state);
#if MANIA_USE_PLUS
    PLAYERMANAGE_MATCHSTATE(Player_State_MightyHammerDrop, p->state);
    PLAYERMANAGE_MATCHSTATE(Player_State_MightyUnspin, p->state);
    PLAYERMANAGE_MATCHSTATE(Player_State_RayGlide, p->state);
#endif
    PLAYERMANAGE_MATCHSTATE(Player_State_FlyToPlayer, p->state);
    PLAYERMANAGE_MATCHSTATE(Player_State_ReturnToPlayer, p->state);
    PLAYERMANAGE_MATCHSTATE(Player_State_HoldRespawn, p->state);
    PLAYERMANAGE_MATCHSTATE(Player_State_EncoreRespawn, p->state);
    PLAYERMANAGE_MATCHSTATE(Player_State_Victory, p->state);
    PLAYERMANAGE_MATCHSTATE(Player_State_Bubble, p->state);
    PLAYERMANAGE_MATCHSTATE(Player_State_WaterSlide, p->state);
    PLAYERMANAGE_MATCHSTATE(Player_State_TransportTube, p->state);
}