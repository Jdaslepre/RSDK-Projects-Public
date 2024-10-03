using System;

namespace RSDK;

public struct SpriteSheet
{
	public uint16 id;

	public void Init() mut => id = (.)(-1);

	public void Load(char8* path, Scopes scopeType) mut { id = RSDKTable.LoadSpriteSheet(path, (.)scopeType); }

	public bool Loaded() { return id != (.)(-1); }

	public bool Matches(RSDK.SpriteSheet other) { return this.id == other.id; }
	public bool Matches(RSDK.SpriteSheet* other)
	{
		return other != null ? id == other.id : id == (.)(-1);
	}
}

[CRepr] public struct SpriteFrame
{
	public int16 sprX;
	public int16 sprY;
	public int16 width;
	public int16 height;
	public int16 pivotX;
	public int16 pivotY;
	public uint16 duration;
	public uint16 unicodeChar;
	public uint8 sheetID;
}

public struct SpriteAnimation
{
	public uint16 aniFrames;

	public void Init() mut => aniFrames = (.)(-1);

	public void Load(char8* path, Scopes scopeType) mut => aniFrames = RSDKTable.LoadSpriteAnimation(path, (.)scopeType);
	public void Create(char8* filename, uint32 frameCount, uint32 listCount, Scopes scopeType) mut => aniFrames = RSDKTable.CreateSpriteAnimation(filename, frameCount, listCount, (.)scopeType);

	public void Edit(uint16 listID, char8* name, int32 frameOffset, uint16 frameCount, int16 speed, uint8 loopIndex, uint8 rotationStyle) => RSDKTable.EditSpriteAnimation(aniFrames, listID, name, frameOffset, frameCount, speed, loopIndex, rotationStyle);

	public uint16 FindAnimation(char8* name) { return RSDKTable.FindSpriteAnimation(aniFrames, name); }

	public bool Loaded() { return aniFrames != (.)(-1); }

	public RSDK.SpriteFrame* GetFrame(int32 animID, int32 frameID) { return RSDKTable.GetFrame(aniFrames, (.)animID, frameID); }

	public bool Matches(RSDK.SpriteAnimation other) { return aniFrames == other.aniFrames; }
	public bool Matches(RSDK.SpriteAnimation* other)
	{
		return other != null ? aniFrames == other.aniFrames : aniFrames == (.)(-1);
	}
}