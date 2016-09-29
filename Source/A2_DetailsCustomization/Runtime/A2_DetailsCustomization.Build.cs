// Copyright 2016 Cameron Angus

using UnrealBuildTool;

public class A2_DetailsCustomization : ModuleRules
{
	public A2_DetailsCustomization(TargetInfo Target)
	{
		PublicDependencyModuleNames.AddRange(new string[] {
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",

			"KantanCodeExamplesCommon",
		});
	}
}
