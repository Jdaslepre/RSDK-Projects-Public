using System;
using System.Collections;

namespace RSDK;

public enum ActiveFlags : uint8
{
	ACTIVE_NEVER, // never update
	ACTIVE_ALWAYS, // always update (even if paused/frozen)
	ACTIVE_NORMAL, // always update (unless paused/frozen)
	ACTIVE_PAUSED, // update only when paused/frozen
	ACTIVE_BOUNDS, // update if in x & y bounds
	ACTIVE_XBOUNDS, // update only if in x bounds (y bounds dont matter)
	ACTIVE_YBOUNDS, // update only if in y bounds (x bounds dont matter)
	ACTIVE_RBOUNDS, // update based on radius boundaries (updateRange.x == radius)

	// Not really even a real active value, but some objects set their active states to this so here it is I suppose
	ACTIVE_DISABLED = 0xFF,
}

public enum VariableTypes
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
	VAR_FLOAT, // Not actually used in Sonic Mania so it's just an assumption, but this is the only thing that'd fit the 32 bit limit and make sense
	VAR_COLOR,
}

public enum ForeachTypes
{
	ALL_ENTITIES,
	ACTIVE_ENTITIES,
#if RETRO_USE_MOD_LOADER && RETRO_MOD_LOADER_VER_2
	GROUP_ENTITIES,
#endif
}

public enum ForeachGroups
{
	GROUP_ALL,

	GROUP_CUSTOM0 = Const.TYPE_COUNT,
	GROUP_CUSTOM1,
	GROUP_CUSTOM2,
	GROUP_CUSTOM3,
}

public enum DefaultObjects : uint16
{
	TYPE_DEFAULTOBJECT = 0,
#if RETRO_REV02
	TYPE_DEVOUTPUT,
#endif
	TYPE_DEFAULT_COUNT, // max
}

public enum TileCollisionModes
{
	TILECOLLISION_NONE, // no tile collisions
	TILECOLLISION_DOWN, // downwards tile collisions
#if RETRO_REV0U
	TILECOLLISION_UP, // upwards tile collisions
#endif
}

