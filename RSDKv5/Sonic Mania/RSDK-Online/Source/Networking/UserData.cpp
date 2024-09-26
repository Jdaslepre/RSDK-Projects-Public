#include "RSDK-Online.hpp"

// --------------------
// Variable Definitions
// --------------------

MultiplayerData multiplayerDataIN  = MultiplayerData();
MultiplayerData multiplayerDataOUT = MultiplayerData();

int32 matchValueData[MATCH_VALUEDATA_SIZE];
uint8 matchValueReadPos  = 0;
uint8 matchValueWritePos = 0;

int32 vsGameLength = 4;
int32 vsItemMode   = ManiaItemModes::ITEMS_RANDOM;
int32 vsPlayerID   = 0;
bool32 vsPlaying   = false;

int32 sendCounter = 0;

bool32 UserData::receiveReady = false;

// --------------------
// Function Definitions
// --------------------

bool32 disableFocusPause_Store = false;

void UserData::Connect2PVS(int32 *gameLength, int32 *itemMode) {
    Dev::Print(Dev::PRINT_NORMAL, "Attempting to connect to network game (%d) (%d)", *gameLength, *itemMode);

    multiplayerDataIN.type = 0;
    matchValueData[0]      = 0;
    matchValueData[1]      = 0;
    matchValueReadPos      = 0;
    matchValueWritePos     = 0;
    Misc::callbackState    = Misc::OnlineCBStates::CONNECT2PVS;

    // PauseSound();
    // actual connection code
    vsGameLength = *gameLength;
    vsItemMode   = *itemMode;
    if (onlineActive) {
        // disableFocusPause_Store = disableFocusPause;
        // disableFocusPause       = 3;
        RunNetwork();
    }
}

void UserData::Disconnect2PVS() {
    Dev::Print(Dev::PRINT_NORMAL, "Attempting to disconnect from network game");

    if (onlineActive) {
        // disableFocusPause = disableFocusPause_Store;
        // Engine.devMenu    = vsPlayerID;
        vsPlaying = false;
        DisconnectNetwork();
        InitNetwork();
    }
}

void UserData::SendEntity(int32 entityID, bool32 verify) {
    //if (!sendCounter) {
        multiplayerDataOUT.type = DataTypes::TypeEntity;
        std::memcpy(multiplayerDataOUT.data, GameObject::Get(entityID), sizeof(GameObject::Entity));
        if (onlineActive) {
            SendData(verify);
        }
    //}
    //sendCounter = (sendCounter + 1) % 2;
}

void UserData::ReceiveEntity(int32 entityID, bool32 incrementPos) {
    if (onlineActive && receiveReady) {
        /*
        if (incrementPos == true) {
            if (multiplayerDataIN.type == 1) {
                std::memcpy(GameObject::Get(entityID), multiplayerDataIN.data, sizeof(GameObject::Entity));
            }
            multiplayerDataIN.type = 0;
        } else {
            std::memcpy(GameObject::Get(entityID), multiplayerDataIN.data, sizeof(GameObject::Entity));
        }
        */
        if (multiplayerDataIN.type == DataTypes::TypeEntity) {
            std::memcpy(GameObject::Get(entityID), multiplayerDataIN.data, sizeof(GameObject::Entity));
        }
        //multiplayerDataIN.type = DataTypes::TypeValue;
    }
}

void UserData::SendValue(int32 value, bool32 verify) {
    // Dev::Print(Dev::PRINT_NORMAL, "Attempting to send value (%d) (%d)", *dataSlot, *value);

    multiplayerDataOUT.type    = 0;
    multiplayerDataOUT.data[0] = value;
    if (onlineActive) {
        SendData(verify);
    }
}

void UserData::ReceiveValue(int32 *value, bool32 incrementPos) {
    // Dev::Print(Dev::PRINT_NORMAL, "Attempting to receive value (%d) (%d)", *incrementPos, *value);

    if (onlineActive && UserData::receiveReady) {
        // receiveReady = false;
        if (incrementPos == 1) {
            if (matchValueReadPos != matchValueWritePos) {
                *value = matchValueData[matchValueReadPos];
                matchValueReadPos++;
            }
        } else {
            *value = matchValueData[matchValueReadPos];
        }
    }
}

// update
void TransmitGlobal(int32 *globalValue, const char *globalName) {
    Dev::Print(Dev::PRINT_NORMAL, "Attempting to transmit global (%s) (%d)", globalName, *globalValue);

    multiplayerDataOUT.type = 2;
    // multiplayerDataOUT.data[0] = GetGlobalVariableID(globalName);
    multiplayerDataOUT.data[1] = *globalValue;
    if (onlineActive) {
        SendData();
    }
}

void UserData::Receive2PVSData(MultiplayerData *data) {
    receiveReady = true;
    switch (data->type) {
        case DataTypes::TypeValue: matchValueData[matchValueWritePos++] = data->data[0]; break;
        case DataTypes::TypeEntity:
            multiplayerDataIN.type = DataTypes::TypeEntity;
            GameObject::Copy(multiplayerDataIN.data, data->data, false);
            break;
        case DataTypes::TypeStruct:
            multiplayerDataIN.type = UserData::DataTypes::TypeStruct;
            std::memcpy(multiplayerDataIN.data, data->data, sizeof(data->data));
            break;
        default: break;
    }
}

void Receive2PVSMatchCode(int32 code) {
    UserData::receiveReady = true;
    code &= 0x00000FF0;
    code |= 0x00001000 * vsPlayerID;
    matchValueData[matchValueWritePos++] = code;
    // ResumeSound();
    // vsPlayerID = Engine.devMenu;
    // Engine.devMenu  = false;
    Misc::callbackState = 0;
    vsPlaying           = true;

    GameObject::Create<GameLogic::MultiplayerHandler>(nullptr, NULL, NULL);
}