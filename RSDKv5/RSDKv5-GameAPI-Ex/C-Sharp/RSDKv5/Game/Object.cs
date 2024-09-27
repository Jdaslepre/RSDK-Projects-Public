using System.Diagnostics.CodeAnalysis;
using System.Runtime.InteropServices;
using static RSDK.EngineAPI;

namespace RSDK
{
    public enum ActiveFlags : byte
    {
        ACTIVE_NEVER,
        ACTIVE_ALWAYS,
        ACTIVE_NORMAL,
        ACTIVE_PAUSED,
        ACTIVE_BOUNDS,
        ACTIVE_XBOUNDS,
        ACTIVE_YBOUNDS,
        ACTIVE_RBOUNDS,

        // Not really even a real active value, but some objects set their active states to this so here it is I suppose
        ACTIVE_DISABLED = 0xFF,
    }

    public enum VarTypes
    {
        VAR_UINT8,
        VAR_UINT16,
        VAR_UINT32,
        VAR_INT8,
        VAR_INT16,
        VAR_INT32,
        VAR_ENUM,
        VAR_BOOL,
        VAR_STRING,
        VAR_VECTOR2,
        VAR_FLOAT,
        VAR_COLOR,
    }

    public enum ObjectClassIDs : ushort
    {
        TYPE_BLANK,
#if RETRO_REV02
        TYPE_DEVOUTPUT,
#endif
    }

    public enum TileCollisionModes : byte
    {
        TILECOLLISION_NONE, // no tile collisions
        TILECOLLISION_DOWN, // downwards tile collisions
#if RETRO_REV0U
        TILECOLLISION_UP, // upwards tile collisions
#endif
    }

    public class GameObject
    {
        public struct Static
        {
            public ushort classID;
            public byte active;

            public unsafe void EditableVar(byte type, string name, int offset) => RSDKTable.SetEditableVar(type, name, (byte)classID, offset);
            public unsafe int Count(uint isActive = 0) { return RSDKTable.GetEntityCount(classID, isActive); }
        }

        public unsafe interface IEntity
        {
            void Create(void* data);
            void Update();
            void Draw();
            void LateUpdate();
#if GAME_INCLUDE_EDITOR
            void EditorDraw();
#endif
            void StageLoad();
            void Serialize();
            void StaticUpdate();
            void StaticLoad(void* sVars);
#if GAME_INCLUDE_EDITOR
            void EditorLoad();
#endif
        }




        [StructLayout(LayoutKind.Sequential)]
        public unsafe class Entity : IEntity
        {
            public void Create(void* data) { }
            public void Update() { }
            public void Draw() { }
            public void LateUpdate() { }
#if GAME_INCLUDE_EDITOR
            public void EditorDraw() { }
#endif
            public void StageLoad() { }
            public void Serialize() { }
            public void StaticUpdate() { }
            public void StaticLoad(void* data)
            {
                var sVars = (Static*)data;

                sVars->classID = (ushort)ObjectClassIDs.TYPE_BLANK;
                sVars->active = (byte)ActiveFlags.ACTIVE_NEVER;
            }
#if GAME_INCLUDE_EDITOR
            public void EditorLoad() { }
#endif

#if RETRO_REV0U
            private void* vfTable;
#endif
            public RSDK.Vector2 position;
            public RSDK.Vector2 scale;
            public RSDK.Vector2 velocity;
            public RSDK.Vector2 updateRange;
            public int angle;
            public int alpha;
            public int rotation;
            public int groundVel;
            public int zdepth;
            public ushort group;
            public ushort classID;
            public bool32 inRange;
            public bool32 isPermanent;
            public int tileCollisions;
            public bool32 interaction;
            public bool32 onGround;
            public ActiveFlags active;
#if RETRO_REV02
            public byte filter;
#endif
            public FlipFlags direction;
            public byte drawGroup;
            public byte collisionLayers;
            public byte collisionPlane;
            public TileCollisionModes collisionMode;
            public DrawFX drawFX;
            public InkEffects inkEffect;
            public byte visible;
            public byte onScreen;
        }

        public unsafe struct DelegateTypes
        {
            public delegate void TakesVoidPtr(void* data);
        }

        public static unsafe void Register<[DynamicallyAccessedMembers(DynamicallyAccessedMemberTypes.PublicMethods)] _TypeEntity, _TypeStatic>(ref _TypeStatic* sVars) where _TypeEntity : class
        {
            if (ObjectRegInfo.registerListCount >= 0x400)
                return;

            Type E = typeof(_TypeEntity);
            var @object = new ObjectRegistration
            {
                name = E.Name,
                update = Managed.GetFieldPtr<Action>(E, "_Update"),
                lateUpdate = Managed.GetFieldPtr<Action>(E, "_LateUpdate"),
                staticUpdate = Managed.GetFieldPtr<Action>(E, "StaticUpdate"),
                draw = Managed.GetFieldPtr<Action>(E, "_Draw"),
                create = Managed.GetFieldPtr<DelegateTypes.TakesVoidPtr>(E, "_Create"),
                stageLoad = Managed.GetFieldPtr<Action>(E, "StageLoad"),
#if GAME_INCLUDE_EDITOR
                editorLoad = Managed.GetFieldPtr<Action>(E, "EditorLoad"),
                editorDraw = Managed.GetFieldPtr<Action>(E, "_EditorDraw"),
#endif
                serialize = Managed.GetFieldPtr<Action>(E, "Serialize"),
#if RETRO_REV0U
                staticLoad = Managed.GetFieldPtr<DelegateTypes.TakesVoidPtr>(E, "StaticLoad"),
#endif
            };

            fixed (_TypeStatic** pSvars = &sVars)
            {
                RSDKTable.RegisterObject(
                    (void**)pSvars,
                    @object.name,
                    (uint)sizeof(_TypeEntity),
                    (int)sizeof(_TypeStatic),
                    @object.update,
                    @object.lateUpdate,
                    @object.staticUpdate,
                    @object.draw,
                    @object.create,
                    @object.stageLoad,
                    @object.editorLoad,
                    @object.editorDraw,
                    @object.serialize,
                    @object.staticLoad
                );
            }

            ObjectRegInfo.registerList[ObjectRegInfo.registerListCount++] = @object;
            sVars = null;
        }
    }

    [AttributeUsage(AttributeTargets.Class, Inherited = false)]
    public class RSDKDeclareAttribute : Attribute
    {
        private static Type _objType;

        public RSDKDeclareAttribute(Type objType)
        {
            _objType = objType;
        }

        // TODO:
    }

    public unsafe struct ObjectRegistration
    {
        public string name;
        public IntPtr update;
        public IntPtr lateUpdate;
        public IntPtr staticUpdate;
        public IntPtr draw;
        public IntPtr create;
        public IntPtr stageLoad;
        public IntPtr serialize;
        public IntPtr editorLoad;
        public IntPtr editorDraw;
        public IntPtr staticLoad;

        public void** staticVars;
        public int entityClassSize;
        public int staticClassSize;
    }

    public class ObjectRegInfo
    {
        public static int registerListCount = 0;
        public static ObjectRegistration[] registerList = new ObjectRegistration[0x400];

    }
}
