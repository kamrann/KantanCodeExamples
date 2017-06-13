// Copyright 2016 Cameron Angus

using UnrealBuildTool;

public class A2_DetailsCustomization : ModuleRules
{
	public A2_DetailsCustomization(ReadOnlyTargetRules Target) : base(Target)
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
	}
}
