#include "AudioSystem.h"

#ifdef _WIN32
#include <windows.h>
#include <mmsystem.h>
#endif

KD_NAMESPACE_BEGIN

AudioSystem::AudioSystem(Window* window)
{
#ifdef _WIN32

	bool result;
	
	result = initializeDirectSound(window->getHWND());
	if (!result)
		throw std::exception("Couldn't initialize DirectSound!");
#endif
}

AudioSystem::~AudioSystem()
{
}

#ifdef _WIN32
bool AudioSystem::initializeDirectSound(HWND hwnd)
{
	HRESULT result;
	DSBUFFERDESC bufferDesc;
	WAVEFORMATEX waveFormat;

	result = DirectSoundCreate8(0, &directSound_, 0);
	if (FAILED(result))
		return false;

	result = directSound_->SetCooperativeLevel(hwnd, DSSCL_PRIORITY);
	if (FAILED(result))
		return false;

	// Setup primary buffer desc
	bufferDesc.dwSize = sizeof(DSBUFFERDESC);
	bufferDesc.dwFlags = DSBCAPS_PRIMARYBUFFER | DSBCAPS_CTRLVOLUME;
	bufferDesc.dwBufferBytes = 0;
	bufferDesc.dwReserved = 0;
	bufferDesc.lpwfxFormat = 0;
	bufferDesc.guid3DAlgorithm = GUID_NULL;

	// Create primary buffer
	result = directSound_->CreateSoundBuffer(&bufferDesc, &primaryBuffer_, 0);
	if (FAILED(result))
		return false;

	// Setup primary buffer sound format
	waveFormat.wFormatTag = WAVE_FORMAT_PCM;
	waveFormat.nSamplesPerSec = 44100;
	waveFormat.wBitsPerSample = 16;
	waveFormat.nChannels = 2;
	waveFormat.nBlockAlign = 
		(waveFormat.wBitsPerSample / 8) * waveFormat.nChannels;
	waveFormat.nAvgBytesPerSec = 
		waveFormat.nSamplesPerSec * waveFormat.nBlockAlign;
	waveFormat.cbSize = 0;

	// Set primary buffer sound format
	result = primaryBuffer_->SetFormat(&waveFormat);
	if (FAILED(result))
		return false;

	return true;
}
#endif

KD_NAMESPACE_END