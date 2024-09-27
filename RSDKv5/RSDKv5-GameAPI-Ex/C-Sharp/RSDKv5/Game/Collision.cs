namespace RSDK
{
    public enum CollisionModes
    {
        CMODE_FLOOR,
        CMODE_LWALL,
        CMODE_ROOF,
        CMODE_RWALL,
    }

    public enum CollisionSides
    {
        C_NONE,
        C_TOP,
        C_LEFT,
        C_RIGHT,
        C_BOTTOM,
    }

    public struct Hitbox
    {
        public short left;
        public short top;
        public short right;
        public short bottom;
    }

    public struct CollisionSensor
    {
        public RSDK.Vector2 position;
        public bool32 collided;
        public byte angle;
    }

    public struct CollisionMask
    {
        public static byte[] floorMasks = new byte[Const.TILE_SIZE];
        public static byte[] lWallMasks = new byte[Const.TILE_SIZE];
        public static byte[] rWallMasks = new byte[Const.TILE_SIZE];
        public static byte[] roofMasks = new byte[Const.TILE_SIZE];
    }

    public struct TileInfo
    {
        public byte floorAngle;
        public byte lWallAngle;
        public byte rWallAngle;
        public byte roofAngle;
        public byte flag;
    }
}
