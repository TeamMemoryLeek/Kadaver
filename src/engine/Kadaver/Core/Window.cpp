#if !defined(__APPLE__)

#include "Window.h"
#include "Engine.h"

#include <vector>

#define WINDOW_CLASS_NAME "Kadaver"


KD_NAMESPACE_BEGIN

void(*Window::keyCallback)(int action, int key) = nullptr;
void(*Window::mouseButtonCallback)(int action, int button) = nullptr;
void(*Window::mouseMoveCallback)(int x, int y) = nullptr;
void(*Window::mouseWheelCallback)(int delta) = nullptr;

#if defined(_WIN32)

static std::vector<HWND> windowHandles;

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
	{
		// Remove handle from static list
		auto w = std::find(windowHandles.begin(), windowHandles.end(), hwnd);
		if (w == windowHandles.end())
			throw std::exception("Attempted to destroy unregistered window");
		windowHandles.erase(w);

		// Destroy window
		DestroyWindow(hwnd);

		// Quit if all windows are closed
		if (windowHandles.empty())
			PostQuitMessage(0);
		break;
	}
	case WM_KEYDOWN:
		if (keyCallback)
			keyCallback(KD_ACTION_DOWN, INT_S(wparam));
		break;
	case WM_KEYUP:
		if(keyCallback)
			keyCallback(KD_ACTION_UP, INT_S(wparam));
		break;
	case WM_MOUSEMOVE:
	{
		int x = GET_X_LPARAM(lparam);
		int y = GET_Y_LPARAM(lparam);

		if (mouseMoveCallback)
			mouseMoveCallback(x, y);
		break;
	}
	case WM_LBUTTONDOWN:
		if (mouseButtonCallback)
			mouseButtonCallback(KD_ACTION_DOWN, 0);
		break;
	case WM_LBUTTONUP:
		if (mouseButtonCallback)
			mouseButtonCallback(KD_ACTION_UP, 0);
		break;
	case WM_RBUTTONDOWN:
		if (mouseButtonCallback)
			mouseButtonCallback(KD_ACTION_DOWN, 1);
		break;
	case WM_RBUTTONUP:
		if (mouseButtonCallback)
			mouseButtonCallback(KD_ACTION_UP, 1);
		break;
	case WM_MBUTTONDOWN:
		if (mouseButtonCallback)
			mouseButtonCallback(KD_ACTION_DOWN, 2);
		break;
	case WM_MBUTTONUP:
		if (mouseButtonCallback)
			mouseButtonCallback(KD_ACTION_UP, 2);
		break;
	case WM_MOUSEWHEEL:
	{
		int delta = GET_WHEEL_DELTA_WPARAM(wparam);
		if (mouseWheelCallback)
			mouseWheelCallback(delta);
		break;
	}
	}

	return DefWindowProcA(hwnd, message, wparam, lparam);
}

#elif defined(__linux__)

static std::vector<Window*> windows;

#endif

Window::Window(int width, int height, const char* title)
{
#if defined(_WIN32)
	static ATOM windowClass = createWindowClass();
	DWORD styleEx, style;
	int x, y;

	// Configure window
	styleEx = WS_EX_OVERLAPPEDWINDOW;
	style = WS_OVERLAPPEDWINDOW;
	x = y = CW_USEDEFAULT;

	// Create window
	hwnd_ = CreateWindowExA(styleEx, WINDOW_CLASS_NAME, title, style, x, y,
		width, height, nullptr, nullptr, GetModuleHandleA(nullptr), nullptr);
	if (!hwnd_)
	{
		throw std::exception("CreateWindowEx failed");
	}

	ShowWindow(hwnd_, SW_SHOW);

	// Add window handle to static list
	windowHandles.push_back(hwnd_);
	
#elif defined(__linux__)
	
	XSetWindowAttributes windowAttributes;
	XID rootWindow;
	Visual* visual;
	int depth;

	// Open display
	display_ = XOpenDisplay(nullptr);
	rootWindow = DefaultRootWindow(display_);
	visual = XDefaultVisual(display_, 0);
	depth = XDefaultDepth(display_, 0);

	// Window attributes
	windowAttributes.colormap = XCreateColormap(display_, rootWindow, visual, AllocNone);
	windowAttributes.event_mask = ExposureMask | KeyPressMask;

	// Create window
   	window_ = XCreateWindow(display_, rootWindow, 0, 0, width, height, 0, depth, InputOutput, visual, CWColormap | CWEventMask, &windowAttributes);
	
	// Message interception
	deleteMessage_ = XInternAtom(display_, "WM_DELETE_WINDOW", False);
	XSetWMProtocols(display_, window_, &deleteMessage_, 1);
	
	// Map window, set title, clear window
	XMapWindow(display_, window_);
	XStoreName(display_, window_, title);
	XClearWindow(display_, window_);
	
	// Add display to static list
	windows.push_back(this);
#endif
}

Window::~Window()
{
	destroy();
}

void kd::Window::setTitle(const std::string& title)
{
#if defined(_WIN32)
	SetWindowTextA(hwnd_, title.c_str());
#elif defined(__linux)
	XStoreName(display_, window_, title.c_str());
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
	for (HWND& hwnd : windowHandles)
	{
		while (PeekMessageA(&msg, hwnd, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessageA(&msg);
		}
	}
#elif defined(__linux__)
	XEvent event;
	
	for (auto it = windows.begin(); it != windows.end(); ++it)
	{
		Window* window = (*it);
		while (XPending(window->display_))
		{
			XNextEvent(window->display_, &event);
			
			if (event.type == ClientMessage &&
				(Atom)event.xclient.data.l[0] == window->deleteMessage_)
			{
				// Destroy window
				window->destroy();
				
				// Remove windows from static list
				it = windows.erase(it);
				
				if (windows.empty())
					return false;
			}
		}
	}
#endif

	return true;
}

void Window::destroy()
{
#if defined(_WIN32)
	DestroyWindow(hwnd_);
	hwnd_ = nullptr;
#elif defined(__linux__)
	if (display_)
	{
		XDestroyWindow(display_, window_);
		XCloseDisplay(display_);
		display_ = nullptr;
		window_ = 0;
		deleteMessage_ = 0;
	}
#endif
}

KD_NAMESPACE_END

#endif
