#pragma once
#include "Core.h"

#if defined(_WIN32)
#include <Windows.h>
#include <vector>
#elif defined(__linux__)
#include <X11/Xlib.h>
#include <X11/Xos.h>
#include <X11/Xutil.h>
#endif

#define KD_KEYACTION_DOWN 0
#define KD_KEYACTION_UP 1

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

	static void setKeyCallback(void(*kcb)(int action, int key))
	{
		keyCallback = kcb;
	}
	static bool pollEvents();
	
	void destroy();
#if defined(_WIN32)
	const HWND& getHWND() const { return hwnd_; }
#endif

private:
#if defined(_WIN32)
	HWND hwnd_;
#elif defined(__linux__)
	_XDisplay* display_;
	XID window_;
	Atom deleteMessage_;
#elif defined(__APPLE__)
	void* window_;
#endif

	// Input callback
	static void(*keyCallback)(int action, int key);
};

KD_NAMESPACE_END
