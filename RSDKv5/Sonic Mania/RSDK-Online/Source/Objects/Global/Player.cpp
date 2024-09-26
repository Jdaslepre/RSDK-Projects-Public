#include "RSDK-Online.hpp"

using namespace RSDK;

namespace GameLogic {

// -------------------
// Object Registration
// -------------------

MOD_REGISTER_OBJECT(Player);

// ----------------
// Public Functions
// ----------------

bool32 (*Player_CheckValidState)(Player *player) = nullptr;

// ----------------------
// Extra Entity Functions
// ----------------------

void Player::Update() {
    auto p1 = GameObject::Get<Player>(SLOT_PLAYER1);

    if (onlineActive) {
        // Host? send some values over to the session
        if (vsPlayerID == 0) {

            PlayerManage::InitDataSource(p1);
            UserData::SendStruct(PlayerManage::src, false);
        }

        // Any other player? receive them
        if (vsPlayerID != 0) {
            UserData::ReceiveStruct(&PlayerManage::src, true);
            PlayerManage::ApplyDataSourceToPlayer(p1);

            if (config.useDynamicStateSystem) {
                PlayerManage::HandleStates(p1);
            }
        }
    }

    sVars->Super(SUPER_UPDATE);
}

} // namespace GameLogic