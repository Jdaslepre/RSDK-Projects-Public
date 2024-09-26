#include "../3KTC.hpp"

using namespace RSDK;

namespace GameLogic {

// -------------------
// Object Registration
// -------------------

MOD_REGISTER_OBJECT(Player);

// -------------
// Object States
// -------------

Action<void> Player::State_Victory;
Action<void> Player::Input_Gamepad;

// ----------------
// Public Functions
// ----------------

bool32 (*Player_CheckValidState)(Player *player) = nullptr;

// ----------------------
// Standard Entity Events
// ----------------------

// The v5U decomp isn't currently able to do super for
// StaticLoad, so here's a clone of it
void Player::StaticLoad(Static *sVars) {
    RSDK_INIT_STATIC_VARS(Player);

    // ---- Sonic

    // Normal
    sVars->sonicPhysicsTable[0] = 0x60000;  // Top speed
    sVars->sonicPhysicsTable[1] = 0xC00;    // Ground acceleration
    sVars->sonicPhysicsTable[2] = 0x1800;   // Air acceleration
    sVars->sonicPhysicsTable[3] = 0x600;    // Air deceleration
    sVars->sonicPhysicsTable[4] = 0x8000;   // Skidding speed
    sVars->sonicPhysicsTable[5] = 0x600;    // Rolling friction
    sVars->sonicPhysicsTable[6] = 0x68000;  // Jump strength
    sVars->sonicPhysicsTable[7] = -0x40000; // Jump cap

    // Underwater
    sVars->sonicPhysicsTable[8]  = 0x30000;  // Top speed
    sVars->sonicPhysicsTable[9]  = 0x600;    // Ground acceleration
    sVars->sonicPhysicsTable[10] = 0xC00;    // Air acceleration
    sVars->sonicPhysicsTable[11] = 0x300;    // Air deceleration
    sVars->sonicPhysicsTable[12] = 0x4000;   // Skidding speed
    sVars->sonicPhysicsTable[13] = 0x300;    // Rolling friction
    sVars->sonicPhysicsTable[14] = 0x38000;  // Jump strength
    sVars->sonicPhysicsTable[15] = -0x20000; // Jump cap

    // Super
    sVars->sonicPhysicsTable[16] = 0xA0000;  // Top speed
    sVars->sonicPhysicsTable[17] = 0x3000;   // Ground acceleration
    sVars->sonicPhysicsTable[18] = 0x6000;   // Air acceleration
    sVars->sonicPhysicsTable[19] = 0x1800;   // Air deceleration
    sVars->sonicPhysicsTable[20] = 0x10000;  // Skidding speed
    sVars->sonicPhysicsTable[21] = 0x600;    // Rolling friction
    sVars->sonicPhysicsTable[22] = 0x80000;  // Jump strength
    sVars->sonicPhysicsTable[23] = -0x40000; // Jump cap

    // Super & underwater
    sVars->sonicPhysicsTable[24] = 0x50000;  // Top speed
    sVars->sonicPhysicsTable[25] = 0x1800;   // Ground acceleration
    sVars->sonicPhysicsTable[26] = 0x3000;   // Air acceleration
    sVars->sonicPhysicsTable[27] = 0xC00;    // Air deceleration
    sVars->sonicPhysicsTable[28] = 0x8000;   // Skidding speed
    sVars->sonicPhysicsTable[29] = 0x300;    // Rolling friction
    sVars->sonicPhysicsTable[30] = 0x38000;  // Jump strength
    sVars->sonicPhysicsTable[31] = -0x20000; // Jump cap

    // Speed shoes
    sVars->sonicPhysicsTable[32] = 0xC0000;  // Top speed
    sVars->sonicPhysicsTable[33] = 0x1800;   // Ground acceleration
    sVars->sonicPhysicsTable[34] = 0x3000;   // Air acceleration
    sVars->sonicPhysicsTable[35] = 0xC00;    // Air deceleration
    sVars->sonicPhysicsTable[36] = 0x8000;   // Skidding speed
    sVars->sonicPhysicsTable[37] = 0x600;    // Rolling friction
    sVars->sonicPhysicsTable[38] = 0x68000;  // Jump strength
    sVars->sonicPhysicsTable[39] = -0x40000; // Jump cap

    // Speed shoes & underwater
    sVars->sonicPhysicsTable[40] = 0x60000;  // Top speed
    sVars->sonicPhysicsTable[41] = 0xC00;    // Ground acceleration
    sVars->sonicPhysicsTable[42] = 0x1800;   // Air acceleration
    sVars->sonicPhysicsTable[43] = 0x600;    // Air deceleration
    sVars->sonicPhysicsTable[44] = 0x4000;   // Skidding speed
    sVars->sonicPhysicsTable[45] = 0x300;    // Rolling friction
    sVars->sonicPhysicsTable[46] = 0x38000;  // Jump strength
    sVars->sonicPhysicsTable[47] = -0x20000; // Jump cap

    // Speed shoes & super
    sVars->sonicPhysicsTable[48] = 0xC0000;  // Top speed
    sVars->sonicPhysicsTable[49] = 0x1800;   // Ground acceleration
    sVars->sonicPhysicsTable[50] = 0x3000;   // Air acceleration
    sVars->sonicPhysicsTable[51] = 0xC00;    // Air deceleration
    sVars->sonicPhysicsTable[52] = 0x8000;   // Skidding speed
    sVars->sonicPhysicsTable[53] = 0x600;    // Rolling friction
    sVars->sonicPhysicsTable[54] = 0x80000;  // Jump strength
    sVars->sonicPhysicsTable[55] = -0x40000; // Jump cap

    // Speed shoes, super & underwater
    sVars->sonicPhysicsTable[56] = 0x60000;  // Top speed
    sVars->sonicPhysicsTable[57] = 0xC00;    // Ground acceleration
    sVars->sonicPhysicsTable[58] = 0x1800;   // Air acceleration
    sVars->sonicPhysicsTable[59] = 0x600;    // Air deceleration
    sVars->sonicPhysicsTable[60] = 0x4000;   // Skidding speed
    sVars->sonicPhysicsTable[61] = 0x300;    // Rolling friction
    sVars->sonicPhysicsTable[62] = 0x38000;  // Jump strength
    sVars->sonicPhysicsTable[63] = -0x20000; // Jump cap

    // ---- Sonic (Competition)

    // Normal
    sVars->sonicPhysicsTableComp[0] = 0x60000;  // Top speed
    sVars->sonicPhysicsTableComp[1] = 0x1000;   // Ground acceleration
    sVars->sonicPhysicsTableComp[2] = 0x1800;   // Air acceleration
    sVars->sonicPhysicsTableComp[3] = 0x600;    // Air deceleration
    sVars->sonicPhysicsTableComp[4] = 0x2000;   // Skidding speed
    sVars->sonicPhysicsTableComp[5] = 0x600;    // Rolling friction
    sVars->sonicPhysicsTableComp[6] = 0x68000;  // Jump strength
    sVars->sonicPhysicsTableComp[7] = -0x40000; // Jump cap

    // Underwater
    sVars->sonicPhysicsTableComp[8]  = 0xC0000;  // Top speed
    sVars->sonicPhysicsTableComp[9]  = 0x1800;   // Ground acceleration
    sVars->sonicPhysicsTableComp[10] = 0x1800;   // Air acceleration
    sVars->sonicPhysicsTableComp[11] = 0x600;    // Air deceleration
    sVars->sonicPhysicsTableComp[12] = 0x8000;   // Skidding speed
    sVars->sonicPhysicsTableComp[13] = 0x600;    // Rolling friction
    sVars->sonicPhysicsTableComp[14] = 0x68000;  // Jump strength
    sVars->sonicPhysicsTableComp[15] = -0x40000; // Jump cap

    // Super
    sVars->sonicPhysicsTableComp[16] = 0x30000;  // Top speed
    sVars->sonicPhysicsTableComp[17] = 0x800;    // Ground acceleration
    sVars->sonicPhysicsTableComp[18] = 0x1800;   // Air acceleration
    sVars->sonicPhysicsTableComp[19] = 0x600;    // Air deceleration
    sVars->sonicPhysicsTableComp[20] = 0x2000;   // Skidding speed
    sVars->sonicPhysicsTableComp[21] = 0x600;    // Rolling friction
    sVars->sonicPhysicsTableComp[22] = 0x68000;  // Jump strength
    sVars->sonicPhysicsTableComp[23] = -0x40000; // Jump cap

    // ---- Tails

    // Normal
    sVars->tailsPhysicsTable[0] = 0x60000;  // Top speed
    sVars->tailsPhysicsTable[1] = 0xC00;    // Ground acceleration
    sVars->tailsPhysicsTable[2] = 0x1800;   // Air acceleration
    sVars->tailsPhysicsTable[3] = 0x600;    // Air deceleration
    sVars->tailsPhysicsTable[4] = 0x8000;   // Skidding speed
    sVars->tailsPhysicsTable[5] = 0x600;    // Rolling friction
    sVars->tailsPhysicsTable[6] = 0x68000;  // Jump strength
    sVars->tailsPhysicsTable[7] = -0x40000; // Jump cap

    // Underwater
    sVars->tailsPhysicsTable[8]  = 0x30000;  // Top speed
    sVars->tailsPhysicsTable[9]  = 0x600;    // Ground acceleration
    sVars->tailsPhysicsTable[10] = 0xC00;    // Air acceleration
    sVars->tailsPhysicsTable[11] = 0x300;    // Air deceleration
    sVars->tailsPhysicsTable[12] = 0x4000;   // Skidding speed
    sVars->tailsPhysicsTable[13] = 0x300;    // Rolling friction
    sVars->tailsPhysicsTable[14] = 0x38000;  // Jump strength
    sVars->tailsPhysicsTable[15] = -0x20000; // Jump cap

    // Super
    sVars->tailsPhysicsTable[16] = 0xA0000;  // Top speed
    sVars->tailsPhysicsTable[17] = 0x3000;   // Ground acceleration
    sVars->tailsPhysicsTable[18] = 0x6000;   // Air acceleration
    sVars->tailsPhysicsTable[19] = 0x1800;   // Air deceleration
    sVars->tailsPhysicsTable[20] = 0x10000;  // Skidding speed
    sVars->tailsPhysicsTable[21] = 0x600;    // Rolling friction
    sVars->tailsPhysicsTable[22] = 0x80000;  // Jump strength
    sVars->tailsPhysicsTable[23] = -0x40000; // Jump cap

    // Super & underwater
    sVars->tailsPhysicsTable[24] = 0x50000;  // Top speed
    sVars->tailsPhysicsTable[25] = 0x1800;   // Ground acceleration
    sVars->tailsPhysicsTable[26] = 0x3000;   // Air acceleration
    sVars->tailsPhysicsTable[27] = 0xC00;    // Air deceleration
    sVars->tailsPhysicsTable[28] = 0x8000;   // Skidding speed
    sVars->tailsPhysicsTable[29] = 0x300;    // Rolling friction
    sVars->tailsPhysicsTable[30] = 0x38000;  // Jump strength
    sVars->tailsPhysicsTable[31] = -0x20000; // Jump cap

    // Speed shoes
    sVars->tailsPhysicsTable[32] = 0xC0000;  // Top speed
    sVars->tailsPhysicsTable[33] = 0x1800;   // Ground acceleration
    sVars->tailsPhysicsTable[34] = 0x3000;   // Air acceleration
    sVars->tailsPhysicsTable[35] = 0xC00;    // Air deceleration
    sVars->tailsPhysicsTable[36] = 0x8000;   // Skidding speed
    sVars->tailsPhysicsTable[37] = 0x600;    // Rolling friction
    sVars->tailsPhysicsTable[38] = 0x68000;  // Jump strength
    sVars->tailsPhysicsTable[39] = -0x40000; // Jump cap

    // Speed shoes & underwater
    sVars->tailsPhysicsTable[40] = 0x40000;  // Top speed
    sVars->tailsPhysicsTable[41] = 0xC00;    // Ground acceleration
    sVars->tailsPhysicsTable[42] = 0x1800;   // Air acceleration
    sVars->tailsPhysicsTable[43] = 0x600;    // Air deceleration
    sVars->tailsPhysicsTable[44] = 0x4000;   // Skidding speed
    sVars->tailsPhysicsTable[45] = 0x300;    // Rolling friction
    sVars->tailsPhysicsTable[46] = 0x38000;  // Jump strength
    sVars->tailsPhysicsTable[47] = -0x20000; // Jump cap

    // Speed shoes & super
    sVars->tailsPhysicsTable[48] = 0xC0000;  // Top speed
    sVars->tailsPhysicsTable[49] = 0x1800;   // Ground acceleration
    sVars->tailsPhysicsTable[50] = 0x3000;   // Air acceleration
    sVars->tailsPhysicsTable[51] = 0xC00;    // Air deceleration
    sVars->tailsPhysicsTable[52] = 0x8000;   // Skidding speed
    sVars->tailsPhysicsTable[53] = 0x600;    // Rolling friction
    sVars->tailsPhysicsTable[54] = 0x80000;  // Jump strength
    sVars->tailsPhysicsTable[55] = -0x40000; // Jump cap

    // Speed shoes, super & underwater
    sVars->tailsPhysicsTable[56] = 0x60000;  // Top speed
    sVars->tailsPhysicsTable[57] = 0xC00;    // Ground acceleration
    sVars->tailsPhysicsTable[58] = 0x1800;   // Air acceleration
    sVars->tailsPhysicsTable[59] = 0x600;    // Air deceleration
    sVars->tailsPhysicsTable[60] = 0x4000;   // Skidding speed
    sVars->tailsPhysicsTable[61] = 0x300;    // Rolling friction
    sVars->tailsPhysicsTable[62] = 0x38000;  // Jump strength
    sVars->tailsPhysicsTable[63] = -0x20000; // Jump cap

    // ---- Tails (Competition)

    // Normal
    sVars->tailsPhysicsTableComp[0] = 0x4C000;  // Top speed
    sVars->tailsPhysicsTableComp[1] = 0x1C00;   // Ground acceleration
    sVars->tailsPhysicsTableComp[2] = 0x1800;   // Air acceleration
    sVars->tailsPhysicsTableComp[3] = 0x600;    // Air deceleration
    sVars->tailsPhysicsTableComp[4] = 0x7000;   // Skidding speed
    sVars->tailsPhysicsTableComp[5] = 0x600;    // Rolling friction
    sVars->tailsPhysicsTableComp[6] = 0x68000;  // Jump strength
    sVars->tailsPhysicsTableComp[7] = -0x40000; // Jump cap

    // Underwater
    sVars->tailsPhysicsTableComp[8]  = 0xC0000;  // Top speed
    sVars->tailsPhysicsTableComp[9]  = 0x1800;   // Ground acceleration
    sVars->tailsPhysicsTableComp[10] = 0x1800;   // Air acceleration
    sVars->tailsPhysicsTableComp[11] = 0x600;    // Air deceleration
    sVars->tailsPhysicsTableComp[12] = 0x8000;   // Skidding speed
    sVars->tailsPhysicsTableComp[13] = 0x600;    // Rolling friction
    sVars->tailsPhysicsTableComp[14] = 0x68000;  // Jump strength
    sVars->tailsPhysicsTableComp[15] = -0x40000; // Jump cap

    // Super
    sVars->tailsPhysicsTableComp[16] = 0x30000;  // Top speed
    sVars->tailsPhysicsTableComp[17] = 0x800;    // Ground acceleration
    sVars->tailsPhysicsTableComp[18] = 0x1800;   // Air acceleration
    sVars->tailsPhysicsTableComp[19] = 0x600;    // Air deceleration
    sVars->tailsPhysicsTableComp[20] = 0x2000;   // Skidding speed
    sVars->tailsPhysicsTableComp[21] = 0x600;    // Rolling friction
    sVars->tailsPhysicsTableComp[22] = 0x68000;  // Jump strength
    sVars->tailsPhysicsTableComp[23] = -0x40000; // Jump cap

    // ---- Knuckles

    // Normal
    sVars->knuxPhysicsTable[0] = 0x60000;  // Top speed
    sVars->knuxPhysicsTable[1] = 0xC00;    // Ground acceleration
    sVars->knuxPhysicsTable[2] = 0x1800;   // Air acceleration
    sVars->knuxPhysicsTable[3] = 0x600;    // Air deceleration
    sVars->knuxPhysicsTable[4] = 0x8000;   // Skidding speed
    sVars->knuxPhysicsTable[5] = 0x600;    // Rolling friction
    sVars->knuxPhysicsTable[6] = 0x60000;  // Jump strength
    sVars->knuxPhysicsTable[7] = -0x40000; // Jump cap

    // Underwater
    sVars->knuxPhysicsTable[8]  = 0x30000;  // Top speed
    sVars->knuxPhysicsTable[9]  = 0x600;    // Ground acceleration
    sVars->knuxPhysicsTable[10] = 0xC00;    // Air acceleration
    sVars->knuxPhysicsTable[11] = 0x300;    // Air deceleration
    sVars->knuxPhysicsTable[12] = 0x4000;   // Skidding speed
    sVars->knuxPhysicsTable[13] = 0x300;    // Rolling friction
    sVars->knuxPhysicsTable[14] = 0x30000;  // Jump strength
    sVars->knuxPhysicsTable[15] = -0x20000; // Jump cap

    // Super
    sVars->knuxPhysicsTable[16] = 0xA0000;  // Top speed
    sVars->knuxPhysicsTable[17] = 0x3000;   // Ground acceleration
    sVars->knuxPhysicsTable[18] = 0x6000;   // Air acceleration
    sVars->knuxPhysicsTable[19] = 0x1800;   // Air deceleration
    sVars->knuxPhysicsTable[20] = 0x10000;  // Skidding speed
    sVars->knuxPhysicsTable[21] = 0x600;    // Rolling friction
    sVars->knuxPhysicsTable[22] = 0x60000;  // Jump strength
    sVars->knuxPhysicsTable[23] = -0x40000; // Jump cap

    // Super & underwater
    sVars->knuxPhysicsTable[24] = 0x50000;  // Top speed
    sVars->knuxPhysicsTable[25] = 0x1800;   // Ground acceleration
    sVars->knuxPhysicsTable[26] = 0x3000;   // Air acceleration
    sVars->knuxPhysicsTable[27] = 0xC00;    // Air deceleration
    sVars->knuxPhysicsTable[28] = 0x8000;   // Skidding speed
    sVars->knuxPhysicsTable[29] = 0x300;    // Rolling friction
    sVars->knuxPhysicsTable[30] = 0x30000;  // Jump strength
    sVars->knuxPhysicsTable[31] = -0x20000; // Jump cap

    // Speed shoes
    sVars->knuxPhysicsTable[32] = 0xC0000;  // Top speed
    sVars->knuxPhysicsTable[33] = 0x1800;   // Ground acceleration
    sVars->knuxPhysicsTable[34] = 0x3000;   // Air acceleration
    sVars->knuxPhysicsTable[35] = 0xC00;    // Air deceleration
    sVars->knuxPhysicsTable[36] = 0x8000;   // Skidding speed
    sVars->knuxPhysicsTable[37] = 0x600;    // Rolling friction
    sVars->knuxPhysicsTable[38] = 0x60000;  // Jump strength
    sVars->knuxPhysicsTable[39] = -0x40000; // Jump cap

    // Speed shoes & underwater
    sVars->knuxPhysicsTable[40] = 0x60000;  // Top speed
    sVars->knuxPhysicsTable[41] = 0xC00;    // Ground acceleration
    sVars->knuxPhysicsTable[42] = 0x1800;   // Air acceleration
    sVars->knuxPhysicsTable[43] = 0x600;    // Air deceleration
    sVars->knuxPhysicsTable[44] = 0x4000;   // Skidding speed
    sVars->knuxPhysicsTable[45] = 0x300;    // Rolling friction
    sVars->knuxPhysicsTable[46] = 0x30000;  // Jump strength
    sVars->knuxPhysicsTable[47] = -0x20000; // Jump cap

    // Speed shoes & super
    sVars->knuxPhysicsTable[48] = 0xC0000;  // Top speed
    sVars->knuxPhysicsTable[49] = 0x1800;   // Ground acceleration
    sVars->knuxPhysicsTable[50] = 0x3000;   // Air acceleration
    sVars->knuxPhysicsTable[51] = 0xC00;    // Air deceleration
    sVars->knuxPhysicsTable[52] = 0x8000;   // Skidding speed
    sVars->knuxPhysicsTable[53] = 0x600;    // Rolling friction
    sVars->knuxPhysicsTable[54] = 0x60000;  // Jump strength
    sVars->knuxPhysicsTable[55] = -0x20000; // Jump cap

    // Speed shoes, super & underwater
    sVars->knuxPhysicsTable[56] = 0x60000;  // Top speed
    sVars->knuxPhysicsTable[57] = 0xC00;    // Ground acceleration
    sVars->knuxPhysicsTable[58] = 0x1800;   // Air acceleration
    sVars->knuxPhysicsTable[59] = 0x600;    // Air deceleration
    sVars->knuxPhysicsTable[60] = 0x8000;   // Skidding speed
    sVars->knuxPhysicsTable[61] = 0x300;    // Rolling friction
    sVars->knuxPhysicsTable[62] = 0x30000;  // Jump strength
    sVars->knuxPhysicsTable[63] = -0x20000; // Jump cap

    // ---- Knuckles (Competition)

    // Normal
    sVars->knuxPhysicsTableComp[0] = 0x58000;  // Top speed
    sVars->knuxPhysicsTableComp[1] = 0x1000;   // Ground acceleration
    sVars->knuxPhysicsTableComp[2] = 0x1800;   // Air acceleration
    sVars->knuxPhysicsTableComp[3] = 0x600;    // Air deceleration
    sVars->knuxPhysicsTableComp[4] = 0x10D88;  // Skidding speed
    sVars->knuxPhysicsTableComp[5] = 0x600;    // Rolling friction
    sVars->knuxPhysicsTableComp[6] = 0x60000;  // Jump strength
    sVars->knuxPhysicsTableComp[7] = -0x40000; // Jump cap

    // Underwater
    sVars->knuxPhysicsTableComp[8]  = 0xC0000;  // Top speed
    sVars->knuxPhysicsTableComp[9]  = 0x1800;   // Ground acceleration
    sVars->knuxPhysicsTableComp[10] = 0x1800;   // Air acceleration
    sVars->knuxPhysicsTableComp[11] = 0x600;    // Air deceleration
    sVars->knuxPhysicsTableComp[12] = 0x8000;   // Skidding speed
    sVars->knuxPhysicsTableComp[13] = 0x600;    // Rolling friction
    sVars->knuxPhysicsTableComp[14] = 0x60000;  // Jump strength
    sVars->knuxPhysicsTableComp[15] = -0x40000; // Jump cap

    // Super
    sVars->knuxPhysicsTableComp[16] = 0x30000;  // Top speed
    sVars->knuxPhysicsTableComp[17] = 0x800;    // Ground acceleration
    sVars->knuxPhysicsTableComp[18] = 0x1800;   // Air acceleration
    sVars->knuxPhysicsTableComp[19] = 0x600;    // Air deceleration
    sVars->knuxPhysicsTableComp[20] = 0x2000;   // Skidding speed
    sVars->knuxPhysicsTableComp[21] = 0x600;    // Rolling friction
    sVars->knuxPhysicsTableComp[22] = 0x60000;  // Jump strength
    sVars->knuxPhysicsTableComp[23] = -0x40000; // Jump cap

    // ---- Mighty

    // Normal
    sVars->mightyPhysicsTable[0] = 0x60000;  // Top speed
    sVars->mightyPhysicsTable[1] = 0xC00;    // Ground acceleration
    sVars->mightyPhysicsTable[2] = 0x1800;   // Air acceleration
    sVars->mightyPhysicsTable[3] = 0x600;    // Air deceleration
    sVars->mightyPhysicsTable[4] = 0x8000;   // Skidding speed
    sVars->mightyPhysicsTable[5] = 0x600;    // Rolling friction
    sVars->mightyPhysicsTable[6] = 0x68000;  // Jump strength
    sVars->mightyPhysicsTable[7] = -0x40000; // Jump cap

    // Underwater
    sVars->mightyPhysicsTable[8]  = 0x30000;  // Top speed
    sVars->mightyPhysicsTable[9]  = 0x600;    // Ground acceleration
    sVars->mightyPhysicsTable[10] = 0xC00;    // Air acceleration
    sVars->mightyPhysicsTable[11] = 0x300;    // Air deceleration
    sVars->mightyPhysicsTable[12] = 0x4000;   // Skidding speed
    sVars->mightyPhysicsTable[13] = 0x300;    // Rolling friction
    sVars->mightyPhysicsTable[14] = 0x38000;  // Jump strength
    sVars->mightyPhysicsTable[15] = -0x20000; // Jump cap

    // Super
    sVars->mightyPhysicsTable[16] = 0xA0000;  // Top speed
    sVars->mightyPhysicsTable[17] = 0x3000;   // Ground acceleration
    sVars->mightyPhysicsTable[18] = 0x6000;   // Air acceleration
    sVars->mightyPhysicsTable[19] = 0x1800;   // Air deceleration
    sVars->mightyPhysicsTable[20] = 0x10000;  // Skidding speed
    sVars->mightyPhysicsTable[21] = 0x600;    // Rolling friction
    sVars->mightyPhysicsTable[22] = 0x80000;  // Jump strength
    sVars->mightyPhysicsTable[23] = -0x40000; // Jump cap

    // Super & underwater
    sVars->mightyPhysicsTable[24] = 0x50000;  // Top speed
    sVars->mightyPhysicsTable[25] = 0x1800;   // Ground acceleration
    sVars->mightyPhysicsTable[26] = 0x3000;   // Air acceleration
    sVars->mightyPhysicsTable[27] = 0xC00;    // Air deceleration
    sVars->mightyPhysicsTable[28] = 0x8000;   // Skidding speed
    sVars->mightyPhysicsTable[29] = 0x300;    // Rolling friction
    sVars->mightyPhysicsTable[30] = 0x38000;  // Jump strength
    sVars->mightyPhysicsTable[31] = -0x20000; // Jump cap

    // Speed shoes
    sVars->mightyPhysicsTable[32] = 0xC0000;  // Top speed
    sVars->mightyPhysicsTable[33] = 0x1800;   // Ground acceleration
    sVars->mightyPhysicsTable[34] = 0x3000;   // Air acceleration
    sVars->mightyPhysicsTable[35] = 0xC00;    // Air deceleration
    sVars->mightyPhysicsTable[36] = 0x8000;   // Skidding speed
    sVars->mightyPhysicsTable[37] = 0x600;    // Rolling friction
    sVars->mightyPhysicsTable[38] = 0x68000;  // Jump strength
    sVars->mightyPhysicsTable[39] = -0x40000; // Jump cap

    // Speed shoes & underwater
    sVars->mightyPhysicsTable[40] = 0x60000;  // Top speed
    sVars->mightyPhysicsTable[41] = 0xC00;    // Ground acceleration
    sVars->mightyPhysicsTable[42] = 0x1800;   // Air acceleration
    sVars->mightyPhysicsTable[43] = 0x600;    // Air deceleration
    sVars->mightyPhysicsTable[44] = 0x4000;   // Skidding speed
    sVars->mightyPhysicsTable[45] = 0x300;    // Rolling friction
    sVars->mightyPhysicsTable[46] = 0x38000;  // Jump strength
    sVars->mightyPhysicsTable[47] = -0x20000; // Jump cap

    // Speed shoes & super
    sVars->mightyPhysicsTable[48] = 0xC0000;  // Top speed
    sVars->mightyPhysicsTable[49] = 0x1800;   // Ground acceleration
    sVars->mightyPhysicsTable[50] = 0x3000;   // Air acceleration
    sVars->mightyPhysicsTable[51] = 0xC00;    // Air deceleration
    sVars->mightyPhysicsTable[52] = 0x8000;   // Skidding speed
    sVars->mightyPhysicsTable[53] = 0x600;    // Rolling friction
    sVars->mightyPhysicsTable[54] = 0x80000;  // Jump strength
    sVars->mightyPhysicsTable[55] = -0x40000; // Jump cap

    // Speed shoes, super & underwater
    sVars->mightyPhysicsTable[56] = 0x60000;  // Top speed
    sVars->mightyPhysicsTable[57] = 0xC00;    // Ground acceleration
    sVars->mightyPhysicsTable[58] = 0x1800;   // Air acceleration
    sVars->mightyPhysicsTable[59] = 0x600;    // Air deceleration
    sVars->mightyPhysicsTable[60] = 0x4000;   // Skidding speed
    sVars->mightyPhysicsTable[61] = 0x300;    // Rolling friction
    sVars->mightyPhysicsTable[62] = 0x38000;  // Jump strength
    sVars->mightyPhysicsTable[63] = -0x20000; // Jump cap

    // ---- Ray

    // Normal
    sVars->rayPhysicsTable[0] = 0x60000;  // Top speed
    sVars->rayPhysicsTable[1] = 0xC00;    // Ground acceleration
    sVars->rayPhysicsTable[2] = 0x1800;   // Air acceleration
    sVars->rayPhysicsTable[3] = 0x600;    // Air deceleration
    sVars->rayPhysicsTable[4] = 0x8000;   // Skidding speed
    sVars->rayPhysicsTable[5] = 0x600;    // Rolling friction
    sVars->rayPhysicsTable[6] = 0x68000;  // Jump strength
    sVars->rayPhysicsTable[7] = -0x40000; // Jump cap

    // Underwater
    sVars->rayPhysicsTable[8]  = 0x30000;  // Top speed
    sVars->rayPhysicsTable[9]  = 0x600;    // Ground acceleration
    sVars->rayPhysicsTable[10] = 0xC00;    // Air acceleration
    sVars->rayPhysicsTable[11] = 0x300;    // Air deceleration
    sVars->rayPhysicsTable[12] = 0x4000;   // Skidding speed
    sVars->rayPhysicsTable[13] = 0x300;    // Rolling friction
    sVars->rayPhysicsTable[14] = 0x38000;  // Jump strength
    sVars->rayPhysicsTable[15] = -0x20000; // Jump cap

    // Super
    sVars->rayPhysicsTable[16] = 0xA0000;  // Top speed
    sVars->rayPhysicsTable[17] = 0x3000;   // Ground acceleration
    sVars->rayPhysicsTable[18] = 0x6000;   // Air acceleration
    sVars->rayPhysicsTable[19] = 0x1800;   // Air deceleration
    sVars->rayPhysicsTable[20] = 0x10000;  // Skidding speed
    sVars->rayPhysicsTable[21] = 0x600;    // Rolling friction
    sVars->rayPhysicsTable[22] = 0x80000;  // Jump strength
    sVars->rayPhysicsTable[23] = -0x40000; // Jump cap

    // Super & underwater
    sVars->rayPhysicsTable[24] = 0x50000;  // Top speed
    sVars->rayPhysicsTable[25] = 0x1800;   // Ground acceleration
    sVars->rayPhysicsTable[26] = 0x3000;   // Air acceleration
    sVars->rayPhysicsTable[27] = 0xC00;    // Air deceleration
    sVars->rayPhysicsTable[28] = 0x8000;   // Skidding speed
    sVars->rayPhysicsTable[29] = 0x300;    // Rolling friction
    sVars->rayPhysicsTable[30] = 0x38000;  // Jump strength
    sVars->rayPhysicsTable[31] = -0x20000; // Jump cap

    // Speed shoes
    sVars->rayPhysicsTable[32] = 0xC0000;  // Top speed
    sVars->rayPhysicsTable[33] = 0x1800;   // Ground acceleration
    sVars->rayPhysicsTable[34] = 0x3000;   // Air acceleration
    sVars->rayPhysicsTable[35] = 0xC00;    // Air deceleration
    sVars->rayPhysicsTable[36] = 0x8000;   // Skidding speed
    sVars->rayPhysicsTable[37] = 0x600;    // Rolling friction
    sVars->rayPhysicsTable[38] = 0x68000;  // Jump strength
    sVars->rayPhysicsTable[39] = -0x40000; // Jump cap

    // Speed shoes & underwater
    sVars->rayPhysicsTable[40] = 0x60000;  // Top speed
    sVars->rayPhysicsTable[41] = 0xC00;    // Ground acceleration
    sVars->rayPhysicsTable[42] = 0x1800;   // Air acceleration
    sVars->rayPhysicsTable[43] = 0x600;    // Air deceleration
    sVars->rayPhysicsTable[44] = 0x4000;   // Skidding speed
    sVars->rayPhysicsTable[45] = 0x300;    // Rolling friction
    sVars->rayPhysicsTable[46] = 0x38000;  // Jump strength
    sVars->rayPhysicsTable[47] = -0x20000; // Jump cap

    // Speed shoes & super
    sVars->rayPhysicsTable[48] = 0xC0000;  // Top speed
    sVars->rayPhysicsTable[49] = 0x1800;   // Ground acceleration
    sVars->rayPhysicsTable[50] = 0x3000;   // Air acceleration
    sVars->rayPhysicsTable[51] = 0xC00;    // Air deceleration
    sVars->rayPhysicsTable[52] = 0x8000;   // Skidding speed
    sVars->rayPhysicsTable[53] = 0x600;    // Rolling friction
    sVars->rayPhysicsTable[54] = 0x80000;  // Jump strength
    sVars->rayPhysicsTable[55] = -0x40000; // Jump cap

    // Speed shoes, super & underwater
    sVars->rayPhysicsTable[56] = 0x60000;  // Top speed
    sVars->rayPhysicsTable[57] = 0xC00;    // Ground acceleration
    sVars->rayPhysicsTable[58] = 0x1800;   // Air acceleration
    sVars->rayPhysicsTable[59] = 0x600;    // Air deceleration
    sVars->rayPhysicsTable[60] = 0x4000;   // Skidding speed
    sVars->rayPhysicsTable[61] = 0x300;    // Rolling friction
    sVars->rayPhysicsTable[62] = 0x38000;  // Jump strength
    sVars->rayPhysicsTable[63] = -0x20000; // Jump cap

#if ORIGINS_USE_PLUS
    // ---- Amy

    // Normal
    sVars->amyPhysicsTable[0] = 0x60000;  // Top speed
    sVars->amyPhysicsTable[1] = 0xC00;    // Ground acceleration
    sVars->amyPhysicsTable[2] = 0x1800;   // Air acceleration
    sVars->amyPhysicsTable[3] = 0x600;    // Air deceleration
    sVars->amyPhysicsTable[4] = 0x8000;   // Skidding speed
    sVars->amyPhysicsTable[5] = 0x600;    // Rolling friction
    sVars->amyPhysicsTable[6] = 0x68000;  // Jump strength
    sVars->amyPhysicsTable[7] = -0x40000; // Jump cap

    // Underwater
    sVars->amyPhysicsTable[8]  = 0x30000;  // Top speed
    sVars->amyPhysicsTable[9]  = 0x600;    // Ground acceleration
    sVars->amyPhysicsTable[10] = 0xC00;    // Air acceleration
    sVars->amyPhysicsTable[11] = 0x300;    // Air deceleration
    sVars->amyPhysicsTable[12] = 0x4000;   // Skidding speed
    sVars->amyPhysicsTable[13] = 0x300;    // Rolling friction
    sVars->amyPhysicsTable[14] = 0x38000;  // Jump strength
    sVars->amyPhysicsTable[15] = -0x20000; // Jump cap

    // Super
    sVars->amyPhysicsTable[16] = 0xA0000;
    sVars->amyPhysicsTable[17] = 0x3000;
    sVars->amyPhysicsTable[18] = 0x6000;
    sVars->amyPhysicsTable[19] = 0x1800;
    sVars->amyPhysicsTable[20] = 0x10000;
    sVars->amyPhysicsTable[21] = 0x600;
    sVars->amyPhysicsTable[22] = 0x80000;
    sVars->amyPhysicsTable[23] = -0x40000;

    sVars->amyPhysicsTable[24] = 327680;
    sVars->amyPhysicsTable[25] = 6144;
    sVars->amyPhysicsTable[26] = 12288;
    sVars->amyPhysicsTable[27] = 3072;
    sVars->amyPhysicsTable[28] = 0x8000;
    sVars->amyPhysicsTable[29] = 768;
    sVars->amyPhysicsTable[30] = 229376;
    sVars->amyPhysicsTable[31] = -131072;

    sVars->amyPhysicsTable[32]     = 786432;
    sVars->amyPhysicsTable[33]     = 6144;
    sVars->amyPhysicsTable[34]     = 12288;
    sVars->amyPhysicsTable[35]     = 3072;
    sVars->amyPhysicsTable[36]     = 0x8000;
    sVars->amyPhysicsTable[37]     = 1536;
    sVars->amyPhysicsTable[38]     = 425984;
    sVars->amyPhysicsTable[39]     = -262144;
    sVars->amyPhysicsTable[40]     = 393216;
    sVars->amyPhysicsTable[41]     = 3072;
    sVars->amyPhysicsTable[42]     = 6144;
    sVars->amyPhysicsTable[43]     = 1536;
    sVars->amyPhysicsTable[44]     = 0x4000;
    sVars->amyPhysicsTable[45]     = 768;
    sVars->amyPhysicsTable[46]     = 229376;
    sVars->amyPhysicsTable[47]     = -131072;
    sVars->amyPhysicsTable[48]     = 786432;
    sVars->amyPhysicsTable[49]     = 6144;
    sVars->amyPhysicsTable[50]     = 12288;
    sVars->amyPhysicsTable[51]     = 3072;
    sVars->amyPhysicsTable[52]     = 0x8000;
    sVars->amyPhysicsTable[53]     = 1536;
    sVars->amyPhysicsTable[54]     = 0x80000;
    sVars->amyPhysicsTable[55]     = -262144;
    sVars->amyPhysicsTable[56]     = 393216;
    sVars->amyPhysicsTable[57]     = 3072;
    sVars->amyPhysicsTable[58]     = 6144;
    sVars->amyPhysicsTable[59]     = 1536;
    sVars->amyPhysicsTable[60]     = 0x4000;
    sVars->amyPhysicsTable[61]     = 768;
    sVars->amyPhysicsTable[62]     = 229376;
    sVars->amyPhysicsTable[63]     = -131072;
    sVars->amyPhysicsTableComp[0]  = 360448;
    sVars->amyPhysicsTableComp[1]  = 4096;
    sVars->amyPhysicsTableComp[2]  = 6144;
    sVars->amyPhysicsTableComp[3]  = 1536;
    sVars->amyPhysicsTableComp[4]  = 69000;
    sVars->amyPhysicsTableComp[5]  = 1536;
    sVars->amyPhysicsTableComp[6]  = 425984;
    sVars->amyPhysicsTableComp[7]  = -262144;
    sVars->amyPhysicsTableComp[8]  = 786432;
    sVars->amyPhysicsTableComp[9]  = 6144;
    sVars->amyPhysicsTableComp[10] = 6144;
    sVars->amyPhysicsTableComp[11] = 1536;
    sVars->amyPhysicsTableComp[12] = 0x8000;
    sVars->amyPhysicsTableComp[13] = 1536;
    sVars->amyPhysicsTableComp[14] = 425984;
    sVars->amyPhysicsTableComp[15] = -262144;
    sVars->amyPhysicsTableComp[16] = 196608;
    sVars->amyPhysicsTableComp[17] = 2048;
    sVars->amyPhysicsTableComp[18] = 6144;
    sVars->amyPhysicsTableComp[19] = 1536;
    sVars->amyPhysicsTableComp[20] = 0x2000;
    sVars->amyPhysicsTableComp[21] = 1536;
    sVars->amyPhysicsTableComp[22] = 425984;
    sVars->amyPhysicsTableComp[23] = -262144;

    // *sVars->unknown0784      = xmmword_140B939A0;
    // *&sVars->unknown0784[4]  = xmmword_140B939B0;
    // *&sVars->unknown0784[8]  = xmmword_140B939C0;
    // *&sVars->unknown0784[12] = xmmword_140B939D0;
    // *&sVars->unknown0784[16] = xmmword_140B939E0;
    // *&sVars->unknown0784[20] = xmmword_140B939F0;
#endif

    // ------------------
    // Character Palettes
    // ------------------

    // Sonic
    sVars->superPalette_Sonic[0]  = 0x6060E0;
    sVars->superPalette_Sonic[1]  = 0x2040C0;
    sVars->superPalette_Sonic[2]  = 0x202080;
    sVars->superPalette_Sonic[3]  = 0x8080E0;
    sVars->superPalette_Sonic[4]  = 0x6060C0;
    sVars->superPalette_Sonic[5]  = 0x404080;
    sVars->superPalette_Sonic[6]  = 0xA0A0E0;
    sVars->superPalette_Sonic[7]  = 0x8080C0;
    sVars->superPalette_Sonic[8]  = 0x6060A0;
    sVars->superPalette_Sonic[9]  = 0xC0C0E0;
    sVars->superPalette_Sonic[10] = 0xA0A0E0;
    sVars->superPalette_Sonic[11] = 0x8080C0;
    sVars->superPalette_Sonic[12] = 0xE0E0E0;
    sVars->superPalette_Sonic[13] = 12632288;
    sVars->superPalette_Sonic[14] = 0xA0A0E0;
    sVars->superPalette_Sonic[15] = 0xE0E0E0;
    sVars->superPalette_Sonic[16] = 0xE0E0E0;
    sVars->superPalette_Sonic[17] = 0xE0E0E0;
    sVars->superPalette_Sonic[18] = 0xE0E0C0;
    sVars->superPalette_Sonic[19] = 0xE0E0C0;
    sVars->superPalette_Sonic[20] = 0xE0E0A0;
    sVars->superPalette_Sonic[21] = 0xE0E0A0;
    sVars->superPalette_Sonic[22] = 0xE0E080;
    sVars->superPalette_Sonic[23] = 0xC0C060;
    sVars->superPalette_Sonic[24] = 0xE0E080;
    sVars->superPalette_Sonic[25] = 0xE0E000;
    sVars->superPalette_Sonic[26] = 0xA0A000;
    sVars->superPalette_Sonic[27] = 0xE0E0A0;
    sVars->superPalette_Sonic[28] = 0xE0E080;
    sVars->superPalette_Sonic[29] = 0xC0C060;

    sVars->superPalette_Sonic_Water1[0]  = 0x2080A0;
    sVars->superPalette_Sonic_Water1[1]  = 0x6080;
    sVars->superPalette_Sonic_Water1[2]  = 0x4060;
    sVars->superPalette_Sonic_Water1[3]  = 0x8080E0;
    sVars->superPalette_Sonic_Water1[4]  = 0x6060C0;
    sVars->superPalette_Sonic_Water1[5]  = 0x404080;
    sVars->superPalette_Sonic_Water1[6]  = 0xA0A0E0;
    sVars->superPalette_Sonic_Water1[7]  = 0x8080C0;
    sVars->superPalette_Sonic_Water1[8]  = 0x6060A0;
    sVars->superPalette_Sonic_Water1[9]  = 0xC0C0E0;
    sVars->superPalette_Sonic_Water1[10] = 0xA0A0E0;
    sVars->superPalette_Sonic_Water1[11] = 0x8080C0;
    sVars->superPalette_Sonic_Water1[12] = 0xE0E0E0;
    sVars->superPalette_Sonic_Water1[13] = 0xC0C0E0;
    sVars->superPalette_Sonic_Water1[14] = 0xA0A0E0;
    sVars->superPalette_Sonic_Water1[15] = 0xE0E0E0;
    sVars->superPalette_Sonic_Water1[16] = 0xE0E0E0;
    sVars->superPalette_Sonic_Water1[17] = 0xE0E0E0;
    sVars->superPalette_Sonic_Water1[18] = 0xE0E0C0;
    sVars->superPalette_Sonic_Water1[19] = 0xC0E0C0;
    sVars->superPalette_Sonic_Water1[20] = 0xC0E0A0;
    sVars->superPalette_Sonic_Water1[21] = 0xC0E0A0;
    sVars->superPalette_Sonic_Water1[22] = 0xC0E080;
    sVars->superPalette_Sonic_Water1[23] = 0xA0C060;
    sVars->superPalette_Sonic_Water1[24] = 0xC0E080;
    sVars->superPalette_Sonic_Water1[25] = 0xA0E040;
    sVars->superPalette_Sonic_Water1[26] = 0x80A040;
    sVars->superPalette_Sonic_Water1[27] = 0xE0E0C0;
    sVars->superPalette_Sonic_Water1[28] = 0xC0E0C0;
    sVars->superPalette_Sonic_Water1[29] = 0xC0E0A0;

    sVars->superPalette_Sonic_Water2[0] = 0x6060C0;
    sVars->superPalette_Sonic_Water2[1] = 0x4040A0;
    sVars->superPalette_Sonic_Water2[2] = 0x402060;
    sVars->superPalette_Sonic_Water2[3] = 0xE08080;
    sVars->superPalette_Sonic_Water2[4] = 0xC06060;
    sVars->superPalette_Sonic_Water2[5] = 0x804040;
    sVars->superPalette_Sonic_Water2[6] = 0xE0A0A0;
    sVars->superPalette_Sonic_Water2[7] = 0xC08080;
    sVars->superPalette_Sonic_Water2[8] = 0xA06060;

    sVars->superPalette_Sonic_Water2[9]  = 0xE0C0C0;
    sVars->superPalette_Sonic_Water2[10] = 0xE0A0A0;
    sVars->superPalette_Sonic_Water2[11] = 0xC08080;
    sVars->superPalette_Sonic_Water2[12] = 0xE0E0E0;
    sVars->superPalette_Sonic_Water2[13] = 0xE0C0C0;
    sVars->superPalette_Sonic_Water2[14] = 0xE0A0A0;
    sVars->superPalette_Sonic_Water2[15] = 0xE0E0E0;
    sVars->superPalette_Sonic_Water2[16] = 0xE0E0E0;
    sVars->superPalette_Sonic_Water2[17] = 0xE0E0E0;
    sVars->superPalette_Sonic_Water2[18] = 0xC0E0E0;
    sVars->superPalette_Sonic_Water2[19] = 0xC0E0C0;
    sVars->superPalette_Sonic_Water2[20] = 0xA0E0C0;
    sVars->superPalette_Sonic_Water2[21] = 0xA0E0C0;
    sVars->superPalette_Sonic_Water2[22] = 0x80E0C0;
    sVars->superPalette_Sonic_Water2[23] = 0x60C0A0;
    sVars->superPalette_Sonic_Water2[24] = 0x80E0C0;
    sVars->superPalette_Sonic_Water2[25] = 0x40E0A0;
    sVars->superPalette_Sonic_Water2[26] = 0x40A080;
    sVars->superPalette_Sonic_Water2[27] = 0xC0E0E0;
    sVars->superPalette_Sonic_Water2[28] = 0xC0E0C0;
    sVars->superPalette_Sonic_Water2[29] = 0xA0E0C0;

    sVars->hyperPalette_Sonic[0]  = 6316256;
    sVars->hyperPalette_Sonic[1]  = 2113728;
    sVars->hyperPalette_Sonic[2]  = 2105472;
    sVars->hyperPalette_Sonic[3]  = 8421600;
    sVars->hyperPalette_Sonic[4]  = 6316224;
    sVars->hyperPalette_Sonic[5]  = 4210816;
    sVars->hyperPalette_Sonic[6]  = 10526944;
    sVars->hyperPalette_Sonic[7]  = 8421568;
    sVars->hyperPalette_Sonic[8]  = 6316192;
    sVars->hyperPalette_Sonic[9]  = 12632288;
    sVars->hyperPalette_Sonic[10] = 10526944;
    sVars->hyperPalette_Sonic[11] = 8421568;
    sVars->hyperPalette_Sonic[12] = 14737632;
    sVars->hyperPalette_Sonic[13] = 12632288;
    sVars->hyperPalette_Sonic[14] = 10526944;
    sVars->hyperPalette_Sonic[15] = 14737632;
    sVars->hyperPalette_Sonic[16] = 14737632;
    sVars->hyperPalette_Sonic[17] = 14737632;
    sVars->hyperPalette_Sonic[18] = 12640480;
    sVars->hyperPalette_Sonic[19] = 10535136;
    sVars->hyperPalette_Sonic[20] = 8429792;
    sVars->hyperPalette_Sonic[21] = 14737632;
    sVars->hyperPalette_Sonic[22] = 14737632;
    sVars->hyperPalette_Sonic[23] = 14737632;
    sVars->hyperPalette_Sonic[24] = 12640448;
    sVars->hyperPalette_Sonic[25] = 10543264;
    sVars->hyperPalette_Sonic[26] = 57376;
    sVars->hyperPalette_Sonic[27] = 14737632;
    sVars->hyperPalette_Sonic[28] = 14737632;
    sVars->hyperPalette_Sonic[29] = 14737632;
    sVars->hyperPalette_Sonic[30] = 12640416;
    sVars->hyperPalette_Sonic[31] = 12640320;
    sVars->hyperPalette_Sonic[32] = 12632064;
    sVars->hyperPalette_Sonic[33] = 14737632;
    sVars->hyperPalette_Sonic[34] = 14737632;
    sVars->hyperPalette_Sonic[35] = 14737632;
    sVars->hyperPalette_Sonic[36] = 14737600;
    sVars->hyperPalette_Sonic[37] = 14737536;
    sVars->hyperPalette_Sonic[38] = 14729280;
    sVars->hyperPalette_Sonic[39] = 14737632;
    sVars->hyperPalette_Sonic[40] = 14737632;
    sVars->hyperPalette_Sonic[41] = 14737632;
    sVars->hyperPalette_Sonic[42] = 14737632;
    sVars->hyperPalette_Sonic[43] = 14729408;
    sVars->hyperPalette_Sonic[44] = 14721184;
    sVars->hyperPalette_Sonic[45] = 14737632;
    sVars->hyperPalette_Sonic[46] = 14737632;
    sVars->hyperPalette_Sonic[47] = 14737632;
    sVars->hyperPalette_Sonic[48] = 14737632;
    sVars->hyperPalette_Sonic[49] = 14729440;
    sVars->hyperPalette_Sonic[50] = 12624064;
    sVars->hyperPalette_Sonic[51] = 14737632;
    sVars->hyperPalette_Sonic[52] = 14737632;
    sVars->hyperPalette_Sonic[53] = 14737632;

    sVars->hyperPalette_Sonic_Water1[0]  = 2130080;
    sVars->hyperPalette_Sonic_Water1[1]  = 24704;
    sVars->hyperPalette_Sonic_Water1[2]  = 16480;
    sVars->hyperPalette_Sonic_Water1[3]  = 8421600;
    sVars->hyperPalette_Sonic_Water1[4]  = 6316224;
    sVars->hyperPalette_Sonic_Water1[5]  = 4210816;
    sVars->hyperPalette_Sonic_Water1[6]  = 10526944;
    sVars->hyperPalette_Sonic_Water1[7]  = 8421568;
    sVars->hyperPalette_Sonic_Water1[8]  = 6316192;
    sVars->hyperPalette_Sonic_Water1[9]  = 12632288;
    sVars->hyperPalette_Sonic_Water1[10] = 10526944;
    sVars->hyperPalette_Sonic_Water1[11] = 8421568;
    sVars->hyperPalette_Sonic_Water1[12] = 14737632;
    sVars->hyperPalette_Sonic_Water1[13] = 12632288;
    sVars->hyperPalette_Sonic_Water1[14] = 10526944;
    sVars->hyperPalette_Sonic_Water1[15] = 14737632;
    sVars->hyperPalette_Sonic_Water1[16] = 14737632;
    sVars->hyperPalette_Sonic_Water1[17] = 14737632;
    sVars->hyperPalette_Sonic_Water1[18] = 12640480;
    sVars->hyperPalette_Sonic_Water1[19] = 10535136;
    sVars->hyperPalette_Sonic_Water1[20] = 8429792;
    sVars->hyperPalette_Sonic_Water1[21] = 14737632;
    sVars->hyperPalette_Sonic_Water1[22] = 14737632;
    sVars->hyperPalette_Sonic_Water1[23] = 14737632;
    sVars->hyperPalette_Sonic_Water1[24] = 12640448;
    sVars->hyperPalette_Sonic_Water1[25] = 10543264;
    sVars->hyperPalette_Sonic_Water1[26] = 57376;
    sVars->hyperPalette_Sonic_Water1[27] = 14737632;
    sVars->hyperPalette_Sonic_Water1[28] = 14737632;
    sVars->hyperPalette_Sonic_Water1[29] = 14737632;
    sVars->hyperPalette_Sonic_Water1[30] = 12640416;
    sVars->hyperPalette_Sonic_Water1[31] = 12640320;
    sVars->hyperPalette_Sonic_Water1[32] = 12632064;
    sVars->hyperPalette_Sonic_Water1[33] = 14737632;
    sVars->hyperPalette_Sonic_Water1[34] = 14737632;
    sVars->hyperPalette_Sonic_Water1[35] = 14737632;
    sVars->hyperPalette_Sonic_Water1[36] = 14737600;
    sVars->hyperPalette_Sonic_Water1[37] = 14737536;
    sVars->hyperPalette_Sonic_Water1[38] = 14729280;
    sVars->hyperPalette_Sonic_Water1[39] = 14737632;
    sVars->hyperPalette_Sonic_Water1[40] = 14737632;
    sVars->hyperPalette_Sonic_Water1[41] = 14737632;
    sVars->hyperPalette_Sonic_Water1[42] = 14737632;
    sVars->hyperPalette_Sonic_Water1[43] = 14729408;
    sVars->hyperPalette_Sonic_Water1[44] = 14721184;
    sVars->hyperPalette_Sonic_Water1[45] = 14737632;
    sVars->hyperPalette_Sonic_Water1[46] = 14737632;
    sVars->hyperPalette_Sonic_Water1[47] = 14737632;
    sVars->hyperPalette_Sonic_Water1[48] = 14737632;
    sVars->hyperPalette_Sonic_Water1[49] = 14729440;
    sVars->hyperPalette_Sonic_Water1[50] = 12624064;
    sVars->hyperPalette_Sonic_Water1[51] = 14737632;
    sVars->hyperPalette_Sonic_Water1[52] = 14737632;
    sVars->hyperPalette_Sonic_Water1[53] = 14737632;

    sVars->hyperPalette_Sonic_Water2[0]  = 6316224;
    sVars->hyperPalette_Sonic_Water2[1]  = 4210848;
    sVars->hyperPalette_Sonic_Water2[2]  = 4202592;
    sVars->hyperPalette_Sonic_Water2[3]  = 14712960;
    sVars->hyperPalette_Sonic_Water2[4]  = 12607584;
    sVars->hyperPalette_Sonic_Water2[5]  = 8405056;
    sVars->hyperPalette_Sonic_Water2[6]  = 14721184;
    sVars->hyperPalette_Sonic_Water2[7]  = 12615808;
    sVars->hyperPalette_Sonic_Water2[8]  = 10510432;
    sVars->hyperPalette_Sonic_Water2[9]  = 14729408;
    sVars->hyperPalette_Sonic_Water2[10] = 14721184;
    sVars->hyperPalette_Sonic_Water2[11] = 12615808;
    sVars->hyperPalette_Sonic_Water2[12] = 14737632;
    sVars->hyperPalette_Sonic_Water2[13] = 14729408;
    sVars->hyperPalette_Sonic_Water2[14] = 14721184;
    sVars->hyperPalette_Sonic_Water2[15] = 14737632;
    sVars->hyperPalette_Sonic_Water2[16] = 14737632;
    sVars->hyperPalette_Sonic_Water2[17] = 14737632;
    sVars->hyperPalette_Sonic_Water2[18] = 12640480;
    sVars->hyperPalette_Sonic_Water2[19] = 10535136;
    sVars->hyperPalette_Sonic_Water2[20] = 8429792;
    sVars->hyperPalette_Sonic_Water2[21] = 14737632;
    sVars->hyperPalette_Sonic_Water2[22] = 14737632;
    sVars->hyperPalette_Sonic_Water2[23] = 14737632;
    sVars->hyperPalette_Sonic_Water2[24] = 12640448;
    sVars->hyperPalette_Sonic_Water2[25] = 10543264;
    sVars->hyperPalette_Sonic_Water2[26] = 57376;
    sVars->hyperPalette_Sonic_Water2[27] = 14737632;
    sVars->hyperPalette_Sonic_Water2[28] = 14737632;
    sVars->hyperPalette_Sonic_Water2[29] = 14737632;
    sVars->hyperPalette_Sonic_Water2[30] = 12640416;
    sVars->hyperPalette_Sonic_Water2[31] = 12640320;
    sVars->hyperPalette_Sonic_Water2[32] = 12632064;
    sVars->hyperPalette_Sonic_Water2[33] = 14737632;
    sVars->hyperPalette_Sonic_Water2[34] = 14737632;
    sVars->hyperPalette_Sonic_Water2[35] = 14737632;
    sVars->hyperPalette_Sonic_Water2[36] = 14737600;
    sVars->hyperPalette_Sonic_Water2[37] = 14737536;
    sVars->hyperPalette_Sonic_Water2[38] = 14729280;
    sVars->hyperPalette_Sonic_Water2[39] = 14737632;
    sVars->hyperPalette_Sonic_Water2[40] = 14737632;
    sVars->hyperPalette_Sonic_Water2[41] = 14737632;
    sVars->hyperPalette_Sonic_Water2[42] = 14737632;
    sVars->hyperPalette_Sonic_Water2[43] = 14729408;
    sVars->hyperPalette_Sonic_Water2[44] = 14721184;
    sVars->hyperPalette_Sonic_Water2[45] = 14737632;
    sVars->hyperPalette_Sonic_Water2[46] = 14737632;
    sVars->hyperPalette_Sonic_Water2[47] = 14737632;
    sVars->hyperPalette_Sonic_Water2[48] = 14737632;
    sVars->hyperPalette_Sonic_Water2[49] = 14729440;
    sVars->hyperPalette_Sonic_Water2[50] = 12624064;
    sVars->hyperPalette_Sonic_Water2[51] = 14737632;
    sVars->hyperPalette_Sonic_Water2[52] = 14737632;
    sVars->hyperPalette_Sonic_Water2[53] = 14737632;

    // Tails
    sVars->superPalette_Tails[0]  = 0xE0A000;
    sVars->superPalette_Tails[1]  = 0xE08000;
    sVars->superPalette_Tails[2]  = 0xA06040;
    sVars->superPalette_Tails[3]  = 0xE0C040;
    sVars->superPalette_Tails[4]  = 14721056;
    sVars->superPalette_Tails[5]  = 0xA06040;
    sVars->superPalette_Tails[6]  = 14729344;
    sVars->superPalette_Tails[7]  = 0xE0C040;
    sVars->superPalette_Tails[8]  = 12607552;
    sVars->superPalette_Tails[9]  = 14737568;
    sVars->superPalette_Tails[10] = 14729344;
    sVars->superPalette_Tails[11] = 14712896;
    sVars->superPalette_Tails[12] = 14729344;
    sVars->superPalette_Tails[13] = 0xE0C040;
    sVars->superPalette_Tails[14] = 12607552;
    sVars->superPalette_Tails[15] = 0xE0C040;
    sVars->superPalette_Tails[16] = 14721056;
    sVars->superPalette_Tails[17] = 0xA06040;

    sVars->superPalette_Tails_Water1[0]  = 14721220;
    sVars->superPalette_Tails_Water1[1]  = 12615776;
    sVars->superPalette_Tails_Water1[2]  = 10502240;
    sVars->superPalette_Tails_Water1[3]  = 0xE0C040;
    sVars->superPalette_Tails_Water1[4]  = 14721056;
    sVars->superPalette_Tails_Water1[5]  = 0xA06040;
    sVars->superPalette_Tails_Water1[6]  = 14729344;
    sVars->superPalette_Tails_Water1[7]  = 0xE0C040;
    sVars->superPalette_Tails_Water1[8]  = 12607552;
    sVars->superPalette_Tails_Water1[9]  = 14737568;
    sVars->superPalette_Tails_Water1[10] = 14729344;
    sVars->superPalette_Tails_Water1[11] = 14712896;
    sVars->superPalette_Tails_Water1[12] = 14729344;
    sVars->superPalette_Tails_Water1[13] = 0xE0C040;
    sVars->superPalette_Tails_Water1[14] = 12607552;
    sVars->superPalette_Tails_Water1[15] = 0xE0C040;
    sVars->superPalette_Tails_Water1[16] = 14721056;
    sVars->superPalette_Tails_Water1[17] = 0xA06040;

    sVars->superPalette_Tails_Water2[0]  = 14721120;
    sVars->superPalette_Tails_Water2[1]  = 12615776;
    sVars->superPalette_Tails_Water2[2]  = 10502240;
    sVars->superPalette_Tails_Water2[3]  = 0xE0C040;
    sVars->superPalette_Tails_Water2[4]  = 14721056;
    sVars->superPalette_Tails_Water2[5]  = 0xA06040;
    sVars->superPalette_Tails_Water2[6]  = 14729344;
    sVars->superPalette_Tails_Water2[7]  = 0xE0C040;
    sVars->superPalette_Tails_Water2[8]  = 12607552;
    sVars->superPalette_Tails_Water2[9]  = 14737568;
    sVars->superPalette_Tails_Water2[10] = 14729344;
    sVars->superPalette_Tails_Water2[11] = 14712896;
    sVars->superPalette_Tails_Water2[12] = 14729344;
    sVars->superPalette_Tails_Water2[13] = 0xE0C040;
    sVars->superPalette_Tails_Water2[14] = 12607552;
    sVars->superPalette_Tails_Water2[15] = 0xE0C040;
    sVars->superPalette_Tails_Water2[16] = 14721056;
    sVars->superPalette_Tails_Water2[17] = 0xA06040;

    // Knuckles
    sVars->superPalette_Knux[0]  = 14696544;
    sVars->superPalette_Knux[1]  = 12582944;
    sVars->superPalette_Knux[2]  = 6291488;
    sVars->superPalette_Knux[3]  = 14696576;
    sVars->superPalette_Knux[4]  = 12582976;
    sVars->superPalette_Knux[5]  = 6291488;
    sVars->superPalette_Knux[6]  = 14704800;
    sVars->superPalette_Knux[7]  = 14696544;
    sVars->superPalette_Knux[8]  = 8396864;
    sVars->superPalette_Knux[9]  = 14713024;
    sVars->superPalette_Knux[10] = 14704768;
    sVars->superPalette_Knux[11] = 10502240;
    sVars->superPalette_Knux[12] = 14721248;
    sVars->superPalette_Knux[13] = 14712992;
    sVars->superPalette_Knux[14] = 12607616;
    sVars->superPalette_Knux[15] = 14729440;
    sVars->superPalette_Knux[16] = 14721216;
    sVars->superPalette_Knux[17] = 14712992;
    sVars->superPalette_Knux[18] = 14737632;
    sVars->superPalette_Knux[19] = 14729440;
    sVars->superPalette_Knux[20] = 14721216;
    sVars->superPalette_Knux[21] = 14729440;
    sVars->superPalette_Knux[22] = 14721216;
    sVars->superPalette_Knux[23] = 14712992;
    sVars->superPalette_Knux[24] = 14721248;
    sVars->superPalette_Knux[25] = 14712992;
    sVars->superPalette_Knux[26] = 12607616;
    sVars->superPalette_Knux[27] = 14713024;
    sVars->superPalette_Knux[28] = 14704768;
    sVars->superPalette_Knux[29] = 10502240;
    sVars->superPalette_Knux[30] = 14704800;
    sVars->superPalette_Knux[31] = 14696544;
    sVars->superPalette_Knux[32] = 8396864;

    sVars->superPalette_Knux_Water1[0]  = 10510496;
    sVars->superPalette_Knux_Water1[1]  = 10494112;
    sVars->superPalette_Knux_Water1[2]  = 4202592;
    sVars->superPalette_Knux_Water1[3]  = 14696576;
    sVars->superPalette_Knux_Water1[4]  = 12582976;
    sVars->superPalette_Knux_Water1[5]  = 6291488;
    sVars->superPalette_Knux_Water1[6]  = 14704800;
    sVars->superPalette_Knux_Water1[7]  = 14696544;
    sVars->superPalette_Knux_Water1[8]  = 8396864;
    sVars->superPalette_Knux_Water1[9]  = 14713024;
    sVars->superPalette_Knux_Water1[10] = 14704768;
    sVars->superPalette_Knux_Water1[11] = 10502240;
    sVars->superPalette_Knux_Water1[12] = 14721248;
    sVars->superPalette_Knux_Water1[13] = 14712992;
    sVars->superPalette_Knux_Water1[14] = 12607616;
    sVars->superPalette_Knux_Water1[15] = 14729440;
    sVars->superPalette_Knux_Water1[16] = 14721216;
    sVars->superPalette_Knux_Water1[17] = 14712992;
    sVars->superPalette_Knux_Water1[18] = 14737632;
    sVars->superPalette_Knux_Water1[19] = 14729440;
    sVars->superPalette_Knux_Water1[20] = 14721216;
    sVars->superPalette_Knux_Water1[21] = 14729440;
    sVars->superPalette_Knux_Water1[22] = 14721216;
    sVars->superPalette_Knux_Water1[23] = 14712992;
    sVars->superPalette_Knux_Water1[24] = 14721248;
    sVars->superPalette_Knux_Water1[25] = 14712992;
    sVars->superPalette_Knux_Water1[26] = 12607616;
    sVars->superPalette_Knux_Water1[27] = 14713024;
    sVars->superPalette_Knux_Water1[28] = 14704768;
    sVars->superPalette_Knux_Water1[29] = 10502240;
    sVars->superPalette_Knux_Water1[30] = 14704800;
    sVars->superPalette_Knux_Water1[31] = 14696544;
    sVars->superPalette_Knux_Water1[32] = 8396864;

    sVars->superPalette_Knux_Water2[0]  = 12599392;
    sVars->superPalette_Knux_Water2[1]  = 8396896;
    sVars->superPalette_Knux_Water2[2]  = 4202592;
    sVars->superPalette_Knux_Water2[3]  = 14696576;
    sVars->superPalette_Knux_Water2[4]  = 12582976;
    sVars->superPalette_Knux_Water2[5]  = 6291488;
    sVars->superPalette_Knux_Water2[6]  = 14704800;
    sVars->superPalette_Knux_Water2[7]  = 14696544;
    sVars->superPalette_Knux_Water2[8]  = 8396864;
    sVars->superPalette_Knux_Water2[9]  = 14713024;
    sVars->superPalette_Knux_Water2[10] = 14704768;
    sVars->superPalette_Knux_Water2[11] = 10502240;
    sVars->superPalette_Knux_Water2[12] = 14721248;
    sVars->superPalette_Knux_Water2[13] = 14712992;
    sVars->superPalette_Knux_Water2[14] = 12607616;
    sVars->superPalette_Knux_Water2[15] = 14729440;
    sVars->superPalette_Knux_Water2[16] = 14721216;
    sVars->superPalette_Knux_Water2[17] = 14712992;
    sVars->superPalette_Knux_Water2[18] = 14737632;
    sVars->superPalette_Knux_Water2[19] = 14729440;
    sVars->superPalette_Knux_Water2[20] = 14721216;
    sVars->superPalette_Knux_Water2[21] = 14729440;
    sVars->superPalette_Knux_Water2[22] = 14721216;
    sVars->superPalette_Knux_Water2[23] = 14712992;
    sVars->superPalette_Knux_Water2[24] = 14721248;
    sVars->superPalette_Knux_Water2[25] = 14712992;
    sVars->superPalette_Knux_Water2[26] = 12607616;
    sVars->superPalette_Knux_Water2[27] = 14713024;
    sVars->superPalette_Knux_Water2[28] = 14704768;
    sVars->superPalette_Knux_Water2[29] = 10502240;
    sVars->superPalette_Knux_Water2[30] = 14704800;
    sVars->superPalette_Knux_Water2[31] = 14696544;
    sVars->superPalette_Knux_Water2[32] = 8396864;

#if ORIGINS_USE_PLUS
    // Amy
    sVars->superPalette_Amy[0]  = 11815056;
    sVars->superPalette_Amy[1]  = 16542972;
    sVars->superPalette_Amy[2]  = 16561404;
    sVars->superPalette_Amy[3]  = 7077960;
    sVars->superPalette_Amy[4]  = 9446508;
    sVars->superPalette_Amy[5]  = 13920432;
    sVars->superPalette_Amy[6]  = 16551164;
    sVars->superPalette_Amy[7]  = 16569596;
    sVars->superPalette_Amy[8]  = 9183336;
    sVars->superPalette_Amy[9]  = 11551884;
    sVars->superPalette_Amy[10] = 16025808;
    sVars->superPalette_Amy[11] = 16559356;
    sVars->superPalette_Amy[12] = 16573692;
    sVars->superPalette_Amy[13] = 11288712;
    sVars->superPalette_Amy[14] = 13657260;
    sVars->superPalette_Amy[15] = 16034032;
    sVars->superPalette_Amy[16] = 16567548;
    sVars->superPalette_Amy[17] = 16573692;
    sVars->superPalette_Amy[18] = 13394088;
    sVars->superPalette_Amy[19] = 15762636;
    sVars->superPalette_Amy[20] = 16042224;
    sVars->superPalette_Amy[21] = 16575740;
    sVars->superPalette_Amy[22] = 16573692;
    sVars->superPalette_Amy[23] = 15499464;
    sVars->superPalette_Amy[24] = 15770860;
    sVars->superPalette_Amy[25] = 16050416;
    sVars->superPalette_Amy[26] = 16575740;
    sVars->superPalette_Amy[27] = 16573692;
    sVars->superPalette_Amy[28] = 15507688;
    sVars->superPalette_Amy[29] = 15779052;
    sVars->superPalette_Amy[30] = 16050416;
    sVars->superPalette_Amy[31] = 16575740;
    sVars->superPalette_Amy[32] = 16573692;
    sVars->superPalette_Amy[33] = 15515880;
    sVars->superPalette_Amy[34] = 15787244;
    sVars->superPalette_Amy[35] = 16050416;
    sVars->superPalette_Amy[36] = 16575740;
    sVars->superPalette_Amy[37] = 16573692;
    sVars->superPalette_Amy[38] = 15507688;
    sVars->superPalette_Amy[39] = 15779052;
    sVars->superPalette_Amy[40] = 16042224;
    sVars->superPalette_Amy[41] = 16575740;
    sVars->superPalette_Amy[42] = 16573692;
    sVars->superPalette_Amy[43] = 15499464;
    sVars->superPalette_Amy[44] = 15770860;
    sVars->superPalette_Amy[45] = 16034032;
    sVars->superPalette_Amy[46] = 16567548;
    sVars->superPalette_Amy[47] = 16573692;
    sVars->superPalette_Amy[48] = 13394088;
    sVars->superPalette_Amy[49] = 15762636;
    sVars->superPalette_Amy[50] = 16025808;
    sVars->superPalette_Amy[51] = 16559356;
    sVars->superPalette_Amy[52] = 16573692;
    sVars->superPalette_Amy[53] = 11288712;
    sVars->superPalette_Amy[54] = 13657260;

    sVars->superPalette_Amy_Water1[0]  = 9191823;
    sVars->superPalette_Amy_Water1[1]  = 11951097;
    sVars->superPalette_Amy_Water1[2]  = 14059260;
    sVars->superPalette_Amy_Water1[3]  = 4587592;
    sVars->superPalette_Amy_Water1[4]  = 6953836;
    sVars->superPalette_Amy_Water1[5]  = 11297199;
    sVars->superPalette_Amy_Water1[6]  = 14056441;
    sVars->superPalette_Amy_Water1[7]  = 16164604;
    sVars->superPalette_Amy_Water1[8]  = 6692968;
    sVars->superPalette_Amy_Water1[9]  = 9059212;
    sVars->superPalette_Amy_Water1[10] = 13402575;
    sVars->superPalette_Amy_Water1[11] = 16161785;
    sVars->superPalette_Amy_Water1[12] = 16172796;
    sVars->superPalette_Amy_Water1[13] = 8798344;
    sVars->superPalette_Amy_Water1[14] = 11164588;
    sVars->superPalette_Amy_Water1[15] = 15507951;
    sVars->superPalette_Amy_Water1[16] = 16169977;
    sVars->superPalette_Amy_Water1[17] = 16180988;
    sVars->superPalette_Amy_Water1[18] = 10903720;
    sVars->superPalette_Amy_Water1[19] = 13269964;
    sVars->superPalette_Amy_Water1[20] = 15516143;
    sVars->superPalette_Amy_Water1[21] = 16178169;
    sVars->superPalette_Amy_Water1[22] = 16180988;
    sVars->superPalette_Amy_Water1[23] = 13009096;
    sVars->superPalette_Amy_Water1[24] = 15375340;
    sVars->superPalette_Amy_Water1[25] = 15524335;
    sVars->superPalette_Amy_Water1[26] = 16186361;
    sVars->superPalette_Amy_Water1[27] = 16180988;
    sVars->superPalette_Amy_Water1[28] = 15114472;
    sVars->superPalette_Amy_Water1[29] = 15383532;
    sVars->superPalette_Amy_Water1[30] = 15524335;
    sVars->superPalette_Amy_Water1[31] = 16186361;
    sVars->superPalette_Amy_Water1[32] = 16180988;
    sVars->superPalette_Amy_Water1[33] = 15122664;
    sVars->superPalette_Amy_Water1[34] = 15383532;
    sVars->superPalette_Amy_Water1[35] = 15524335;
    sVars->superPalette_Amy_Water1[36] = 16186361;
    sVars->superPalette_Amy_Water1[37] = 16180988;
    sVars->superPalette_Amy_Water1[38] = 15114472;
    sVars->superPalette_Amy_Water1[39] = 15383532;
    sVars->superPalette_Amy_Water1[40] = 15516143;
    sVars->superPalette_Amy_Water1[41] = 16178169;
    sVars->superPalette_Amy_Water1[42] = 16180988;
    sVars->superPalette_Amy_Water1[43] = 13009096;
    sVars->superPalette_Amy_Water1[44] = 15375340;
    sVars->superPalette_Amy_Water1[45] = 15507951;
    sVars->superPalette_Amy_Water1[46] = 16169977;
    sVars->superPalette_Amy_Water1[47] = 16180988;
    sVars->superPalette_Amy_Water1[48] = 10903720;
    sVars->superPalette_Amy_Water1[49] = 13269964;
    sVars->superPalette_Amy_Water1[50] = 13402575;
    sVars->superPalette_Amy_Water1[51] = 16161785;
    sVars->superPalette_Amy_Water1[52] = 16172796;
    sVars->superPalette_Amy_Water1[53] = 8798344;
    sVars->superPalette_Amy_Water1[54] = 11164588;

    sVars->superPalette_Amy_Water2[0]  = 11420304;
    sVars->superPalette_Amy_Water2[1]  = 16145658;
    sVars->superPalette_Amy_Water2[2]  = 16363260;
    sVars->superPalette_Amy_Water2[3]  = 6684744;
    sVars->superPalette_Amy_Water2[4]  = 9116780;
    sVars->superPalette_Amy_Water2[5]  = 13525680;
    sVars->superPalette_Amy_Water2[6]  = 16153850;
    sVars->superPalette_Amy_Water2[7]  = 16371452;
    sVars->superPalette_Amy_Water2[8]  = 8790120;
    sVars->superPalette_Amy_Water2[9]  = 11222156;
    sVars->superPalette_Amy_Water2[10] = 15631056;
    sVars->superPalette_Amy_Water2[11] = 16162042;
    sVars->superPalette_Amy_Water2[12] = 16379644;
    sVars->superPalette_Amy_Water2[13] = 10895496;
    sVars->superPalette_Amy_Water2[14] = 13327532;
    sVars->superPalette_Amy_Water2[15] = 15639280;
    sVars->superPalette_Amy_Water2[16] = 16170234;
    sVars->superPalette_Amy_Water2[17] = 16379644;
    sVars->superPalette_Amy_Water2[18] = 13000872;
    sVars->superPalette_Amy_Water2[19] = 15432908;
    sVars->superPalette_Amy_Water2[20] = 15647472;
    sVars->superPalette_Amy_Water2[21] = 16178426;
    sVars->superPalette_Amy_Water2[22] = 16379644;
    sVars->superPalette_Amy_Water2[23] = 15106248;
    sVars->superPalette_Amy_Water2[24] = 15441132;
    sVars->superPalette_Amy_Water2[25] = 15655664;
    sVars->superPalette_Amy_Water2[26] = 16186618;
    sVars->superPalette_Amy_Water2[27] = 16379644;
    sVars->superPalette_Amy_Water2[28] = 15114472;
    sVars->superPalette_Amy_Water2[29] = 15449324;
    sVars->superPalette_Amy_Water2[30] = 15655664;
    sVars->superPalette_Amy_Water2[31] = 16186618;
    sVars->superPalette_Amy_Water2[32] = 16379644;
    sVars->superPalette_Amy_Water2[33] = 15122664;
    sVars->superPalette_Amy_Water2[34] = 15457516;
    sVars->superPalette_Amy_Water2[35] = 15655664;
    sVars->superPalette_Amy_Water2[36] = 16186618;
    sVars->superPalette_Amy_Water2[37] = 16379644;
    sVars->superPalette_Amy_Water2[38] = 15114472;
    sVars->superPalette_Amy_Water2[39] = 15449324;
    sVars->superPalette_Amy_Water2[40] = 15647472;
    sVars->superPalette_Amy_Water2[41] = 16178426;
    sVars->superPalette_Amy_Water2[42] = 16379644;
    sVars->superPalette_Amy_Water2[43] = 15106248;
    sVars->superPalette_Amy_Water2[44] = 15441132;
    sVars->superPalette_Amy_Water2[45] = 15639280;
    sVars->superPalette_Amy_Water2[46] = 16170234;
    sVars->superPalette_Amy_Water2[47] = 16379644;
    sVars->superPalette_Amy_Water2[48] = 13000872;
    sVars->superPalette_Amy_Water2[49] = 15432908;
    sVars->superPalette_Amy_Water2[50] = 15631056;
    sVars->superPalette_Amy_Water2[51] = 16162042;
    sVars->superPalette_Amy_Water2[52] = 16379644;
    sVars->superPalette_Amy_Water2[53] = 10895496;
    sVars->superPalette_Amy_Water2[54] = 13327532;
#endif

    sVars->spindashChargeSpeeds[0]  = 1.0f;
    sVars->spindashChargeSpeeds[1]  = 1.0614005f;
    sVars->spindashChargeSpeeds[2]  = 1.125531f;
    sVars->spindashChargeSpeeds[3]  = 1.1926451f;
    sVars->spindashChargeSpeeds[4]  = 1.2630343f;
    sVars->spindashChargeSpeeds[5]  = 1.3370349f;
    sVars->spindashChargeSpeeds[6]  = 1.4150375f;
    sVars->spindashChargeSpeeds[7]  = 1.4974997f;
    sVars->spindashChargeSpeeds[8]  = 1.5849625f;
    sVars->spindashChargeSpeeds[9]  = 1.6780719f;
    sVars->spindashChargeSpeeds[10] = 1.7776076f;
    sVars->spindashChargeSpeeds[11] = 1.8845228f;
    sVars->spindashChargeSpeeds[12] = 2.0f;

    sVars->ringExtraLife = 100;
    sVars->savedLives    = 3;
    sVars->savedScore1UP = 50000;
    sVars->sonicFrames.Init();
    sVars->knuxFrames.Init();

    sVars->sfxJump.Init();
    sVars->sfxPeelCharge.Init();
    sVars->sfxHurt.Init();
    sVars->sfxFlying.Init();
    sVars->sfxTired.Init();
    sVars->sfxLand.Init();
    //
    sVars->sfxSwap.Init();
#if ORIGINS_USE_PLUS
    sVars->sfxHammerDash.Init();
#endif

    sVars->sfxRoll.Init();
    sVars->sfxCharge.Init();
    sVars->sfxRelease.Init();
    sVars->sfxPeelRelease.Init();
    sVars->sfxDropdash.Init();
    sVars->sfxLoseRings.Init();
    sVars->sfxPimPom.Init();
    sVars->sfxSkidding.Init();
    sVars->sfxGrab.Init();
    sVars->sfxSlide.Init();
    sVars->sfxTransform2.Init();
    sVars->sfxSwapFail.Init();
}

// ----------------------
// Extra Entity Functions
// ----------------------

bool32 Player::CanTransform(void) {
    if (!sceneInfo->timeEnabled)
        return false;

    return false;

    /*
    // Support for MegAmi's Super Cancel mod
    bool32 superCancel = false;
    Mod::List::LoadModInfo("SuperCancel", NULL, NULL, NULL, &superCancel);
    if (superCancel && !GameObject::Find("ERZSetup") && (this->state.Matches(&Player::State_Transform) || this->superState ==
    SuperStates::StateSuper)) return true;

    SaveRAM *saveRAM = SaveGame_GetSaveRAM();
    if (!saveRAM)
        return false;

    uint8 emeralds = saveRAM->chaosEmeralds;

    if (sVars->canSuperCB && !sVars->canSuperCB(false))
        return false;

    if (this->superState >= SuperStates::StateSuper || emeralds != 0x7F || this->rings < 50 || this->sidekick)
        return false;

    return true;
    */
}

bool32 Player::CanSwap(void) {
    auto sidekick = GameObject::Get<Player>(SLOT_PLAYER2);
    if (!sidekick->classID)
        return false;

    if (sVars->cantSwap || this->drawGroup == 2 || !sceneInfo->timeEnabled)
        return false;

    if (sVars->respawnTimer) {
        sVars->respawnTimer = 240;
        return false;
    }

    /*
    if (player->state == Player_State_Death || player->state == Player_State_Drown) {
        if (sidekick->state == Player_State_Death || sidekick->state == Player_State_Drown || sidekick->state == Player_State_EncoreRespawn
            || sidekick->state == Player_State_Static) {
            return false;
        }
    } else {
        if (player->state != Player_State_Ground && player->state != Player_State_Roll)
            return false;
        if (sidekick->state != Player_State_Ground && sidekick->state != Player_State_Roll)
            return false;
    }

    return true;
    */

    return false;
}

bool32 Player_Input_Gamepad_Hook(bool32 skippedState) {
    auto self = ((Player *)sceneInfo->entity);

    if (self->controllerID < PLAYER_COUNT) {
        ControllerState *controller = &controllerInfo[self->controllerID];

        /*
        if (self->state != ERZStart_State_PlayerSuperFly && self->state != ERZStart_State_PlayerRebound
            && !(self->state == Player_State_Static && self->animator.animationID == ANI_BUBBLE))
            Touch::Control4Dir(controller);
        else
            Touch::Control8Dir(controller);
            */

        Touch::Control4Dir(controller);

        // bool32 canSuper = Player_CanTransform(self) && !self->onGround;
        // bool32 canSwap  = Player_CanSwap(self) && globals->gameMode == MODE_ENCORE;

        bool32 canSuper       = false;
        bool32 canSwapGravity = sceneInfo->debugMode;

        int32 jumpX = screenInfo->center.x;
        int32 jumpY = 96;

        if (canSuper)
            jumpX = screenInfo[self->playerID].size.x + config.jumpDPadPos.x - 48;

        // fixes a bug with button vs touch
        bool32 touchedJump = false;
        if (Touch::CheckRect(jumpX, jumpY, screenInfo->size.x, screenInfo->size.y, NULL, NULL) >= 0) {
            controllerInfo->keyA.down |= true;
            controller->keyA.down = true;
            touchedJump           = true;
        }

        bool32 touchedPause = false;
        if (CheckTouchPause()) {
            controllerInfo->keyStart.down |= true;
            controller->keyStart.down = true;
            touchedPause              = true;
        }

        bool32 touchedDebug = false;
        if (sceneInfo->debugMode) {
            if (Touch::CheckRect(0, 0, 112, 56, NULL, NULL) >= 0) {
                controllerInfo->keyX.down |= true;
                controller->keyX.down = true;
                touchedDebug          = true;
            }
        }

        bool32 touchedSuper = false;
        if (canSuper) {
            if (Touch::CheckRect(jumpX - 64, jumpY, jumpX, screenInfo->size.y, NULL, NULL) >= 0) {
                controllerInfo->keyY.down |= true;
                controller->keyY.down = true;
                touchedSuper          = true;
            }

            if (!Player::modSVars->touchSuper && touchedSuper) {
                controllerInfo->keyY.press |= controllerInfo->keyY.down;
                controller->keyY.press |= controller->keyY.down;
            }
            Player::modSVars->touchSuper = controller->keyY.down;
        } else {
            Player::modSVars->touchSuper = 0;
        }

        bool32 touchedGrav = false;
        if (canSwapGravity) {
            if (Touch::CheckRect(screenInfo->size.x - 0x80, 0x20, screenInfo->size.x, 0x40, NULL, NULL) >= 0) {
                controllerInfo->keyY.down |= true;
                controller->keyY.down = true;
                touchedGrav           = true;
            }

            if (!Player::modSVars->touchSwap && touchedGrav) {
                controllerInfo->keyY.press |= controllerInfo->keyY.down;
                controller->keyY.press |= controller->keyY.down;
            }
            Player::modSVars->touchSwap = controller->keyY.down;
        } else {
            Player::modSVars->touchSwap = 0;
        }

        if (!Player::modSVars->touchJump && touchedJump) {
            controllerInfo->keyA.press |= controllerInfo->keyA.down;
            controller->keyA.press |= controller->keyA.down;
        }
        Player::modSVars->touchJump = controller->keyA.down;

        if (!Player::modSVars->touchDebug && touchedDebug) {
            controllerInfo->keyX.press |= controllerInfo->keyX.down;
            controller->keyX.press |= controller->keyX.down;
        }
        Player::modSVars->touchDebug = controller->keyX.down;

        if (!Player::modSVars->touchPause && touchedPause) {
            controllerInfo->keyStart.press |= controllerInfo->keyStart.down;
            controller->keyStart.press |= controller->keyStart.down;
        }
        Player::modSVars->touchPause = controller->keyStart.down;
    }

    return false;
}

} // namespace GameLogic