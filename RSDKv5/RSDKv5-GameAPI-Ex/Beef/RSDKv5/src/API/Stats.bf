#if RETRO_REV02
namespace RSDK
{
    public struct StatInfo
    {
        public uint8 statID;
        public char8* name;
        public void[64] *data;
    }

    namespace API
    {
        public class Stats
        {
            public static void TryTrackStat(RSDK.StatInfo* stat) => APITable.TryTrackStat(stat);
            public static bool32 GetEnabled() { return APITable.GetStatsEnabled(); }
            public static void SetEnabled(bool32 enabled) => APITable.SetStatsEnabled(enabled);
        }
    }
}
#endif