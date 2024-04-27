// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class ExposeDiffCommand : ModuleRules
{
	public ExposeDiffCommand(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
			}
		);
		
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"AssetTools",
				"CoreUObject",
				"UnrealEd",
			}
		);
	}
}
