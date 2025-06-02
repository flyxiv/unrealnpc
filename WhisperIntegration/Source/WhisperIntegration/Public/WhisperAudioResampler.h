/* ---------------------------------------------------
	Resamples Audio to fit whisper.cpp
	model's requirement of 16kHz and mono channel
--------------------------------------------------- */

#include "CoreMinimal.h"

class WhisperAudioResampler {
private:
	WhisperAudioResampler();
	~WhisperAudioResampler() {};
	WhisperAudioResampler(const WhisperAudioResampler& resampler) = delete;
	WhisperAudioResampler& operator=(const WhisperAudioResampler& resampler) = delete;
	WhisperAudioResampler& operator=(WhisperAudioResampler&& resampler) = delete;

public:
	static bool Resample(const float* InAudio, int32 NumFrames, int32 NumChannels, int32 StartSampleRate, Audio::FAlignedFloatBuffer& OutAudio);
	static const double WHISPER_TARGET_RESAMPLE_RATE;
};
