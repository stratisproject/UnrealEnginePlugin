// Copyright Epic Games, Inc. All Rights Reserved.

using System.IO;
using UnrealBuildTool;

public class Trezor : ModuleRules
{
    public Trezor(ReadOnlyTargetRules Target) : base(Target)
    {

        Type = ModuleType.External;
        
        PublicIncludePaths.Add(Path.Combine(ModuleDirectory));
        
		if (Target.Platform == UnrealTargetPlatform.Win64)
		{
			PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "Libraries", "Release", "Win64", "trezor.lib"));
        } else if (Target.Platform == UnrealTargetPlatform.Win32)
		{
			PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "Libraries", "Release", "Win32", "trezor.lib"));
        } else if (Target.Platform == UnrealTargetPlatform.Mac)
		{
			PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "Libraries", "Release", "MacOS", "trezor.a"));
        }
    }
}
