using System.IO;
using UnrealBuildTool;

public class Libbitcoin : ModuleRules
{
	public Libbitcoin(ReadOnlyTargetRules Target) : base(Target)
	{
		Type = ModuleType.External;

		if (Target.Platform == UnrealTargetPlatform.Win64)
		{

        }
		else if (Target.Platform == UnrealTargetPlatform.Win32)
		{
			
        }
        else if (Target.Platform == UnrealTargetPlatform.Mac)
        {
			// PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "bin", "Mac", "libbitcoin.a"));
        }
	}
}
