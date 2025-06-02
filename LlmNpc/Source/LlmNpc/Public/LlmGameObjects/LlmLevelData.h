#pragma once

#include "Dom/JsonObject.h"
#include "Serialization/JsonReader.h"
#include "JsonObjectConverter.h" 
#include "LlmLevelData.generated.h"

USTRUCT(BlueprintType)
struct LLMNPC_API FLlmAssetInfo {
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	FString AssetName;
};

UCLASS()
class LLMNPC_API ULlmLevelData : public UDataAsset {
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere)
    TArray<FLlmAssetInfo> AssetItems;

protected:
	void PostInitProperties() override;

private:
	TSharedPtr<FJsonObject> LevelInfo;
}; 