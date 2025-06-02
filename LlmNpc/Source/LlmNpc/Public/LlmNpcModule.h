#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleInterface.h"

struct whisper_context;

class FLlmNpcModule : public IModuleInterface
{
public:
    virtual void StartupModule() override;
    virtual void ShutdownModule() override;

    static inline FLlmNpcModule& Get() {
        return FModuleManager::GetModuleChecked<FLlmNpcModule>("LlmNpc");
    }

private:
    whisper_context* _context = nullptr;
};