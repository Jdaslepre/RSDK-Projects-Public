using System;

namespace RSDK;

public struct Vector2
{
	public int32 x, y = .();

	public this()
	{
	 	x = 0;
		y = 0;
	}

	public this(RSDK.Vector2 other)
	{
	    x = other.x;
	    y = other.y;
	}

	public this(RSDK.Vector2* other)
	{
	    x = other.x;
	    y = other.y;
	}

	public this(int32 X, int32 Y)
	{
	 	x = X;
		y = Y;
	}

	public bool CheckOnScreen(RSDK.Vector2 *range) mut { return RSDKTable.CheckPosOnScreen(&this, range); }
}

public struct Vector2<T> where T : var, IInteger
{
	public T x, y = .();

	public this()
	{
	 	x = 0;
		y = 0;
	}

	public this(RSDK.Vector2 other)
	{
	    x = other.x;
	    y = other.y;
	}

	public this(RSDK.Vector2* other)
	{
	    x = other.x;
	    y = other.y;
	}

	public this(int32 X, int32 Y)
	{
	 	x = X;
		y = Y;
	}

	public bool CheckOnScreen(RSDK.Vector2 *range) mut { return RSDKTable.CheckPosOnScreen((.)&this, range); }
}