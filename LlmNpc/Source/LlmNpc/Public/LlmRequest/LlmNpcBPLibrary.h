/* --------------------------------
	Defines Blueprint API
	for using LLM NPC 
	in Blueprint Environment
--------------------------------- */

#pragma once

#include "LlmRequest/LlmApiRequestHandler.h"
#include "LlmGameObjects/LlmContextSubsystem.h"
#include "LlmGameObjects/LlmControlledNpc.h"

#include "LlmNpcBPLibrary.generated.h"

UCLASS()
class LLMNPC_API ULlmNpcBlueprintLibrary: public UBlueprintFunctionLibrary 
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "LLM NPC", meta = (WorldContext = "WorldContextObject", DisplayName = "Request Response To LLM"))
	static void RequestNpcResponse(
		const FString& Command, 
		ALlmControlledNpc* Npc, 
		ALlmContextSubsystem* LevelContext
	);

	UFUNCTION(BlueprintCallable, Category = "LLM NPC", meta = (DisplayName = "Request Action to LLM"))
	static void RequestNpcAction(const FString& UserMessage, ALlmContextSubsystem* LevelContext);

};