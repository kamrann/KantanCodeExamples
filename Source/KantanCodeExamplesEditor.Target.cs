// Copyright 2016 Cameron Angus

using UnrealBuildTool;
using System.Collections.Generic;

public class KantanCodeExamplesEditorTarget : TargetRules
{
	public KantanCodeExamplesEditorTarget(TargetInfo Target): base(Target)
	{
		Type = TargetType.Editor;

		ExtraModuleNames.AddRange( new string[] {
			"KantanCodeExamplesCommon",
			
			"A1_GatherSubclasses",
			
			"A2_DetailsCustomization",
			"A2_DetailsCustomizationEditor",
		});
	}
}
