using System;
using RSDK;

namespace GameLogic;

public class Game
{
	public static void** registerGlobals    = null;
	public static int32 registerGlobalsSize = 0;

	public static function void(void* globals) registerGlobalsInitCB = null;

	public void RegisterGlobals(void** globals, int32 size, function void(void* globals) initCB)
	{
		registerGlobals       = globals;
		registerGlobalsSize   = size;
		registerGlobalsInitCB = initCB;
	}

#if RETRO_REV02
	[Export, CLink, AlwaysInclude] public static void LinkGameLogicDLL(EngineInfo* info)
	{
		InitEngineInfo(info);
#else
	[Export, CLink, AlwaysInclude] public static void LinkGameLogicDLL(EngineInfo info)
	{
		InitEngineInfo(&info);
#endif

		if (registerGlobals != null)
		{
#if RETRO_REV0U
			// EngineAPI.RSDKTable.RegisterGlobalVariables(registerGlobals, registerGlobalsSize, registerGlobalsInitCB);
#else
			RSDKTable.RegisterGlobalVariables(registerGlobals, registerGlobalsSize);
#endif
		}

		for (int32 r = 0; r < GameObject.registerObjectListCount; ++r)
		{
			GameObject.ObjectRegistration* registration = &GameObject.registerObjectList[r];

			if (registration.name != null)
			{
				// modloader stuff needs to be added
				Dev.Print(.NORMAL, "auto registered:");

				Dev.Print(.NORMAL, registration.name);
				Dev.PrintInt32(.NORMAL, "entity size", (.)registration.entityClassSize);
				Dev.PrintInt32(.NORMAL, "static size", (.)registration.staticClassSize);
#if RETRO_REV0U
				RSDKTable.RegisterObject(registration.staticVars, registration.name, registration.entityClassSize, registration.staticClassSize,
					=> registration.update, => registration.lateUpdate, => registration.staticUpdate, => registration.draw,
					=> registration.create, => registration.stageLoad, => registration.editorDraw, => registration.editorLoad,
					=> registration.serialize, => registration.staticLoad);
#else
				RSDKTable.RegisterObject(registration.staticVars, registration.name, registration.entityClassSize, registration.staticClassSize,
					=> registration.update, => registration.lateUpdate, => registration.staticUpdate, => registration.draw,
					=> registration.create, => registration.stageLoad, => registration.editorDraw, => registration.editorLoad,
					=> registration.serialize);
#endif
			}
		}

#if RETRO_REV02
		for (int32 r = 0; r < GameObject.registerStaticListCount; ++r)
		{
			GameObject.ObjectRegistration* registration = &GameObject.registerStaticList[r];

			if (registration.name != null)
			{
				RSDKTable.RegisterStaticVariables((void**)registration.staticVars, registration.name, registration.staticClassSize);
			}
		}
#endif

		Dev.Print(.POPUP, "Your game, on beef :)");
		Dev.PrintInt32(.NORMAL, "sizeof(sceneInfo.entity)", sizeof(GameObject.Entity));

		Dev.PrintInt32(.NORMAL, "bool32 size", sizeof(bool32));
		Dev.PrintInt32(.NORMAL, "Boolean<uint32> size", sizeof(Boolean<uint32>));
		Dev.PrintInt32(.NORMAL, "Boolean<uint8> size", sizeof(Boolean<uint8>));

		StateMachine<Game> g = .();

		g.Set( => EvilState);
		g.Run(null);

		StateMachine<Game> e = .();

		e.Copy(&g);
		e.Run(null);
	}

	public static void EvilState() => Dev.Print(.NORMAL, "evil");
}
