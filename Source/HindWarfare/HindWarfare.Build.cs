using UnrealBuildTool;

public class HindWarfare : ModuleRules
{
	public HindWarfare(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "PhysicsCore" });
	}
}
