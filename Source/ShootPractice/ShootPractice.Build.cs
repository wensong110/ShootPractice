// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class ShootPractice : ModuleRules
{
	public ShootPractice(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore","UMG" });
	}
}
