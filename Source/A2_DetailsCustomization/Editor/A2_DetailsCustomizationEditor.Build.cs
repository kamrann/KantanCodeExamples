// Copyright 2016 Cameron Angus

using UnrealBuildTool;

public class A2_DetailsCustomizationEditor : ModuleRules
{
	public A2_DetailsCustomizationEditor(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
		bEnforceIWYU = false;

		PublicDependencyModuleNames.AddRange(new string[] {
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"Slate",
			"SlateCore",
			"UnrealEd",
			"PropertyEditor",

			"KantanCodeExamplesCommon",
			"A2_DetailsCustomization",
		});
	}
}
