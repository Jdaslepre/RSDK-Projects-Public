#pragma once

// ------------------
// Macros/Definitions
// ------------------

#define MATCH_VALUEDATA_SIZE (0x100)

// ---------------------
// Variable Declarations
// ---------------------

#ifndef NETWORKING_H
struct MultiplayerData {
    int32 type;
    int32 data[0x1FF];
};
#endif

extern MultiplayerData multiplayerDataIN;
extern MultiplayerData multiplayerDataOUT;

extern int32 matchValueData[MATCH_VALUEDATA_SIZE];
extern uint8 matchValueReadPos;
extern uint8 matchValueWritePos;

extern int32 vsGameLength;
extern int32 vsItemMode;
extern int32 vsPlayerID;
extern bool32 vsPlaying;

extern int32 sendCounter;

// ---------------------
// Function Declarations
// ---------------------

void TransmitGlobal(int32 *globalValue, const char *globalName);
void Receive2PVSMatchCode(int32 code);

struct UserData {
    enum DataTypes {
        TypeValue,
        TypeEntity,
        TypeStruct,
    };

    static bool32 receiveReady;

    static void Connect2PVS(int32 *gameLength, int32 *itemMode);
    static void Disconnect2PVS();
    static void SendEntity(int32 entityID, bool32 verify);
    static void SendValue(int32 value, bool32 verify);

    template <typename T> static void SendStruct(const T &value, bool32 verify) {
        multiplayerDataOUT.type = DataTypes::TypeStruct;
        std::memcpy(multiplayerDataOUT.data, &value, sizeof(T));
        if (onlineActive) {
            SendData(verify);
        }
    }

    static void ReceiveEntity(int32 entityID, bool32 incrementPos);
    static void ReceiveValue(int32 *value, bool32 incrementPos);

    template <typename T> static void ReceiveStruct(T *value, bool32 incrementPos) {
        if (onlineActive && receiveReady) {
            /*
            if (incrementPos == true) {
                if (multiplayerDataIN.type == DataTypes::TypeStruct) {
                    std::memcpy(value, multiplayerDataIN.data, sizeof(T));
                }
                multiplayerDataIN.type = 0;
            } else {
                std::memcpy(value, multiplayerDataIN.data, sizeof(T));
            }
            */
            if (multiplayerDataIN.type == DataTypes::TypeStruct) {
                std::memcpy(value, multiplayerDataIN.data, sizeof(T));
            }
           // multiplayerDataIN.type = DataTypes::TypeValue;
        }
    }

    static void TransmitGlobal(int32 *globalValue, const char *globalName);
    static void Receive2PVSData(MultiplayerData *data);
    static void Receive2PVSMatchCode(int32 code);
};
