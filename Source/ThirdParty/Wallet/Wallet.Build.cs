// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Wallet : ModuleRules
{
    public Wallet(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(
            new string[]
            {
                "Core",
                "Trezor"
            }
            );

        bUseRTTI = true;
        bEnableExceptions = true;
        bEnableUndefinedIdentifierWarnings = true;

        CppStandard = CppStandardVersion.Cpp17;
        ShadowVariableWarningLevel = WarningLevel.Off;

        if (Target.Platform == UnrealTargetPlatform.Win64)
        {
            PublicDefinitions.Add("__STDC_WANT_SECURE_LIB__=1");
            PublicAdditionalLibraries.Add("bcrypt.lib");
        }
    }
}
