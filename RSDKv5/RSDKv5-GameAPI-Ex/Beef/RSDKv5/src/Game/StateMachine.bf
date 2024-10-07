using System;

namespace RSDK;

static
{
	public static char8* currentState = null;
}

public struct StateMachine<T>
{
	public enum Priority : uint8
	{
		NORMAL   = 0,
		LOCKED = 0xFF,
	}

	public void Init() mut => Internal.MemSet(&this, 0, sizeof(StateMachine<T>));

	public bool32 Set(function void() statePtr, Priority priorityType = .NORMAL) mut
	{
		if (priorityType < this.priority || this.priority == .LOCKED)
			return false;

		state = statePtr;
		timer = 0;
		priority = priorityType;

		return true;
	}

	public bool32 SetAndRun(function void() statePtr, GameObject.Entity* self, Priority priorityType = .NORMAL) mut
	{
		bool32 applied = Set(state, priorityType);
		if (applied)
			Run(self);
		return applied;
	}

	public bool32 QueueForTime(function void() statePtr, uint32 duration, Priority priorityType = .NORMAL) mut
	{
		if (priorityType < this.priority || this.priority == .LOCKED)
			return false;

		state = statePtr;
		timer    = (.)duration;
		priority = priorityType;

		return true;
	}

	public void Run(GameObject.Entity* entity) mut
	{
		if (timer != 0)
			timer--;

		if (state != null)
		{
			currentState = null;

#if RETRO_USE_MOD_LOADER
			bool32 skipState = modTable.HandleRunState_HighPriority(state);

			if (!skipState)
				state();

			modTable.HandleRunState_LowPriority(state, skipState);
#else
			state();
#endif
		}
	}

	public bool32 Matches(function void() other) { return state == other; }

	public void Copy(StateMachine<T>* other) mut => Internal.MemCpy(&this, other, sizeof(StateMachine<T>));

	public function void() state;
	public int32 timer;
	private uint8[3] unknown;
	public Priority priority;
}