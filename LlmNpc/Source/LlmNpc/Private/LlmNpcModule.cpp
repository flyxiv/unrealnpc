#include "LlmNpcModule.h"

#define LOCTEXT_NAMESPACE "LlmNpc"

void FLlmNpcModule::StartupModule() {
	UE_LOG(LogTemp, Display, TEXT("LLM NPC module starting up"));
}

void FLlmNpcModule::ShutdownModule() {
	UE_LOG(LogTemp, Display, TEXT("LLM NPC module shutting down"));
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FLlmNpcModule, LlmNpc)
