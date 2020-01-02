// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;

public class AProject : ModuleRules
{
	public AProject(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "GameplayTasks", "AIModule" , "UMG"});

		PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

        // Uncomment if you are using Slate UI
        // PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

        // Uncomment if you are using online features
        // PrivateDependencyModuleNames.Add("OnlineSubsystem");

        // To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
        string KProjectPath = ModuleDirectory;

        PublicSystemIncludePaths.Add(KProjectPath + "/Frame");
        PublicSystemIncludePaths.Add(KProjectPath + "/Frame/UMG");
        PublicSystemIncludePaths.Add(KProjectPath + "/Frame/Table");
        PublicSystemIncludePaths.Add(KProjectPath + "/Frame/Table/Xml");
        
        PublicSystemIncludePaths.Add(KProjectPath + "/Game");
        PublicSystemIncludePaths.Add(KProjectPath + "/Game/Character");
	}
}
