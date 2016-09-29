// Copyright 2016 Cameron Angus

using UnrealBuildTool;

public class A1_GatherSubclasses : ModuleRules
{
	public A1_GatherSubclasses(TargetInfo Target)
	{
		PublicDependencyModuleNames.AddRange(new string[] {
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",

			"KantanCodeExamplesCommon",
		});

		if(UEBuildConfiguration.bBuildEditor)
		{
			PrivateDependencyModuleNames.Add("UnrealEd");
		}
	}
}
