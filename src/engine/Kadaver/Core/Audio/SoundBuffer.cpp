#include "SoundBuffer.h"
#include "AudioSystem.h"
#include "Kadaver/Core/Math/Math.hpp"
#include <stdio.h>

KD_NAMESPACE_BEGIN

SoundBuffer::SoundBuffer(AudioSystem* as)
	: audioSystem_(as)
	, volume_(1.0f)
#ifdef _WIN32
	, buffer_(nullptr)
#endif
{
}

SoundBuffer::~SoundBuffer()
{
#ifdef _WIN32
	// Release buffer
	if (buffer_)
		buffer_->Release();
#endif
}

void SoundBuffer::loadFromWave(const char* path)
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
		throw std::exception("Couldn't open .wav file");

	// Read in the wave file header
	count = fread(&waveFileHeader, sizeof(waveFileHeader), 1, file);
	if(count != 1)
		throw std::exception();

	// Check that the chunk ID is the RIFF format
	if (waveFileHeader.chunkID[0] != 'R' || waveFileHeader.chunkID[1] != 'I' ||
		waveFileHeader.chunkID[2] != 'F' || waveFileHeader.chunkID[3] != 'F')
	{
		throw std::exception();
	}

	// Check format
	if (waveFileHeader.format[0] != 'W' || waveFileHeader.format[1] != 'A' ||
		waveFileHeader.format[2] != 'V' || waveFileHeader.format[3] != 'E')
	{
		throw std::exception();
	}

	// Check that the sub chunk ID is the FMT format
	if (waveFileHeader.subChunkID[0] != 'f' || 
		waveFileHeader.subChunkID[1] != 'm' ||
		waveFileHeader.subChunkID[2] != 't' || 
		waveFileHeader.subChunkID[3] != 32)
	{
		throw std::exception();
	}

	// Check that the audio format is WAVE_FORMAT_PCM
	if(waveFileHeader.audioFormat != WAVE_FORMAT_PCM)
		throw std::exception();

	// Check that the wave file was recorded in stereo
	if (waveFileHeader.numChannels != 2)
		throw std::exception();

	// Check that the wave file was recorded in 44.1KHz
	if(waveFileHeader.sampleRate != 44100)
		throw std::exception();

	// Check if 16 bit format
	if (waveFileHeader.bitsPerSample != 16)
		throw std::exception();

	// Check for the data chunk header
	if (waveFileHeader.dataChunkID[0] != 'd' ||
		waveFileHeader.dataChunkID[1] != 'a' ||
		waveFileHeader.dataChunkID[2] != 't' ||
		waveFileHeader.dataChunkID[3] != 'a')
	{
		throw std::exception();
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
		throw std::exception();

	if (FAILED(tempBuffer->QueryInterface(IID_IDirectSoundBuffer8,
		(void**)&buffer_)))
		throw std::exception();

	// Release temp buffer
	tempBuffer->Release();
	tempBuffer = 0;

	// Move to beginning of wave data
	fseek(file, sizeof(WaveHeaderType), SEEK_SET);

	// Create temp buffer for wav data
	waveData = new byte[waveFileHeader.dataSize];
	if (!waveData)
		throw std::exception();

	// Read the wave file into new buffer
	count = fread(waveData, 1, waveFileHeader.dataSize, file);
	if (count != waveFileHeader.dataSize)
		throw std::exception();

	// Close file
	error = fclose(file);
	if(error)
		throw std::exception();

	// Lock buffer
	if (FAILED(buffer_->Lock(0, waveFileHeader.dataSize, (void**)&buffer,
		(DWORD*)&bufferSize, 0, 0, 0)))
		throw std::exception();

	// Copy data into buffer
	memcpy(buffer, waveData, waveFileHeader.dataSize);

	// Unlock buffer
	if (FAILED(buffer_->Unlock((void*)buffer, bufferSize, 0, 0)))
		throw std::exception();

	// Release wave data
	delete[] waveData;

	// Store data size
	dataSize_ = waveFileHeader.dataSize;
	
	// Store original frequency
	if (FAILED(buffer_->GetFrequency(&originalFrequency_)))
		throw std::exception();
#endif
}

void SoundBuffer::setVolume(float volume)
{	
	volume = clamp(volume, 0.0f, 1.0f);

#ifdef _WIN32
	if (!buffer_)
		return;

	int vol = interpolate<int>(-5000, DSBVOLUME_MAX, volume);
	if (FAILED(buffer_->SetVolume(vol)))
		throw std::exception("Couldn't set volume");
#endif

	volume_ = volume;
}

void SoundBuffer::setPosition(float position)
{
#ifdef _WIN32
	if (!buffer_)
		return;

	int pos = interpolate<int>(0, dataSize_, position);
	if (FAILED(buffer_->SetCurrentPosition(pos)))
		throw std::exception("Couldn't set position");
#endif
}

void SoundBuffer::setPan(float pan)
{
	pan = clamp(pan, -1.0f, 1.0f);

#ifdef _WIN32
	if (!buffer_)
		return;
	int p = interpolate<int>(0, 5000, pan);
	if (FAILED(buffer_->SetPan(p)))
		throw std::exception("Couldn't set pan");
#endif
}

void kd::SoundBuffer::setFrequency(float freq)
{
	freq = FLOAT_S(originalFrequency_) * (freq + 0.01f);
#ifdef _WIN32
	if (!buffer_)
		return;
	freq = clamp(freq, FLOAT_S(DSBFREQUENCY_MIN), FLOAT_S(DSBFREQUENCY_MAX));

	if (FAILED(buffer_->SetFrequency(UINT(freq))))
		throw std::exception("Couldn't set frequency");
#endif
}

void SoundBuffer::play()
{
#ifdef _WIN32
	if (!buffer_)
		return;

	if (FAILED(buffer_->Play(0, 0, 0)))
		throw std::exception("Couldn't play");
#endif
}

void kd::SoundBuffer::stop()
{
#ifdef _WIN32
	if (!buffer_)
		return;

	if (FAILED(buffer_->Stop()))
		throw std::exception("Couldn't stop");
#endif
}


KD_NAMESPACE_END

