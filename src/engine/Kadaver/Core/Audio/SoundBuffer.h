#pragma once

#include "Kadaver/Core/Core.h"

#ifdef _WIN32
#include <windows.h>
#include <mmsystem.h>
#include <dsound.h>
#endif

KD_NAMESPACE_BEGIN

class AudioSystem;

class KD_CORE_DLL SoundBuffer
{
public:
	struct WaveHeaderType
	{
		char chunkID[4];
		unsigned long chunkSize;
		char format[4];
		char subChunkID[4];
		unsigned long subChunkSize;
		unsigned short audioFormat;
		unsigned short numChannels;
		unsigned long sampleRate;
		unsigned long bytesPerSecond;
		unsigned short blockAlign;
		unsigned short bitsPerSample;
		char dataChunkID[4];
		unsigned long dataSize;
	};

	SoundBuffer(AudioSystem* as);
	SoundBuffer(AudioSystem* as, const char* path);
	~SoundBuffer();

	void loadFromWave(const char* path);

	void play();

private:
	AudioSystem* audioSystem_;

#ifdef _WIN32
	IDirectSoundBuffer8* buffer_;
#endif
};

KD_NAMESPACE_END