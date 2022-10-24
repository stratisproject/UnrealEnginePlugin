// Copyright Epic Games, Inc. All Rights Reserved.

using System.IO;
using UnrealBuildTool;

public class Trezor : ModuleRules
{
    public Trezor(ReadOnlyTargetRules Target) : base(Target)
    {

        Type = ModuleType.External;
        
		if (Target.Platform == UnrealTargetPlatform.Win64)
		{
			PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "Libraries", "Release", "Win64", "trezor.lib"));
        }
    }
}
