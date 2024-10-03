using System;

namespace RSDK;

public class Video
{
	public bool32 LoadVideo(char8* filename, double startDelay, function bool32() skipCallback)
	{
		return RSDKTable.LoadVideo(filename, startDelay, skipCallback);
	}

	public bool32 LoadImage(char8* filename, double displayLength, double speed, function bool32() skipCallback)
	{
		return RSDKTable.LoadImage(filename, displayLength, speed, skipCallback);
	}
}