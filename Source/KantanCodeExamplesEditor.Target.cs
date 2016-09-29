// Copyright 2016 Cameron Angus

using UnrealBuildTool;
using System.Collections.Generic;

public class KantanCodeExamplesEditorTarget : TargetRules
{
	public KantanCodeExamplesEditorTarget(TargetInfo Target)
	{
		Type = TargetType.Editor;
	}

	//
	// TargetRules interface.
	//

	public override void SetupBinaries(
		TargetInfo Target,
		ref List<UEBuildBinaryConfiguration> OutBuildBinaryConfigurations,
		ref List<string> OutExtraModuleNames
		)
	{
		OutExtraModuleNames.AddRange( new string[] {
			"KantanCodeExamplesCommon",
			
			"A1_GatherSubclasses",
			
			"A2_DetailsCustomization",
			"A2_DetailsCustomizationEditor",
			}
			);
	}
}
