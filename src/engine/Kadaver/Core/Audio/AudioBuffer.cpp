#include "AudioBuffer.h"
#include "AudioSystem.h"
#include "Kadaver/Core/Math/Math.hpp"
#include <stdio.h>

KD_NAMESPACE_BEGIN

AudioBuffer::AudioBuffer(AudioSystem* as)
	: audioSystem_(as)
	, volume_(1.0f)
#ifdef _WIN32
	, buffer_(nullptr)
#endif
{
}

AudioBuffer::~AudioBuffer()
{
#ifdef _WIN32
	// Release buffer
	if (buffer_)
		buffer_->Release();
#endif
}

void AudioBuffer::loadFromWave(const char* path)
{
#ifdef _WIN32
	if (buffer_)
		return;

	int error;
	FILE* file;
	size_t count;
	WaveHeaderType waveFileHeader;
	WAVEFORMATEX waveFormat;
	DSBUFFERDESC bufferDesc;
	IDirectSoundBuffer* tempBuffer;
	byte* waveData;
	byte* buffer;
	unsigned long bufferSize;

	// Open the wave file in binary
	error = fopen_s(&file, path, "rb");
	if (error)
		throw Exception("Couldn't open .wav file");

	// Read in the wave file header
	count = fread(&waveFileHeader, sizeof(waveFileHeader), 1, file);
	if(count != 1)
		throw Exception();

	// Check that the chunk ID is the RIFF format
	if (waveFileHeader.chunkID[0] != 'R' || waveFileHeader.chunkID[1] != 'I' ||
		waveFileHeader.chunkID[2] != 'F' || waveFileHeader.chunkID[3] != 'F')
	{
		throw Exception();
	}

	// Check format
	if (waveFileHeader.format[0] != 'W' || waveFileHeader.format[1] != 'A' ||
		waveFileHeader.format[2] != 'V' || waveFileHeader.format[3] != 'E')
	{
		throw Exception();
	}

	// Check that the sub chunk ID is the FMT format
	if (waveFileHeader.subChunkID[0] != 'f' || 
		waveFileHeader.subChunkID[1] != 'm' ||
		waveFileHeader.subChunkID[2] != 't' || 
		waveFileHeader.subChunkID[3] != 32)
	{
		throw Exception();
	}

	// Check that the audio format is WAVE_FORMAT_PCM
	if(waveFileHeader.audioFormat != WAVE_FORMAT_PCM)
		throw Exception();

	// Check that the wave file was recorded in stereo
	if (waveFileHeader.numChannels != 2)
		throw Exception();

	// Check that the wave file was recorded in 44.1KHz
	if(waveFileHeader.sampleRate != 44100)
		throw Exception();

	// Check if 16 bit format
	if (waveFileHeader.bitsPerSample != 16)
		throw Exception();

	// Check for the data chunk header
	if (waveFileHeader.dataChunkID[0] != 'd' ||
		waveFileHeader.dataChunkID[1] != 'a' ||
		waveFileHeader.dataChunkID[2] != 't' ||
		waveFileHeader.dataChunkID[3] != 'a')
	{
		throw Exception();
	}

	// Set wave format of secondary buffer
	waveFormat.wFormatTag = WAVE_FORMAT_PCM;
	waveFormat.nSamplesPerSec = 44100;
	waveFormat.wBitsPerSample = 16;
	waveFormat.nChannels = 2;
	waveFormat.nBlockAlign = 
		(waveFormat.wBitsPerSample / 8) * waveFormat.nChannels;
	waveFormat.nAvgBytesPerSec = 
		waveFormat.nSamplesPerSec * waveFormat.nBlockAlign;
	waveFormat.cbSize = 0;

	// Set the description of the secondary buffer
	bufferDesc.dwSize = sizeof(DSBUFFERDESC);
	bufferDesc.dwFlags = 
		DSBCAPS_CTRLVOLUME | 
		DSBCAPS_CTRLPAN | 
		DSBCAPS_CTRLFREQUENCY;
	bufferDesc.dwBufferBytes = waveFileHeader.dataSize;
	bufferDesc.dwReserved = 0;
	bufferDesc.lpwfxFormat = &waveFormat;
	bufferDesc.guid3DAlgorithm = GUID_NULL;

	// Create temp buffer
	if (FAILED(audioSystem_->directSound_->CreateSoundBuffer(
		&bufferDesc, &tempBuffer, 0)))
		throw Exception();

	if (FAILED(tempBuffer->QueryInterface(IID_IDirectSoundBuffer8,
		(void**)&buffer_)))
		throw Exception();

	// Release temp buffer
	tempBuffer->Release();
	tempBuffer = 0;

	// Move to beginning of wave data
	fseek(file, sizeof(WaveHeaderType), SEEK_SET);

	// Create temp buffer for wav data
	waveData = new byte[waveFileHeader.dataSize];
	if (!waveData)
		throw Exception();

	// Read the wave file into new buffer
	count = fread(waveData, 1, waveFileHeader.dataSize, file);
	if (count != waveFileHeader.dataSize)
		throw Exception();

	// Close file
	error = fclose(file);
	if(error)
		throw Exception();

	// Lock buffer
	if (FAILED(buffer_->Lock(0, waveFileHeader.dataSize, (void**)&buffer,
		(DWORD*)&bufferSize, 0, 0, 0)))
		throw Exception();

	// Copy data into buffer
	memcpy(buffer, waveData, waveFileHeader.dataSize);

	// Unlock buffer
	if (FAILED(buffer_->Unlock((void*)buffer, bufferSize, 0, 0)))
		throw Exception();

	// Release wave data
	delete[] waveData;

	// Store data size
	dataSize_ = waveFileHeader.dataSize;
	
	// Store original frequency
	if (FAILED(buffer_->GetFrequency(&originalFrequency_)))
		throw Exception();
#endif
}

