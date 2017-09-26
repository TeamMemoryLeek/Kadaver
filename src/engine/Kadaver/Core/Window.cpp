#include "Window.h"

#if defined(_WIN32)
#include <vector>
#endif

#define WINDOW_CLASS_NAME "Kadaver"


KD_NAMESPACE_BEGIN

#if defined(_WIN32)

static std::vector<HWND> window_handles;

ATOM Window::createWindowClass()
{
	WNDCLASSEXA class_desc;
	class_desc.cbSize = sizeof(WNDCLASSEXA);
	class_desc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	class_desc.lpfnWndProc = Window::wndProc;
	class_desc.cbClsExtra = 0;
	class_desc.cbWndExtra = 0;
	class_desc.hInstance = GetModuleHandleA(nullptr);
	class_desc.hIcon = nullptr;
	class_desc.hCursor = nullptr;
	class_desc.hbrBackground = (HBRUSH)BLACK_BRUSH;
	class_desc.lpszMenuName = nullptr;
	class_desc.lpszClassName = WINDOW_CLASS_NAME;
	class_desc.hIconSm = nullptr;

	return RegisterClassExA(&class_desc);
}

LRESULT CALLBACK Window::wndProc(HWND hwnd, UINT message, WPARAM wparam,
	LPARAM lparam)
{
	switch (message)
	{
	case WM_CLOSE:
		// Remove handle from static list
		auto w = std::find(window_handles.begin(), window_handles.end(), hwnd);
		if (w == window_handles.end())
			throw std::exception("Attempted to destroy unregistered window");
		window_handles.erase(w);

		// Destroy window
		DestroyWindow(hwnd);

		// Quit if all windows are closed
		if (window_handles.empty())
			PostQuitMessage(0);
	}

	return DefWindowProcA(hwnd, message, wparam, lparam);
}

#endif

Window::Window(int width, int height, const char* title)
{
#if defined(_WIN32)
	static ATOM window_class = createWindowClass();
	DWORD style_ex, style;
	int x, y;

	// Configure window
	style_ex = WS_EX_OVERLAPPEDWINDOW;
	style = WS_OVERLAPPEDWINDOW;
	x = y = CW_USEDEFAULT;

	// Create window
	hwnd_ = CreateWindowExA(style_ex, WINDOW_CLASS_NAME, title, style, x, y,
		width, height, nullptr, nullptr, GetModuleHandleA(nullptr), nullptr);
	if (hwnd_)
	{
		throw std::exception("CreateWindowEx failed");
	}

	ShowWindow(hwnd_, SW_SHOW);

	// Add window handle to static list
	window_handles.push_back(hwnd_);
#endif
}

Window::~Window()
{
#if defined(_WIN32)
	DestroyWindow(hwnd_);
#endif
}

bool Window::pollEvents()
{
#if defined(_WIN32)
	MSG msg;

	// Handle desktop messages
	while (PeekMessageA(&msg, HWND_DESKTOP, 0, 0, PM_REMOVE))
	{
		TranslateMessage(&msg);
		DispatchMessageA(&msg);

		if (msg.message == WM_QUIT)
			return false;
	}

	// Handle all window messages
	for (HWND& hwnd : window_handles)
	{
		while (PeekMessageA(&msg, hwnd, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessageA(&msg);
		}
	}
#endif

	return true;
}

KD_NAMESPACE_END
