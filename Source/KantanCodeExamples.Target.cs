// Copyright 2016 Cameron Angus

using UnrealBuildTool;
using System.Collections.Generic;

public class KantanCodeExamplesTarget : TargetRules
{
	public KantanCodeExamplesTarget(TargetInfo Target): base(Target)
	{
		Type = TargetType.Game;

		ExtraModuleNames.AddRange( new string[] {
			"KantanCodeExamplesCommon",
			
			"A1_GatherSubclasses",
			
			"A2_DetailsCustomization",
		});
	}
}
