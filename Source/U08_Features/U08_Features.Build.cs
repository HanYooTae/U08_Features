// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class U08_Features : ModuleRules
{
	public U08_Features(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "NavigationSystem", "AIModule", "ProceduralMeshComponent" });

		PublicIncludePaths.Add(ModuleDirectory);
    }

	
}