[CRepr] public struct GameObject
{
	[CRepr] public struct Static
	{
		public uint16 classID;
		public uint8 active;

		public void EditableVar(VariableTypes type, char8* name, uint32 offset) => RSDKTable.SetEditableVar((.)type, name, (.)classID, (.)offset);
		public int32 Count(bool32 isActive = false) { return RSDKTable.GetEntityCount(classID, isActive); }

#if RETRO_USE_MOD_LOADER
		public void Super(int32 callback, void *data = null) => modTable.Super(classID, callback, data);
#endif
	}

	public interface IEntity
	{
		public void Create(void* data);
		public void Update();
		public void Draw();
		public void LateUpdate();
		public static void StageLoad();
		public static void Serialize();
		public static void StaticUpdate();
#if RETRO_REV0U
		public static void StaticLoad(void* sVars);
#endif
		public static void EditorLoad();
		public void EditorDraw();
	}

	[CRepr] public struct Entity : IEntity
	{
		public void Create(void* data) { }
		public void Update() { }
		public void Draw() { }
		public void LateUpdate() { }

		public static void StageLoad() { }
		public static void Serialize() { }
		public static void StaticUpdate() { }
#if RETRO_REV0U
		public static void StaticLoad(void* sVars)
		{
			var vrs = (Static*)sVars;
			vrs.classID = (.)DefaultObjects.TYPE_DEFAULTOBJECT;
			vrs.active  = (.)ActiveFlags.ACTIVE_NEVER;
		}
#endif
		public static void EditorLoad() { }
		public void EditorDraw() { }

#if RETRO_REV0U
		// used for languages such as beeflang that always have vfTables in classes
		public void* vfTable;
#endif

		public RSDK.Vector2 position;
		public RSDK.Vector2 scale;
		public RSDK.Vector2 velocity;
		public RSDK.Vector2 updateRange;
		public int32 angle;
		public int32 alpha;
		public int32 rotation;
		public int32 groundVel;
		public int32 zdepth;
		public uint16 group;
		public uint16 classID;
		public bool32 inRange;
		public bool32 isPermanent;
		public int32 tileCollisions;
		public bool32 interaction;
		public bool32 onGround;
		public ActiveFlags active;
#if RETRO_REV02
		public uint8 filter;
#endif
		public FlipFlags direction;
		public uint8 drawGroup;
		public uint8 collisionLayers;
		public uint8 collisionPlane;
		public uint8 collisionMode;
		public DrawFX drawFX;
		public InkEffects inkEffect;
		public Boolean<uint8> visible;
		public Boolean<uint8> onScreen;

		public void Init() mut
		{
			active        = .ACTIVE_BOUNDS;
			visible       = false;
			updateRange.x = RSDK.Math.TO_FIXED(128);
			updateRange.y = RSDK.Math.TO_FIXED(128);
		}

		public uint16 Slot() mut { return (.)RSDKTable.GetEntitySlot(&this); }
		public void Destroy() mut => RSDKTable.ResetEntity(&this, (.)DefaultObjects.TYPE_DEFAULTOBJECT, null);

		public void Reset(uint32 type, void* data) mut => RSDKTable.ResetEntity(&this, (.)type, data);
		public void Reset(uint32 type, int32 data) mut => RSDKTable.ResetEntity(&this, (.)type, RSDK.Math.INT_TO_VOID(data));

		public void Copy(GameObject.Entity* dst, bool32 clearThis) mut => RSDKTable.CopyEntity(dst, &this, clearThis);

		public bool32 CheckOnScreen(RSDK.Vector2* range) mut { return RSDKTable.CheckOnScreen(&this, range); }

		public void AddDrawListRef(uint8 drawGroup) mut => RSDKTable.AddDrawListRef(drawGroup, Slot());

		public bool32 TileCollision(uint16 collisionLayers, uint8 collisionMode, uint8 collisionPlane, int32 xOffset, int32 yOffset, bool32 setPos) mut
		{
			return RSDKTable.ObjectTileCollision(&this, collisionLayers, collisionMode, collisionPlane, xOffset, yOffset, setPos);
		}

		public bool32 TileGrip(uint16 collisionLayers, uint8 collisionMode, uint8 collisionPlane, int32 xOffset, int32 yOffset, int32 tolerance) mut
		{
			return RSDKTable.ObjectTileGrip(&this, collisionLayers, collisionMode, collisionPlane, xOffset, yOffset, tolerance);
		}

		public void ProcessMovement(RSDK.Hitbox* outerBox, RSDK.Hitbox* innerBox) mut => RSDKTable.ProcessObjectMovement(&this, outerBox, innerBox);

		public bool32 CheckCollisionTouchBox(RSDK.Hitbox* thisHitbox, GameObject.Entity* other, RSDK.Hitbox* otherHitbox) mut
		{
			return RSDKTable.CheckObjectCollisionTouchBox(&this, thisHitbox, other, otherHitbox);
		}

		public bool32 CheckCollisionTouchCircle(int32 thisRadius, GameObject.Entity* other, int32 otherRadius) mut
		{
			return RSDKTable.CheckObjectCollisionTouchCircle(&this, thisRadius, other, otherRadius);
		}

		public uint8 CheckCollisionBox(RSDK.Hitbox* thisHitbox, GameObject.Entity* other, RSDK.Hitbox* otherHitbox, bool32 setPos = true) mut
		{
			return RSDKTable.CheckObjectCollisionBox(&this, thisHitbox, other, otherHitbox, setPos);
		}

		public bool32 CheckCollisionPlatform(RSDK.Hitbox* thisHitbox, GameObject.Entity* other, RSDK.Hitbox* otherHitbox, bool32 setPos = true) mut
		{
			return RSDKTable.CheckObjectCollisionPlatform(&this, thisHitbox, other, otherHitbox, setPos);
		}

#if RETRO_USE_MOD_LOADER
		public void Super(int32 callback, void *data = null) => modTable.Super(classID, callback, data);
#endif
	}

	/*
	[CRepr] public class Entity : IEntity
	{
		public void Create(void* data) { }
		public void Update() { }
		public void Draw() { }
		public void LateUpdate() { }

		public static void StageLoad() { }
		public static void Serialize() { }
		public static void StaticUpdate() { }
		#if RETRO_REV0U
		public static void StaticLoad(void* sVars){}
		#endif
		public static void EditorLoad() { }
		public void EditorDraw() { }

		// vars
	#if RETRO_REV0U
		private void* vfTable;
	#endif

		public RSDK.Vector2 position;
		public RSDK.Vector2 scale;
		public RSDK.Vector2 velocity;
		public RSDK.Vector2 updateRange;
		public int32 angle;
		public int32 alpha;
		public int32 rotation;
		public int32 groundVel;
		public int32 zdepth;
		public uint16 group;
		public uint16 classID;
		public bool32 inRange;
		public bool32 isPermanent;
		public int32 tileCollisions;
		public bool32 interaction;
		public bool32 onGround;
		public ActiveFlags active;
	#if RETRO_REV02
		public uint8 filter;
	#endif
		public FlipFlags direction;
		public uint8 drawGroup;
		public uint8 collisionLayers;
		public uint8 collisionPlane;
		public uint8 collisionMode;
		public DrawFX drawFX;
		public InkEffects inkEffect;
		public Boolean<uint8> visible;
		public Boolean<uint8> onScreen;

		public uint16 Slot() { return (.)RSDKTable.GetEntitySlot(this); }
		public void Destroy() => RSDKTable.ResetEntity(this, 0, null);

		public void Reset(uint32 type, void* data) => RSDKTable.ResetEntity(this, (.)type, data);
		public void Reset(uint32 type, int32 data) => RSDKTable.ResetEntity(this, (.)type, RSDK.Math.INT_TO_VOID(data));

		public void Copy(GameObject.Entity dst, bool32 clearThis) => RSDKTable.CopyEntity(dst, this, clearThis);

		public bool32 CheckOnScreen(RSDK.Vector2* range) { return RSDKTable.CheckOnScreen(this, range); }

		public void AddDrawListRef(uint8 drawGroup) => RSDKTable.AddDrawListRef(drawGroup, Slot());

		public bool32 TileCollision(uint16 collisionLayers, uint8 collisionMode, uint8 collisionPlane, int32 xOffset, int32 yOffset, bool32 setPos)
		{
			return RSDKTable.ObjectTileCollision(this, collisionLayers, collisionMode, collisionPlane, xOffset, yOffset, setPos);
		}

		public bool32 TileGrip(uint16 collisionLayers, uint8 collisionMode, uint8 collisionPlane, int32 xOffset, int32 yOffset, int32 tolerance)
		{
			return RSDKTable.ObjectTileGrip(this, collisionLayers, collisionMode, collisionPlane, xOffset, yOffset, tolerance);
		}

		public void ProcessMovement(RSDK.Hitbox* outerBox, RSDK.Hitbox* innerBox) => RSDKTable.ProcessObjectMovement(this, outerBox, innerBox);

		public bool32 CheckCollisionTouchBox(RSDK.Hitbox* thisHitbox, GameObject.Entity other, RSDK.Hitbox* otherHitbox)
		{
			return RSDKTable.CheckObjectCollisionTouchBox(this, thisHitbox, other, otherHitbox);
		}

		public bool32 CheckCollisionTouchCircle(int32 thisRadius, GameObject.Entity other, int32 otherRadius)
		{
			return RSDKTable.CheckObjectCollisionTouchCircle(this, thisRadius, other, otherRadius);
		}

		public uint8 CheckCollisionBox(RSDK.Hitbox* thisHitbox, GameObject.Entity other, RSDK.Hitbox* otherHitbox, bool32 setPos = true)
		{
			return RSDKTable.CheckObjectCollisionBox(this, thisHitbox, other, otherHitbox, setPos);
		}

		public bool32 CheckCollisionPlatform(RSDK.Hitbox* thisHitbox, GameObject.Entity other, RSDK.Hitbox* otherHitbox, bool32 setPos = true)
		{
			return RSDKTable.CheckObjectCollisionPlatform(this, thisHitbox, other, otherHitbox, setPos);
		}

	#if RETRO_USE_MOD_LOADER
		public void Super(int32 callback, void *data = null) => modTable.Super(classID, callback, data);
	#endif
	}
	*/

	// untested
	public static GameObject.Entity* Create(void* data, int32 x, int32 y) { return (.)RSDKTable.CreateEntity((.)DefaultObjects.TYPE_DEFAULTOBJECT, data, x, y); }
	public static GameObject.Entity* Create(int32 data, int32 x, int32 y) { return (.)RSDKTable.CreateEntity((.)DefaultObjects.TYPE_DEFAULTOBJECT, RSDK.Math.INT_TO_VOID(data), x, y); }

	// untested
	public static T* Create<T>(void* data, int32 x, int32 y) where T : struct
	{
		typeof(T).GetField("sVars").Value.GetValue<Static*>(null, var fStatic);
		return (.)RSDKTable.CreateEntity(fStatic.classID, data, x, y);
	}

	// untested
	public static T* Create<T>(int32 data, int32 x, int32 y) where T : struct
	{
		typeof(T).GetField("sVars").Value.GetValue<Static*>(null, var fStatic);
		return (.)RSDKTable.CreateEntity(fStatic.classID, RSDK.Math.INT_TO_VOID(data), x, y);
	}

	public static GameObject.Entity* Get(uint16 slot) { return (.)RSDKTable.GetEntity(slot); }
	public static T* Get<T>(uint16 slot) where T : struct { return (.)RSDKTable.GetEntity(slot); }

	// untested
	public static int32 Count<T>(bool32 isActive = false) where T : struct
	{
		typeof(T).GetField("sVars").Value.GetValue<Static*>(null, var fStatic);
		return RSDKTable.GetEntityCount(fStatic.classID, isActive);
	}

	// untested
	public static void Copy(GameObject.Entity* dst, GameObject.Entity* src, bool32 clearSrc) => RSDKTable.CopyEntity(dst, src, clearSrc);
	public static void Copy(void* dst, void* src, bool32 clearSrc) => RSDKTable.CopyEntity(dst, src, clearSrc);

	// untested
	public static void Reset(uint16 slot, uint16 type, void* data) => RSDKTable.ResetEntitySlot(slot, type, data);
	public static void Reset(uint16 slot, uint16 type, int32 data) => RSDKTable.ResetEntitySlot(slot, type, RSDK.Math.INT_TO_VOID(data));

	// TODO: THIS

	public static List<Entity*> GetEntities(ForeachTypes type)
	{
		List<Entity*> list = null;

		Entity* entity = null;

		if (type == .ALL_ENTITIES)
		{
			while (RSDKTable.GetAllEntities((.)ForeachGroups.GROUP_ALL, (void**)&entity)) list.Add(entity);
		}
		else if (type == .ACTIVE_ENTITIES)
		{
			while (RSDKTable.GetActiveEntities((.)ForeachGroups.GROUP_ALL, (void**)&entity)) list.Add(entity);
		}
#if RETRO_USE_MOD_LOADER && RETRO_MOD_LOADER_VER_2
		else if (type == .GROUP_ENTITIES) {
			while (modTable.GetGroupEntities((.)ForeachGroups.GROUP_ALL, (void **)&entity)) list.Add(entity);
		}
#endif

		return list;
	}

	public static List<T*> GetEntities<T>(ForeachTypes type) where T : struct
	{
		typeof(T).GetField("sVars").Value.GetValue<Static*>(null, var fStatic);

		List<T*> list = null;

		uint16 group = fStatic != null ? fStatic.classID : (.)ForeachGroups.GROUP_ALL;

		T* entity = null;
		if (type == .ALL_ENTITIES)
		{
			while (RSDKTable.GetAllEntities(group, (.)&entity)) list.Add(entity);
		}
		else if (type == .ACTIVE_ENTITIES)
		{
			while (RSDKTable.GetActiveEntities(group, (void**)&entity)) list.Add(entity);
		}
#if RETRO_USE_MOD_LOADER && RETRO_MOD_LOADER_VER_2
		else if (type == .GROUP_ENTITIES) {
			while (modTable.GetGroupEntities(group, (void **)&entity)) list.Add(entity);
		}
#endif

		return list;
	}

	// untested
	public static int32 Find(char8* name) { return RSDKTable.FindObject(name); }

#if RETRO_USE_MOD_LOADER
	// untested
	public static void *FindClass(char8 *name) { return modTable.FindObject(name); }
#endif

#if GAME_INCLUDE_EDITOR
	public static void SetActiveVariable(int32 classID, char8 *name) => RSDKTable.SetActiveVariable(classID, name);
	public static void AddVarEnumValue(char8 *name) => RSDKTable.AddVarEnumValue(name);
#endif

	public struct ObjectRegistration
	{
		public char8* name;
		void* padding;
		public function void() update;
		public function void() lateUpdate;
		public function void() staticUpdate;
		public function void() draw;
		public function void(void* data) create;
		public function void() stageLoad;
#if GAME_INCLUDE_EDITOR
		public function void() editorLoad;
		public function void() editorDraw;
#endif
		public function void() serialize;
#if RETRO_REV0U
		public function void(void*) staticLoad;
#endif
		public void** staticVars;
		public uint32 entityClassSize;
		public uint32 staticClassSize;
#if RETRO_USE_MOD_LOADER
		public void** modStaticVars;
		public uint32 modStaticClassSize;
		public char8* inherit;
		public bool32 isModded;
#endif
	};

	[CRepr] public struct EntityBase : GameObject.Entity
	{
		public void[0x100]* data;
#if RETRO_REV0U
		public void *unknown;
#endif
	};

	public static int32 registerObjectListCount = 0;
	public static ObjectRegistration[Const.OBJECT_COUNT] registerObjectList;

#if RETRO_REV02
	public static int32 registerStaticListCount = 0;
	public static ObjectRegistration[Const.OBJECT_COUNT] registerStaticList;
#endif

	[AttributeUsage(.Class | .Struct, .ReflectAttribute, ReflectUser = .All)]
	public struct RegisterClassAttribute : Attribute, IOnTypeInit
	{
		public this() { }

		[Comptime]
		public void OnTypeInit(Type entityType, Self* prev)
		{
			if (entityType.IsGenericParam)
				return;

			System.String obj = entityType.GetName(.. scope .());
			System.String regFns = scope .();

#if GAME_INCLUDE_EDITOR
			#if RETRO_REV0U
			regFns.Append("=> _Update, => _LateUpdate, => StaticUpdate, => _Draw, => _Create, => StageLoad, => EditorLoad, => _EditorDraw, => Serialize, => StaticLoad");
			#else
			regFns.Append("=> _Update, => _LateUpdate, => StaticUpdate, => _Draw, => _Create, => StageLoad, => EditorLoad, => _EditorDraw, => Serialize, => null");
			#endif
#else
			#if RETRO_REV0U
			regFns.Append("=> _Update, => _LateUpdate, => StaticUpdate, => _Draw, => _Create, => StageLoad, => null, => null, => Serialize, => StaticLoad");
			#else
			regFns.Append("=> _Update, => _LateUpdate, => StaticUpdate, => _Draw, => Create, => StageLoad, => null, => null, => Serialize, => null");
			#endif
#endif

			Compiler.EmitTypeBody(entityType, scope $"""
									[Reflect] public static Static* sVars = GameObject.RegisterInternal<Self, Static>(ref sVars, "{obj}", {regFns});

									public static void _Create(void* data) => (*(Self*)(void*)&sceneInfo.entity).Create(data);
									public static void _Draw() => (*(Self*)(void*)&sceneInfo.entity).Draw();
									public static void _Update() => (*(Self*)(void*)&sceneInfo.entity).Update();
									public static void _LateUpdate() => (*(Self*)(void*)&sceneInfo.entity).LateUpdate();\n
									""");

#if GAME_INCLUDE_EDITOR
			Compiler.EmitTypeBody(entityType, scope $"public static void _EditorDraw() => (*(Self*)(void*)&sceneInfo.entity).EditorDraw();");
#endif
		}
	}

	public static staticVars* RegisterInternal<entity, staticVars>(ref staticVars* sVars, char8* name, function void() update, function void() lateUpdate, function void() staticUpdate, function void() draw,
		function void(void* data) create, function void() stageLoad, function void() editorLoad, function void() editorDraw,
		function void() serialize, function void(void* staticVars) staticLoad)
	{
		if (registerObjectListCount < Const.OBJECT_COUNT)
		{
			ObjectRegistration* object = &registerObjectList[registerObjectListCount++];
			Internal.MemSet(object, 0, sizeof(ObjectRegistration));
			object.name = name;
			object.update = update;
			object.lateUpdate = lateUpdate;
			object.staticUpdate = staticUpdate;
			object.draw = draw;
			object.create = create;
			object.stageLoad = stageLoad;
#if GAME_INCLUDE_EDITOR
			// these are null if GAME_INCLUDE_EDITOR is false, but
			// let's check anyways?
			object.editorLoad = editorLoad;
			object.editorDraw = editorDraw;
#endif
			object.serialize = serialize;
#if RETRO_REV0U
			// same here
			object.staticLoad = staticLoad;
#endif

			object.staticVars      = (.)(void**)&sVars;
			object.entityClassSize = (.)typeof(entity).Size;
			object.staticClassSize = (.)sizeof(staticVars);
		}

		sVars = null;
		return null;
	}
}
