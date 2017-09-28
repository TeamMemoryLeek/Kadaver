#pragma once

#include "../Window.h"

#ifdef _WIN32
#include <dsound.h>
#endif

KD_NAMESPACE_BEGIN

class KD_CORE_DLL AudioSystem
{
public:
	AudioSystem(Window* window);
	~AudioSystem();


private:
#ifdef _WIN32
	bool initializeDirectSound(HWND hwnd);

	IDirectSound8* directSound_;
	IDirectSoundBuffer* primaryBuffer_;
#endif

	friend class AudioBuffer;
};

KD_NAMESPACE_END