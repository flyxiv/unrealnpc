using System.IO;
using UnrealBuildTool;

public class LlmNpc: ModuleRules
{
	public LlmNpc(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
		PublicIncludePaths.Add(Path.GetFullPath(Path.Combine(ModuleDirectory, "Public")));
		PrivateIncludePaths.Add(Path.GetFullPath(Path.Combine(ModuleDirectory, "Private")));


		PublicDependencyModuleNames.AddRange(new[] {
			"Core", "CoreUObject", "Engine", "InputCore", "HTTP", "Json", "JsonUtilities" 
		});

        PrivateDependencyModuleNames.AddRange(new string[] { "Projects" });
    }
}

