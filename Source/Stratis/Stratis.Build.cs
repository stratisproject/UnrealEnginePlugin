// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Stratis : ModuleRules
{
	public Stratis(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;		
		
		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				"StratisAPI"
			}
			);
	}
}
