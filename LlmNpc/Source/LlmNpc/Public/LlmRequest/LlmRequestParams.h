#pragma once

#include "LlmRequestParams.generated.h" 

USTRUCT(BlueprintType)
struct LLMNPC_API FLlmRequestParams {
	GENERATED_BODY()

	float temperature = 0.7;
	int max_tokens = 1000;
};
