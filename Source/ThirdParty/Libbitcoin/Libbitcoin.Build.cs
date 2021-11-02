using System.IO;
using UnrealBuildTool;

public class Libbitcoin : ModuleRules
{
	public Libbitcoin(ReadOnlyTargetRules Target) : base(Target)
	{
		Type = ModuleType.External;

		PublicIncludePaths.Add(Path.Combine(ModuleDirectory, "include"));

		if (Target.Platform == UnrealTargetPlatform.Win32 || Target.Platform == UnrealTargetPlatform.Win64)
		{
			string architecture = Target.Platform == UnrealTargetPlatform.Win32 ? "Win32" : "Win64";
			PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "bin", "Windows", architecture, "libbitcoin.lib"));
        }
        else if (Target.Platform == UnrealTargetPlatform.Mac)
        {
			PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "bin", "Mac", "libbitcoin.a"));
        }

		bUseRTTI = true;
		bEnableExceptions = true;
		bEnableUndefinedIdentifierWarnings = true;

		Definitions.Add("BOOST_DISABLE_ABI_HEADERS=1");
		Definitions.Add("WITH_BOOST_BINDING=1");
	}
}
