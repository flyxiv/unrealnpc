#include "LlmRequest/LlmApiRequestHandler.h"

FString LlmApiRequestHandler::LOCAL_SERVER_ADDRESS = TEXT("http://localhost:23456/api/v1");
FString LlmApiRequestHandler::RESPONSE_API = TEXT("npcresponse");
FString LlmApiRequestHandler::ACTION_API = TEXT("npcaction");

FHttpModule* LlmApiRequestHandler::HttpModule = nullptr;
bool LlmApiRequestHandler::bIsInitialized = false;

LlmApiRequestHandler::LlmApiRequestHandler() {
	Init();
}


void LlmApiRequestHandler::Init() {
	if (bIsInitialized) {
		return;
	}

	HttpModule = &FHttpModule::Get();
	bIsInitialized = true;
}


// Request NPC's response to user's message 
void LlmApiRequestHandler::RequestLlmNpcResponse(const FString& UserMessage, ALlmControlledNpc* Npc, ALlmContextSubsystem* LevelContext)
{
	if (!Npc || !LevelContext) {
		UE_LOG(LogTemp, Error, TEXT("Npc or LevelContext is nullptr: Npc %d, LevelContext %d"), Npc, LevelContext);
	}
	TSharedRef<IHttpRequest> Request = HttpModule->CreateRequest();
	Request->OnProcessRequestComplete().BindStatic(&LlmApiRequestHandler::OnNpcResponseReceived);

	TSharedPtr<FJsonObject> BodyJsonObject = MakeShared<FJsonObject>();
	BodyJsonObject->SetStringField(TEXT("user_message"), UserMessage);
	BodyJsonObject->SetObjectField(TEXT("npc_context"), Npc->GetNpcInfo());
	BodyJsonObject->SetObjectField(TEXT("level_context"), LevelContext->GetLevelInfo());

	FString JsonPayloadString;
	TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&JsonPayloadString);
	FJsonSerializer::Serialize(BodyJsonObject.ToSharedRef(), Writer);

	Request->SetURL(LOCAL_SERVER_ADDRESS + "/" + RESPONSE_API);
	Request->SetVerb("POST");
	Request->SetHeader(TEXT("User-Agent"), "X-UnrealEngine-Agent");
	Request->SetHeader("Content-Type", TEXT("application/json"));
	Request->SetContentAsString(JsonPayloadString);
	Request->ProcessRequest();
}


void LlmApiRequestHandler::RequestLlmNpcAction(const FString& Command, ALlmContextSubsystem* LevelContext)
{
	if (!LevelContext) {
		UE_LOG(LogTemp, Error, TEXT("LevelContext is nullptr"), LevelContext);
	}

	TSharedRef<IHttpRequest> Request = HttpModule->CreateRequest();
	Request->OnProcessRequestComplete().BindStatic(&LlmApiRequestHandler::OnNpcActionReceived);

	TSharedPtr<FJsonObject> BodyJsonObject = MakeShared<FJsonObject>();
	BodyJsonObject->SetStringField(TEXT("command"), Command);
	BodyJsonObject->SetObjectField(TEXT("level_context"), LevelContext->GetLevelInfo());

	FString JsonPayloadString;
	TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&JsonPayloadString);
	FJsonSerializer::Serialize(BodyJsonObject.ToSharedRef(), Writer);

	Request->SetURL(LOCAL_SERVER_ADDRESS + ACTION_API);
	Request->SetVerb("POST");
	Request->SetHeader(TEXT("User-Agent"), "X-UnrealEngine-Agent");
	Request->SetHeader("Content-Type", TEXT("application/json"));
	Request->SetContentAsString(JsonPayloadString);
	Request->ProcessRequest();
}


void LlmApiRequestHandler::OnNpcResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful) {
	TSharedPtr<FJsonObject> JsonObject;
	TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(Response->GetContentAsString());

	if (FJsonSerializer::Deserialize(Reader, JsonObject))
	{
		LlmApiRequestBuffer = JsonObject->GetStringField("Response");

#if !UE_BUILD_SHIPPING
		UE_LOG(LogTemp, Display, TEXT("response text: %s"), *LlmApiRequestBuffer);
#endif
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("Deserialization Failed."))
	}
}


void LlmApiRequestHandler::OnNpcActionReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful) {
	TSharedPtr<FJsonObject> JsonObject;
	TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(Response->GetContentAsString());

	if (FJsonSerializer::Deserialize(Reader, JsonObject))
	{
		LlmApiRequestBuffer = JsonObject->GetStringField("Response");

#if !UE_BUILD_SHIPPING
		UE_LOG(LogTemp, Display, TEXT("response text: %s"), *LlmApiRequestBuffer);
#endif
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("Deserialization Failed."))
	}
}
