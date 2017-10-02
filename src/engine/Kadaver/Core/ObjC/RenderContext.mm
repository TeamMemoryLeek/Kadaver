#include "RenderContext.h"

#include "Engine.h"
#include "Window.h"

#import <Cocoa/Cocoa.h>
#import <OpenGL/OpenGL.h>
#import <OpenGL/gl.h>

#define OBJC_OPENGL_VIEW reinterpret_cast<NSOpenGLView*>(openGlView_)


KD_NAMESPACE_BEGIN

RenderContext::RenderContext()
	: openGlView_(nullptr)
{
}

RenderContext::~RenderContext()
{
	destroy();
}

void RenderContext::initFromWindow(const Window* cppWindow)
{
	NSWindow* window = reinterpret_cast<NSWindow*>(cppWindow->getWindow());
	NSOpenGLView* view = [NSOpenGLView alloc];
	NSOpenGLPixelFormat* pixelFormat = [NSOpenGLPixelFormat alloc];
	
	NSOpenGLPixelFormatAttribute attributes[] =	{
		NSOpenGLPFADoubleBuffer,
		0
	};
	
	NSRect frame = NSMakeRect(0, 0, cppWindow->getWidth(),
		cppWindow->getHeight());
	
	// Init pixel format
	[pixelFormat initWithAttributes:attributes];
	
	// Create OpenGL view
	if (![view initWithFrame:frame pixelFormat:pixelFormat])
	{
		throw Exception("NSOpenGLView::initWithFrame failed");
	}
	[view prepareOpenGL];
	[[window contentView] addSubview:view];
	
	// Make context current
	[[view openGLContext] makeCurrentContext];
	
	// Get OpenGL version
	const GLubyte* glVersion = glGetString(GL_VERSION);
	if (!glVersion)
	{
		throw Exception("Failed to fetch GL version");
	}
	
	// Print OpenGL version
	std::string s = std::string("OpenGL v.") +
	reinterpret_cast<const char*>(glVersion);
	KD_LOGGER.log(s, LOG_RENDERING);
	
	glEnable(GL_DEPTH_TEST);
	glViewport(0, 0, cppWindow->getWidth(), cppWindow->getHeight());
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	
	openGlView_ = view;
}

void RenderContext::destroy()
{
	[OBJC_OPENGL_VIEW dealloc];
}

void RenderContext::clear()
{
	[[OBJC_OPENGL_VIEW openGLContext] flushBuffer];
}

KD_NAMESPACE_END
