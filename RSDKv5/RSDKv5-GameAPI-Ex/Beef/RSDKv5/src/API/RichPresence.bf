namespace RSDK.API;

public class RichPresence
{
	public static void Set(int32 id, RSDK.String *text) => APITable.SetRichPresence(id, text);
}