void AudioBuffer::setVolume(float volume)
{	
	volume = clamp(volume, 0.0f, 1.0f);

#ifdef _WIN32
	if (!buffer_)
		return;

	int vol = interpolate<int>(-7500, DSBVOLUME_MAX, volume);
	if (FAILED(buffer_->SetVolume(vol)))
		throw Exception("Couldn't set volume");
#endif

	volume_ = volume;
}

void AudioBuffer::setPosition(float position)
{
#ifdef _WIN32
	if (!buffer_)
		return;

	int pos = interpolate<int>(0, dataSize_, position);
	if (FAILED(buffer_->SetCurrentPosition(pos)))
		throw Exception("Couldn't set position");
#endif
}

void AudioBuffer::setPan(float pan)
{
	pan = clamp(pan, -1.0f, 1.0f);

#ifdef _WIN32
	if (!buffer_)
		return;
	int p = interpolate<int>(0, 5000, pan);
	if (FAILED(buffer_->SetPan(p)))
		throw Exception("Couldn't set pan");
#endif
}

void kd::AudioBuffer::setFrequency(float freq)
{
	freq = FLOAT_S(originalFrequency_) * (freq + 0.01f);
#ifdef _WIN32
	if (!buffer_)
		return;
	freq = clamp(freq, FLOAT_S(DSBFREQUENCY_MIN), FLOAT_S(DSBFREQUENCY_MAX));

	if (FAILED(buffer_->SetFrequency(UINT(freq))))
		throw Exception("Couldn't set frequency");
#endif
}

void AudioBuffer::play()
{
#ifdef _WIN32
	if (!buffer_)
		return;

	if (FAILED(buffer_->Play(0, 0, 0)))
		throw Exception("Couldn't play");
#endif
}

void kd::AudioBuffer::stop()
{
#ifdef _WIN32
	if (!buffer_)
		return;

	if (FAILED(buffer_->Stop()))
		throw Exception("Couldn't stop");
#endif
}

float kd::AudioBuffer::getProgress() const
{
#ifdef _WIN32
	if (!buffer_)
		return false;
	unsigned long currentPos;
	if (FAILED(buffer_->GetCurrentPosition(&currentPos, nullptr)))
		return false;

	return FLOAT_S(currentPos) / FLOAT_S(dataSize_);
#else
	return 0.f;
#endif
}

bool kd::AudioBuffer::isPlaying() const
{
	float progress = getProgress();
	if (progress != 0.0f && progress != 1.0f)
		return true;
	return false;
}

KD_NAMESPACE_END

