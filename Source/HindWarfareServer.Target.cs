using UnrealBuildTool;
using System.Collections.Generic;

public class HindWarfareServerTarget : TargetRules
{
	public HindWarfareServerTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Server;
		ExtraModuleNames.Add("HindWarfare");
	}
}
