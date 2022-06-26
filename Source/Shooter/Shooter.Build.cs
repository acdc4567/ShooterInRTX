// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Shooter : ModuleRules
{
	public Shooter(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "UMG","GameplayTasks","NavigationSystem","GameplayAbilities","GameplayTags","AIModule" });

		PrivateDependencyModuleNames.AddRange(new string[] {  });

		PublicIncludePaths.AddRange(new string[] {
		"Shooter/Public/Character"
		,"Shooter/Public/Animation"
		,"Shooter/Public/Weapons"
		,"Shooter/Public/PlayerControllers"
		,"Shooter/Public/GameModes"
		,"Shooter/Public/Ammunition"
		,"Shooter/Public/Enemy"
		,"Shooter/Public/Enemy/Tasks"
		,"Shooter/Public/Enemy/Services"
		,"Shooter/Public/Enemy/EQS"
		,"Shooter/Public/Components"
		,"Shooter/Public/Dev"
		,"Shooter/Public/GameStates"
		,"Shooter/Public/GameInstances"
		,"Shooter/Public/WeaponBuys"
		,"Shooter/Public/Attributes"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
