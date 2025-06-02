#include "LlmRequest/LlmNpcBPLibrary.h"

void ULlmNpcBlueprintLibrary::RequestNpcResponse(const FString& Command, ALlmControlledNpc* Npc, ALlmContextSubsystem* LevelContext) {
	LlmApiRequestHandler::Get().RequestLlmNpcResponse(Command, Npc, LevelContext);
}

void ULlmNpcBlueprintLibrary::RequestNpcAction(const FString& UserMessage, ALlmContextSubsystem* LevelContext) {
	LlmApiRequestHandler::Get().RequestLlmNpcAction(UserMessage, LevelContext);
}

