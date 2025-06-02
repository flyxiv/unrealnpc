#pragma once

#include "GameFramework/Character.h"

#include "Dom/JsonObject.h"
#include "Serialization/JsonReader.h"
#include "Serialization/JsonSerializer.h"
#include "JsonObjectConverter.h"  

#include "LlmControlledNpc.generated.h"

UCLASS()
class LLMNPC_API ALlmControlledNpc : public ACharacter {
	GENERATED_BODY()

public:
	ALlmControlledNpc() {}
	TSharedPtr<FJsonObject> GetNpcInfo() const;

protected:
	void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config", meta = (FilePathFilter = "json")) 
	FFilePath SettingsFilePath;

private:
	TSharedPtr<FJsonObject> NpcInfo;
};