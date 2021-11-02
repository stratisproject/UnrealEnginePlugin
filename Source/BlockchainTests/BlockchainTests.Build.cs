// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class BlockchainTests : ModuleRules
{
	public BlockchainTests(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;		
		
		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				"Blockchain"			
			}
		);
	}
}
