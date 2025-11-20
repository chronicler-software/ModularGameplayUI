// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class ModularGameplayUI : ModuleRules
{
	public ModularGameplayUI(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
		
		PublicIncludePaths.AddRange(
			new string[] {
			}
			);
				
		
		PrivateIncludePaths.AddRange(
			new string[] {
			}
			);
			
		
		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"CommonLoadingScreen",
				"Core",
				"EnhancedInput",
				"GameplayTags",
				"ModularGameplayData",
				"ModularGameplayExperiences",
				"UIExtension"
			}
			);
			
		
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"CommonGame",
				"CommonInput",
				"CommonUI",
				"CommonUser",
				"ControlFlows",
				"CoreUObject",
				"Engine",
				"GameFeatures",
				"GameplayAbilities",
				"ModularGameplay",
				"ModularGameplayAbilities",
				"ModularGameplayActors",
				"ModularGameplayData",
				"ModularGameplayExperiences",
				"Slate",
				"SlateCore",
				"UIExtension",
				"UMG",
				"WebRTC",
			}
			);
		
		
		DynamicallyLoadedModuleNames.AddRange(
			new string[]
			{
			}
			);
	}
}
