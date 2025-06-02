#pragma once

#include "CoreMinimal.h"

#include "HttpModule.h" 
#include "Interfaces/IHttpResponse.h"

#include "Dom/JsonObject.h"
#include "Serialization/JsonReader.h"
#include "Serialization/JsonSerializer.h"
#include "JsonObjectConverter.h"  

#include "LlmGameObjects/LlmContextSubsystem.h"
#include "LlmGameObjects/LlmControlledNpc.h"

static FString LlmApiRequestBuffer;

class LlmApiRequestHandler
{
public:
	LlmApiRequestHandler();
	LlmApiRequestHandler(const LlmApiRequestHandler& handler) = delete;
	LlmApiRequestHandler(LlmApiRequestHandler&& handler) = delete;
	const LlmApiRequestHandler& operator=(const LlmApiRequestHandler& handler) = delete;
	const LlmApiRequestHandler& operator=(LlmApiRequestHandler&& handler) = delete;

	static void RequestLlmNpcResponse(const FString& Command, ALlmControlledNpc* Npc, ALlmContextSubsystem* LevelContext);
	static void RequestLlmNpcAction(const FString& UserMessage, ALlmContextSubsystem* LevelContext);
	static void OnNpcResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);
	static void OnNpcActionReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);


	static inline const LlmApiRequestHandler& Get() {
		static LlmApiRequestHandler handler;
		return handler;
	}

private:
	static FString LOCAL_SERVER_ADDRESS;
	static FString RESPONSE_API;
	static FString ACTION_API;

	static void Init();
	static bool bIsInitialized;
	static FHttpModule* HttpModule;
};