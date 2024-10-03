using System;
using static System.Windows;
using RSDK;

namespace GameLogic;

[AlwaysInclude]
public class Program
{
	public static this()
	{
	}

	public static ~this()
	{
	}

	public static int Main(System.String[] args)
	{
		return 0;
	}

	enum DLL_REASON
	{
		DLL_PROCESS_DETACH,
		DLL_PROCESS_ATTACH,
		DLL_THREAD_ATTACH,
		DLL_THREAD_DETACH
	}


	/*
	[LinkName(.C), AlwaysInclude]
	public static IntBool WinMain(void* module, void* prevModule, char8* args, int32 showCmd)
	{
		return 0;
	}

	[Export, CLink]
	public IntBool DllMain(HInstance handle, uint32 fdwReason, void* lpvReserved)
	{
		// Perform actions based on the reason for calling.
		switch ((DLL_REASON)fdwReason)
		{
		case .DLL_PROCESS_ATTACH:
			// Initialize once for each new process.
			// Return FALSE to fail DLL load.
			break;

		case .DLL_THREAD_ATTACH:
			// Do thread-specific initialization.
			break;

		case .DLL_THREAD_DETACH:
			// Do thread-specific cleanup.
			break;

		case .DLL_PROCESS_DETACH:
			if (lpvReserved != null)
			{
				break; // do not do cleanup if process termination scenario
			}

			// Perform any necessary cleanup.
			break;
		}


		return true; // Successful DLL_PROCESS_ATTACH.
	}
	*/

}
