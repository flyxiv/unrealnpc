#include "LlmGameObjects/LlmLevelData.h"

void ULlmLevelData::PostInitProperties() {
	Super::PostInitProperties();

	LevelInfo = MakeShareable(new FJsonObject());

	TArray<TSharedPtr<FJsonValue>> ObjectsInLevel;

	for (const FLlmAssetInfo& AssetItem : AssetItems) {
		TSharedRef<FJsonObject> AssetJsonObject(new FJsonObject());

		if (!FJsonObjectConverter::UStructToJsonObject(AssetItem.StaticStruct(), &AssetItem, AssetJsonObject)) {
			UE_LOG(LogTemp, Error, TEXT("Conversion to Json Object failed for an Asset Item"));
		}
		ObjectsInLevel.Add(MakeShareable(new FJsonValueObject(AssetJsonObject)));
	}

	LevelInfo->SetArrayField(TEXT("asset_infos"), ObjectsInLevel);
}
