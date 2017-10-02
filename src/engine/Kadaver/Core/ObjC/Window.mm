#include "Window.h"

#import <Cocoa/Cocoa.h>

#define OBJC_WINDOW reinterpret_cast<NSWindow*>(window_)


KD_NAMESPACE_BEGIN

void(*Window::keyCallback)(int action, int key) = nullptr;
void(*Window::mouseButtonCallback)(int action, int button) = nullptr;
void(*Window::mouseMoveCallback)(int x, int y) = nullptr;
void(*Window::mouseWheelCallback)(int delta) = nullptr;

Window::Window(int width, int height, const char* title)
	: window_(nullptr)
{
	const NSWindowStyleMask styleMask =
		NSWindowStyleMaskResizable | NSWindowStyleMaskTitled |
		NSWindowStyleMaskClosable | NSWindowStyleMaskMiniaturizable;
	
	NSApplication* app;
	NSScreen* screen;
	NSWindow* window;
	NSRect frame;
	
	// Get current application and screen
	app = [NSApplication sharedApplication];
	screen = [NSScreen mainScreen];
	
	// Center window
	CGFloat x = static_cast<CGFloat>(screen.frame.size.width - width) * 0.5f;
	CGFloat y = static_cast<CGFloat>(screen.frame.size.width - width) * 0.5f;
	CGFloat w = static_cast<CGFloat>(width);
	CGFloat h = static_cast<CGFloat>(height);
	frame = NSMakeRect(x, y, w, h);
	
	// Create window
	window = [NSWindow alloc];
	[window autorelease];
	if (![window initWithContentRect:frame styleMask:styleMask
		backing:NSBackingStoreBuffered defer:NO])
	{
//		throw std::exception("NSWindow::initWithContentRect failed");
		throw std::exception();
	}
	
	// Set title
	setTitle(title);
	
	// Associate delegate, activate mouse events, show window
	[window setAcceptsMouseMovedEvents:TRUE];
	[window setIsVisible:TRUE];
	
	[window makeKeyAndOrderFront:app]; // Needed?
	
	window_ = window;
}

Window::~Window()
{
	destroy();
}

void Window::setTitle(const std::string& title)
{
	NSString* t = [NSString stringWithUTF8String:title.c_str()];
	[OBJC_WINDOW setTitle:t];
	[t release];
}

bool Window::pollEvents()
{
	NSEvent* event;
	NSApplication* app;
	
	app = [NSApplication sharedApplication];
	
	while((event = [app nextEventMatchingMask:NSEventMaskAny untilDate:nullptr
		inMode:NSDefaultRunLoopMode dequeue:TRUE]))
	{
		printf("Event: %lu\n", [event type]);
		
		[app sendEvent:event];
	}
	
	[app updateWindows];
	
	if ([app windows].count == 0)
	{
		return false;
	}
	
	return true;
}

void Window::destroy()
{
	[OBJC_WINDOW dealloc];
}

KD_NAMESPACE_END
