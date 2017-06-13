// Copyright 2016 Cameron Angus

using UnrealBuildTool;

public class KantanCodeExamplesCommon : ModuleRules
{
	public KantanCodeExamplesCommon(ReadOnlyTargetRules Target): base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
		bEnforceIWYU = false;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore" });
	}
}
