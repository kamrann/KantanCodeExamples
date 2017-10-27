// Copyright 2016 Cameron Angus

using UnrealBuildTool;

public class A1_GatherSubclasses : ModuleRules
{
	public A1_GatherSubclasses(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
		bEnforceIWYU = false;

		PublicDependencyModuleNames.AddRange(new string[] {
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",

			"KantanCodeExamplesCommon",
		});

		if(Target.bBuildEditor)
		{
			PrivateDependencyModuleNames.Add("UnrealEd");
		}
	}
}
