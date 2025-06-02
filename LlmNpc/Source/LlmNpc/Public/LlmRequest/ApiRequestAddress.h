#pragma once

struct ApiRequestAddress {
	FString ApiServerAddress;
	int32 port = -1;

	const FString CreateAddress() {
		FString ServerAddress = ApiServerAddress;

		if (port != -1) {
			ServerAddress += FString::Printf(TEXT(":%d", port));
		}

#if UE_BUILD_SHIPPING
		UE_LOG(LogTemp, Display, Text("%s"), ServerAddress);
#endif
		return ServerAddress;
	}
};