// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class WarLegend : ModuleRules
{
	public WarLegend(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] {
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"EnhancedInput",
			"AIModule",
			"NavigationSystem",
			"StateTreeModule",
			"GameplayStateTreeModule",
			"Niagara",
			"UMG",
			"Slate",
			"SlateCore",
			"GameplayMessageRuntime",
			"GameplayTags",
			"GameplayTasks",
			"GameplayAbilities"
		});

		PrivateDependencyModuleNames.AddRange(new string[] { });

		PublicIncludePaths.AddRange(new string[] {
			"WarLegend",
			"WarLegend/Variant_Strategy",
			"WarLegend/Variant_Strategy/UI",
			"WarLegend/Variant_TwinStick",
			"WarLegend/Variant_TwinStick/AI",
			"WarLegend/Variant_TwinStick/Gameplay",
			"WarLegend/Variant_TwinStick/UI"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
