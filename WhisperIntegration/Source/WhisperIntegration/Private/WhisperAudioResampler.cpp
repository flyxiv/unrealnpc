#include "WhisperAudioResampler.h"

const double WhisperAudioResampler::WHISPER_TARGET_RESAMPLE_RATE = 16000.0F;

bool WhisperAudioResampler::Resample(const float* InAudio, int32 NumSamples, int32 NumChannels, int32 StartSampleRate, Audio::FAlignedFloatBuffer& OutAudio)
{
	if (0 == NumSamples) {
		UE_LOG(LogTemp, Error, TEXT("NumSamples == 0. Cannot resample."));
		return false;
	}

	// Interpolate to Mono-Channel
	Audio::FAlignedFloatBuffer MonoChannelAudio = Audio::FAlignedFloatBuffer();
	MonoChannelAudio.SetNum((NumSamples / NumChannels));

	for (int32 sampleCnt = 0; sampleCnt < NumSamples; sampleCnt += NumChannels)
	{
		float sum = 0.f;
		for (int32 channelCnt = 0; channelCnt < NumChannels; ++channelCnt)
			sum += InAudio[sampleCnt + channelCnt];
		MonoChannelAudio.Add(sum / NumChannels);
	}

	// Interpolate to Target Sample Rate
	const double Ratio = double(StartSampleRate) / WHISPER_TARGET_RESAMPLE_RATE;
	const int32 NewLen = FMath::CeilToInt(MonoChannelAudio.Num() / Ratio);

	OutAudio.SetNum(NewLen);

	for (int32 i = 0; i < NewLen; ++i)
	{
		double SrcIdx = i * Ratio;
		int32 Idx = FMath::FloorToInt(SrcIdx);
		double Frac = SrcIdx - Idx;

		float SampleValueAtStart = MonoChannelAudio[FMath::Clamp(Idx, 0, MonoChannelAudio.Num() - 1)];
		float SampleValueAtEnd = MonoChannelAudio[FMath::Clamp(Idx + 1, 0, MonoChannelAudio.Num() - 1)];
		OutAudio[i] = (SampleValueAtStart + (SampleValueAtEnd - SampleValueAtStart) * Frac);
	}

	return true;
}
