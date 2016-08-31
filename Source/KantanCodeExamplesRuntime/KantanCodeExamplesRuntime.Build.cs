// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;

public class KantanCodeExamplesRuntime : ModuleRules
{
	public KantanCodeExamplesRuntime(TargetInfo Target)
	{
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore" });

		PrivateDependencyModuleNames.AddRange(new string[] {  });

		if(UEBuildConfiguration.bBuildEditor)
		{
			PrivateDependencyModuleNames.Add("UnrealEd");
		}
	}
}
