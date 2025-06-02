#include "WhisperIntegrationModule.h"
#include "Misc/Paths.h"
#include "HAL/PlatformMisc.h"

#define LOCTEXT_NAMESPACE "FWhisperIntegrationModule"

void FWhisperIntegrationModule::StartupModule()
{
    UE_LOG(LogTemp, Display, TEXT("WhisperIntegration module starting up"));
    InitializeModel("Models/ggml-base.bin");
}

void FWhisperIntegrationModule::ShutdownModule()
{
    if (_context) {
        whisper_free(_context);
        _context = nullptr;
    }

    UE_LOG(LogTemp, Display, TEXT("WhisperIntegration module shutting down"));
}

bool FWhisperIntegrationModule::InitializeModel(const FString& ModelPath) {
    if (_context) return true;

    FString FullPath = FPaths::ProjectContentDir() / ModelPath;


	whisper_context_params PARAMS;
	PARAMS.use_gpu = true;
	PARAMS.gpu_device = 0;

    _context = whisper_init_from_file_with_params(TCHAR_TO_UTF8(*FullPath), PARAMS);

    if (!_context) {
        UE_LOG(LogTemp, Error, TEXT("Failed to load model in path: %s"), *FullPath);
	}
	else {
		UE_LOG(LogTemp, Display, TEXT("Loaded Model!!!!!!"));
	}

    return _context != nullptr;
}

FString FWhisperIntegrationModule::TranscribeFromBuffer(const float* PCMData, int32 SampleCount) 
{
	if (!_context)
	{
		UE_LOG(LogTemp, Error, TEXT("Whisper model not initialized!"));
		return FString();
	}


	whisper_full_params Params = whisper_full_default_params(WHISPER_SAMPLING_GREEDY);
	Params.n_threads = FMath::Max(1, FPlatformMisc::NumberOfCoresIncludingHyperthreads());
	Params.offset_ms = 0;
	Params.translate = false;
	Params.print_realtime = false;
	Params.logprob_thold = -1.0f;
	Params.no_speech_thold = 0.0f;
	Params.language = "ko";

	int32 Success = whisper_full(_context, Params, PCMData, SampleCount);
	if (Success != 0)
	{
		UE_LOG(LogTemp, Error, TEXT("whisper_full failed: %d"), Success);
		return FString();
	}

    FString ResultText = TEXT("");
    const int NumSegments = whisper_full_n_segments(_context);

    for (int32 i = 0; i < NumSegments; ++i) {
        const char* SegmentTextAnsi = whisper_full_get_segment_text(_context, i);
        if (SegmentTextAnsi)
        {
            ResultText += FString(UTF8_TO_TCHAR(SegmentTextAnsi));
        }
    }

	return ResultText;
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FWhisperIntegrationModule, WhisperIntegration)