// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Frog_Puzzle : ModuleRules
{
	public Frog_Puzzle(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] 
		{ 
			"Core", 
			"CoreUObject", 
			"Engine", 
			"InputCore", 
			"EnhancedInput", 
			"OnlineSubsystem", 
			"OnlineSubsystemSteam",
            "OnlineSubsystemUtils",
            "AdvancedSessions", 
			"AdvancedSteamSessions",
			"Steamworks"
        });
	}
}
