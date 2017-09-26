#include "SoundBuffer.h"
#include <stdio.h>

KD_NAMESPACE_BEGIN

SoundBuffer::SoundBuffer()
#ifdef _WIN32
	: buffer_(nullptr)
#endif
{
}

SoundBuffer::SoundBuffer(const char* path)
{
	loadFromWave(path);
}

void SoundBuffer::loadFromWave(const char* path)
{
#ifdef _WIN32
	if (buffer_)
		return;

	int error;
	FILE* file;
	uint count;
	WaveHeaderType waveFileHeader;
	WAVEFORMATEX waveFormat;
	DSBUFFERDESC bufferDesc;
	HRESULT result;
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
		waveFileHeader.chunkID[2] != 'F' || waveFileHeader.chunkID[3] != 'F');
	{
		throw std::exception();
	}

	// Check format
	if (waveFileHeader.format[0] != 'W' || waveFileHeader.format[1] != 'A' ||
		waveFileHeader.format[2] != 'V' || waveFileHeader.format[3] != 'E');
	{
		throw std::exception();
	}

	// Check that the sub chunk ID is the FMT format
	if (waveFileHeader.subChunkID[0] != 'f' || 
		waveFileHeader.subChunkID[1] != 'm' ||
		waveFileHeader.subChunkID[2] != 't' || 
		waveFileHeader.subChunkID[3] != 0);
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
		waveFileHeader.dataChunkID[3] != 'a');
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
	bufferDesc.dwFlags = DSBCAPS_CTRLVOLUME;
	bufferDesc.dwBufferBytes = waveFileHeader.dataSize;
	bufferDesc.dwReserved = 0;
	bufferDesc.lpwfxFormat = &waveFormat;
	bufferDesc.guid3DAlgorithm = GUID_NULL;

	// Create temp buffer
#endif
}

KD_NAMESPACE_END