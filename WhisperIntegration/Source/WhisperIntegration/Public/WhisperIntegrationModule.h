/* --------------------------------
    Defines core implmementation
    for integrating whisper.cpp
    into Unreal 5
--------------------------------- */

#pragma once

#include "whisper.h"
#include "CoreMinimal.h"
#include "Modules/ModuleInterface.h"

struct whisper_context;

class FWhisperIntegrationModule : public IModuleInterface
{
public:
    virtual void StartupModule() override;
    virtual void ShutdownModule() override;

    static inline FWhisperIntegrationModule& Get() {
        return FModuleManager::GetModuleChecked<FWhisperIntegrationModule>("WhisperIntegration");
    }

    bool InitializeModel(const FString& ModelPath);
    FString TranscribeFromBuffer(const float* PCMData, int32 SampleCount);

private:
    whisper_context* _context = nullptr;
};