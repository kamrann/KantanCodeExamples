// Copyright 2016 Cameron Angus

using UnrealBuildTool;

public class A2_DetailsCustomizationEditor : ModuleRules
{
	public A2_DetailsCustomizationEditor(TargetInfo Target)
	{
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
