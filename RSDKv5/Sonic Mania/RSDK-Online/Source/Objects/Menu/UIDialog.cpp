#include "RSDK-Online.hpp"

using namespace RSDK;

namespace GameLogic {

// -------------------
// Object Registration
// -------------------

MOD_REGISTER_OBJECT(UIDialog);

// ----------------
// Public Functions
// ----------------

UIDialog* (*UIDialog_CreateDialogOk)(String *text, void (*callback)(void), bool32 closeOnSelect) = nullptr;

} // namespace GameLogic