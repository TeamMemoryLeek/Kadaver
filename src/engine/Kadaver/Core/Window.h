#pragma once
#include "Core.h"

#if defined(_WIN32)
#include <Windows.h>
#include <vector>
#endif


KD_NAMESPACE_BEGIN

class KD_CORE_DLL Window
{
private:
#if defined(_WIN32)
	static ATOM createWindowClass();
	static LRESULT CALLBACK wndProc(HWND hwnd, UINT message, WPARAM wparam,
		LPARAM lparam);
#endif

public:
	Window(int width, int height, const char* title);
	~Window();

	static bool pollEvents();

#if defined(_WIN32)
	const HWND& getHWND() const { return hwnd_; }
#endif

private:
#if defined(_WIN32)
	HWND hwnd_;
#endif
};

KD_NAMESPACE_END
