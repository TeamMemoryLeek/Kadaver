#include "AudioSystem.h"

#ifdef _WIN32
#include <windows.h>
#include <mmsystem.h>
#endif

KD_NAMESPACE_BEGIN

AudioSystem::AudioSystem(Window* window)
{
#if defined(_WIN32)

	bool result;
	
	result = initializeDirectSound(window->getHWND());
	if (!result)
		throw Exception("Couldn't initialize DirectSound!");
#elif defined(__linux__)
	KD_UNUSED(window);
	
	bool result = initializeALSA();
	if(!result)
	{
		printf("Couldn't initialize ALSA!");
		throw Exception();
	}
#endif
}

AudioSystem::~AudioSystem()
{
#if defined(_WIN32)
	// Release primary buffer
	if (primaryBuffer_)
		primaryBuffer_->Release();

	// Release direct sound interface
	if (directSound_)
		directSound_->Release();
#elif defined(__linux__)
	snd_pcm_drain(device_);
	snd_pcm_close(device_);
#endif
}

#if defined(_WIN32)
bool AudioSystem::initializeDirectSound(HWND hwnd)
{
	DSBUFFERDESC bufferDesc;
	WAVEFORMATEX waveFormat;

	if (FAILED(DirectSoundCreate8(0, &directSound_, 0)))
		return false;

	if (FAILED(directSound_->SetCooperativeLevel(hwnd, DSSCL_PRIORITY)))
		return false;

	// Setup primary buffer desc
	bufferDesc.dwSize = sizeof(DSBUFFERDESC);
	bufferDesc.dwFlags =
		DSBCAPS_PRIMARYBUFFER |
		DSBCAPS_CTRLVOLUME |
		DSBCAPS_CTRLPAN;
	bufferDesc.dwBufferBytes = 0;
	bufferDesc.dwReserved = 0;
	bufferDesc.lpwfxFormat = 0;
	bufferDesc.guid3DAlgorithm = GUID_NULL;

	// Create primary buffer
	if (FAILED(directSound_->CreateSoundBuffer(&bufferDesc, 
		&primaryBuffer_, 0)))
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
	if (FAILED(primaryBuffer_->SetFormat(&waveFormat)))
		return false;

	return true;
}

#elif defined(__linux__)

bool AudioSystem::initializeALSA()
{
#define KD_ASYS_CHECK_ERR(err) if(err < 0) return false

	uint err;
	int channels = 2;
	uint rate = 44100;
	
	// Open device
	err = snd_pcm_open(&device_, "plughw:0,0", SND_PCM_STREAM_PLAYBACK,0);
	KD_ASYS_CHECK_ERR(err);
	
	// Allocate memory for hardware parameter struct
	err = snd_pcm_hw_params_malloc(&params_);
	KD_ASYS_CHECK_ERR(err);
	
	// Get current parameters for sound device
	err = snd_pcm_hw_params_any(device_, params_);
	KD_ASYS_CHECK_ERR(err);
		
	// Set parameters
	err = snd_pcm_hw_params_set_access(device_, params_, 
		SND_PCM_ACCESS_RW_INTERLEAVED);
	KD_ASYS_CHECK_ERR(err);
	
	err = snd_pcm_hw_params_set_format(device_, params_, 
		SND_PCM_FORMAT_S16_LE);
	KD_ASYS_CHECK_ERR(err);
	
	err = snd_pcm_hw_params_set_channels(device_, params_, channels);
	KD_ASYS_CHECK_ERR(err);
	
	err = snd_pcm_hw_params_set_rate_near(device_, params_, &rate, 0);
	KD_ASYS_CHECK_ERR(err);
	
	// Write parameters
	err = snd_pcm_hw_params(device_, params_);
	KD_ASYS_CHECK_ERR(err);
	
#undef KD_ASYS_CHECK_ERR

	return true;
}	

#endif

KD_NAMESPACE_END