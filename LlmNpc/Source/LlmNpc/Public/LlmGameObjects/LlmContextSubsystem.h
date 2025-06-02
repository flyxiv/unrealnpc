#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "LlmLevelData.h"
#include "LLMContextSubsystem.generated.h"

UCLASS()
class LLMNPC_API ALlmContextSubsystem : public AActor
{
    GENERATED_BODY()

public:
    TSharedPtr<FJsonObject> GetLevelInfo() const;

protected:
    void BeginPlay() override;

private:
    UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
    TObjectPtr<ULlmLevelData> CurrentLevelAssets;

    TSharedPtr<FJsonObject> LevelInfo;
};