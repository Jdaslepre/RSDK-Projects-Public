#ifndef NETWORKING_H
#define NETWORKING_H
#include <thread>
#include <memory>

#define PACKET_SIZE 0x1000

extern char networkHost[64];
extern char networkGame[7];
extern int32 networkPort;

extern float lastPing;
extern int32 dcError;
extern bool32 waitingForPing;

struct MultiplayerData {
    int32 type;
    int32 data[(PACKET_SIZE - 16) / sizeof(int) - 1];
};

struct ServerPacket {
    uint8 header  = 0;
    char game[7] = { 0, 0, 0, 0, 0, 0, 0 };
    uint32 player  = 0;
    uint32 room    = 0;

    union {
        unsigned char bytes[PACKET_SIZE - 16];
        MultiplayerData multiData;
    } data;
};

enum ClientHeaders {
    CL_REQUEST_CODE = 0x00,
    CL_JOIN         = 0x01,

    CL_DATA          = 0x10,
    CL_DATA_VERIFIED = 0x11,

    CL_QUERY_VERIFICATION = 0x20,

    CL_LEAVE = 0xFF
};
enum ServerHeaders {
    SV_CODES      = 0x00,
    SV_NEW_PLAYER = 0x01,

    SV_DATA          = 0x10,
    SV_DATA_VERIFIED = 0x11,

    SV_RECEIVED     = 0x20,
    SV_VERIFY_CLEAR = 0x21,

    SV_INVALID_HEADER = 0x80,
    SV_NO_ROOM        = 0x81,
    SV_UNKNOWN_PLAYER = 0x82,

    SV_LEAVE = 0xFF
};

class NetworkSession;
extern std::shared_ptr<NetworkSession> session;

void InitNetwork();
void RunNetwork();
void SendData(bool32 verify = false);
void DisconnectNetwork(bool32 finalClose = false);
void SendServerPacket(ServerPacket &send, bool32 verify = false);
int32 GetRoomCode();
void SetRoomCode(int32 code);
void SetNetworkGameName(int32 *unused, const char *name);
#endif