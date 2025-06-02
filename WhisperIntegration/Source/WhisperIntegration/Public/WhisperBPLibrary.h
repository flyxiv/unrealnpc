/* --------------------------------
    Defines Blueprint API 
    for using WhisperIntegration 
	in Blueprint Environment
--------------------------------- */

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "AudioMixerDevice.h"
#include "AudioDeviceManager.h"
#include "Engine/World.h"
#include "WhisperBPLibrary.generated.h"

static TUniquePtr<Audio::FAudioRecordingData> RecordData;

UCLASS()
class WHISPERINTEGRATION_API UWhisperBPLibrary : public UBlueprintFunctionLibrary // 모듈 API 매크로 확인!
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Whisper Integration", meta = (WorldContext = "WorldContextObject", DisplayName = "Translate Mic To Text(Whisper)"))
	static FString TranslateMicToText(const UObject* WorldContextObject, USoundSubmix* SubmixToRecord = nullptr);

	UFUNCTION(BlueprintCallable, Category = "Whisper Integration", meta = (DisplayName = "Transcribe Audio Buffer (Whisper)"))
	static FString TranscribeAudioBuffer(const TArray<float> &PCMData);

};
