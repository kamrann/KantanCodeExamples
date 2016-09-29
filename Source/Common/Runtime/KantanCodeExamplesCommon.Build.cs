// Copyright 2016 Cameron Angus

using UnrealBuildTool;

public class KantanCodeExamplesCommon : ModuleRules
{
	public KantanCodeExamplesCommon(TargetInfo Target)
	{
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore" });
	}
}
