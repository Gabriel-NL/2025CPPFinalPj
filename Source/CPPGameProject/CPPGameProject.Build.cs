// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class CPPGameProject : ModuleRules
{
	public CPPGameProject(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "PhysXVehicles", "HeadMountedDisplay" , "UMG"});

		PublicDefinitions.Add("HMD_MODULE_INCLUDED=1");
	}
}
