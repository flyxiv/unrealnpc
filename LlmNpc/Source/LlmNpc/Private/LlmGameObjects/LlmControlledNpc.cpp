#include "LlmGameObjects/LlmControlledNpc.h"
#include "LlmRequest/LlmApiRequestHandler.h"

// Extract Character Settings from input JSON file.
void ALlmControlledNpc::BeginPlay() {
	FString NpcInfoString;

	if (SettingsFilePath.FilePath.IsEmpty()) {
		UE_LOG(LogTemp, Error, TEXT("Failed to load npc: file path %s is empty"), *SettingsFilePath.FilePath);
		return;
	}

	if (!FFileHelper::LoadFileToString(NpcInfoString, *SettingsFilePath.FilePath))
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to load json file in path: %s"), *SettingsFilePath.FilePath);
		return;
	}

	TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(NpcInfoString);
	NpcInfo = MakeShareable(new FJsonObject());
	FJsonSerializer::Deserialize(JsonReader, NpcInfo);
		
	if (!NpcInfo.IsValid()) 
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to load deserialize npc info"));
		return;
	}
}

TSharedPtr<FJsonObject> ALlmControlledNpc::GetNpcInfo() const {
	return NpcInfo;
 }