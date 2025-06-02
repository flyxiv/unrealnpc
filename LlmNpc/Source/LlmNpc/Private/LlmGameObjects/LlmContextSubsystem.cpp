#include "LlmGameObjects/LlmContextSubsystem.h"

TSharedPtr<FJsonObject> ALlmContextSubsystem::GetLevelInfo() const {
	return LevelInfo;
}


void ALlmContextSubsystem::BeginPlay() {
	LevelInfo = MakeShareable(new FJsonObject());

	TArray<TSharedPtr<FJsonValue>> ObjectsInLevel;

	if (!CurrentLevelAssets) {
		UE_LOG(LogTemp, Error, TEXT("Cannot load level assets: CurrentLevelAssets is nullptr"));
	}

	for (const FLlmAssetInfo& AssetItem : CurrentLevelAssets->AssetItems) {
		TSharedRef<FJsonObject> AssetJsonObject(new FJsonObject());

		if (!FJsonObjectConverter::UStructToJsonObject(AssetItem.StaticStruct(), &AssetItem, AssetJsonObject)) {
			UE_LOG(LogTemp, Error, TEXT("Conversion to Json Object failed for an Asset Item"));
		}
		ObjectsInLevel.Add(MakeShareable(new FJsonValueObject(AssetJsonObject)));
	}

	LevelInfo->SetArrayField(TEXT("asset_infos"), ObjectsInLevel);
}
