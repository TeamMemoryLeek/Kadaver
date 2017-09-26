#pragma once

#include "../Window.h"

#ifdef _WIN32
#include <dsound.h>
#endif

KD_NAMESPACE_BEGIN

class AudioSystem
{
public:
	AudioSystem(Window* window);
	~AudioSystem();
private:
#ifdef _WIN32
	bool InitializeDirectSound(HWND hwnd);

	IDirectSound8* directSound_;
	IDirectSoundBuffer* primaryBuffer_;
#endif
};

KD_NAMESPACE_END