#pragma once

#include "../Window.h"

#if defined(_WIN32)
#include <dsound.h>
#elif defined(__linux__)
#include <alsa/asoundlib.h>
#endif

KD_NAMESPACE_BEGIN

class KD_CORE_DLL AudioSystem
{
public:
	AudioSystem(Window* window);
	~AudioSystem();


private:
#if defined(_WIN32)
	bool initializeDirectSound(HWND hwnd);

	IDirectSound8* directSound_;
	IDirectSoundBuffer* primaryBuffer_;
#elif defined(__linux__)
	bool initializeALSA();

	snd_pcm_t* device_;
	snd_pcm_hw_params_t* params_;
#endif

	friend class AudioBuffer;
};

KD_NAMESPACE_END