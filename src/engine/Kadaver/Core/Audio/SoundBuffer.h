#pragma once

#include "Kadaver/Core/Core.h"

#ifdef _WIN32
#include <windows.h>
#include <mmsystem.h>
#include <dsound.h>
#endif

KD_NAMESPACE_BEGIN

class SoundBuffer
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

	SoundBuffer();
	SoundBuffer(const char* path);

	void loadFromWave(const char* path);

private:
#ifdef _WIN32
	IDirectSoundBuffer8* buffer_;
#endif
};

KD_NAMESPACE_END