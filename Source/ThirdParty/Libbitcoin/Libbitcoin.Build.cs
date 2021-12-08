using System.IO;
using UnrealBuildTool;

public class Libbitcoin : ModuleRules
{

	private static readonly string[] WindowsLibs = { 
		"libbitcoin-system.lib",
		"secp256k1.lib",
		"libboost_atomic-vc142-mt-{0}-1_77.lib",
		"libboost_chrono-vc142-mt-{0}-1_77.lib",
		"libboost_date_time-vc142-mt-{0}-1_77.lib",
		"libboost_filesystem-vc142-mt-{0}-1_77.lib",
		"libboost_iostreams-vc142-mt-{0}-1_77.lib",
		"libboost_locale-vc142-mt-{0}-1_77.lib",
		"libboost_log_setup-vc142-mt-{0}-1_77.lib",
		"libboost_log-vc142-mt-{0}-1_77.lib",
		"libboost_program_options-vc142-mt-{0}-1_77.lib",
		"libboost_regex-vc142-mt-{0}-1_77.lib",
		"libboost_system-vc142-mt-{0}-1_77.lib",
		"libboost_thread-vc142-mt-{0}-1_77.lib",
		"libboost_unit_test_framework-vc142-mt-{0}-1_77.lib"
	};

	public Libbitcoin(ReadOnlyTargetRules Target) : base(Target)
	{
		Type = ModuleType.External;

		PublicIncludePaths.Add(Path.Combine(ModuleDirectory, "include"));

		bUseRTTI = true;
		bEnableExceptions = true;
		bEnableUndefinedIdentifierWarnings = true;

		PublicDefinitions.Add("BOOST_DISABLE_ABI_HEADERS=1");
		PublicDefinitions.Add("WITH_BOOST_BINDING=1");
		PublicDefinitions.Add("BC_STATIC");	
		PublicDefinitions.Add("SECP256K1_BUILD");	

		if (Target.Platform == UnrealTargetPlatform.Win32 || Target.Platform == UnrealTargetPlatform.Win64)
		{
			string architecture = Target.Platform == UnrealTargetPlatform.Win32 ? "x32" : "x64";

			foreach (var library in WindowsLibs)
			{
				var fullLibraryName = string.Format(library, architecture);
				PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "bin", "Windows", architecture, fullLibraryName));
			}
        }
        else if (Target.Platform == UnrealTargetPlatform.Mac)
        {
			PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "bin", "Mac", "libbitcoin.a"));
        }
	}
}
