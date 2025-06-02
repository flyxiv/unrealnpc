using System.IO;
using UnrealBuildTool;

public class WhisperIntegration : ModuleRules
{
	public WhisperIntegration(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
		PublicIncludePaths.Add(Path.GetFullPath(Path.Combine(ModuleDirectory, "Public")));
		PrivateIncludePaths.Add(Path.GetFullPath(Path.Combine(ModuleDirectory, "Private")));


		PublicDependencyModuleNames.AddRange(new[] {
			"Core", "CoreUObject", "Engine", "InputCore", "AudioCaptureCore", "SignalProcessing"
		});

		string ThirdPartyPath = Path.Combine(ModuleDirectory, "..", "ThirdParty", "whisper.cpp");
		PublicIncludePaths.Add(Path.Combine(ThirdPartyPath, "include"));

		string LibPath = Path.Combine(ThirdPartyPath, "lib");
		string[] NeededLibs = { "whisper.lib", "ggml.lib", "ggml-base.lib", "ggml-cuda.lib", "ggml-cpu.lib" };

		foreach (string Lib in NeededLibs)
		{
			PublicAdditionalLibraries.Add(Path.Combine(LibPath, Lib));
		}

        string CudaPath = System.Environment.GetEnvironmentVariable("CUDA_PATH");
        if (!string.IsNullOrEmpty(CudaPath))
        {
            string CudaLibPath = Path.Combine(CudaPath, "lib", "x64");
            if (Directory.Exists(CudaLibPath))
            {
                PublicAdditionalLibraries.Add(Path.Combine(CudaLibPath, "cudart.lib"));
                PublicAdditionalLibraries.Add(Path.Combine(CudaLibPath, "cublas.lib")); 
                PublicAdditionalLibraries.Add(Path.Combine(CudaLibPath, "cuda.lib")); 
                System.Console.WriteLine($"Info: Added CUDA runtime libraries from: {CudaLibPath}");
            }
            else
            {
                System.Console.WriteLine($"Warning: CUDA lib path not found: {CudaLibPath}");
            }
        }
        else
        {
            System.Console.WriteLine("Warning: CUDA_PATH environment variable not found. CUDA libraries will not be linked, which will cause linker errors if CUDA backend is used.");
        }    
    }
}

