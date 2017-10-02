#pragma once
#include "Kadaver/Core/Core.h"
#include "Kadaver/Core/RenderContext.h"

#include <string>

#if defined(_WIN32)
#include <Windows.h>
#include <windowsx.h>
#include <vector>
#elif defined(__linux__)
#include <X11/Xlib.h>
#include <X11/Xos.h>
#include <X11/Xutil.h>
#endif

#define KD_ACTION_DOWN 0
#define KD_ACTION_UP 1

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

	// Input callback setters
	static void setKeyCallback(void(*cb)(int action, int key))
	{
		keyCallback = cb;
	}
	static void setMouseButtonCallback(void(*cb)(int action, int button))
	{
		mouseButtonCallback = cb;
	}
	static void setMouseMoveCallback(void(*cb)(int x, int y))
	{
		mouseMoveCallback = cb;
	}
	static void setMouseWheelCallback(void(*cb)(int delta))
	{
		mouseWheelCallback = cb;
	}

	void setTitle(const std::string& title);

	static bool pollEvents();
	
	void swapBuffers();
	void destroy();

	const RenderContext& getRenderContext() const { return renderContext_; }
	int getWidth() const { return width_; }
	int getHeight() const { return height_; }

#if defined(_WIN32)
	const HWND& getHWND() const { return hwnd_; }
	const HDC& getHDC() const { return hdc_; }
#endif

private:
	RenderContext renderContext_;
	int width_, height_;

#if defined(_WIN32)
	HWND hwnd_;
	HDC hdc_;
#elif defined(__linux__)
	_XDisplay* display_;
	XVisualInfo* visualInfo_;
	XID window_;
	Atom deleteMessage_;
#elif defined(__APPLE__)
	void* window_;
#endif

	// Input callback
	static void(*keyCallback)(int action, int key);
	static void(*mouseButtonCallback)(int action, int button);
	static void(*mouseMoveCallback)(int x, int y);
	static void(*mouseWheelCallback)(int delta);
};

KD_NAMESPACE_END
