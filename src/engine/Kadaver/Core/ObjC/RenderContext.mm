#include "RenderContext.h"

#include "Engine.h"
#include "Window.h"

#import <Cocoa/Cocoa.h>
#import <OpenGL/OpenGL.h>
#import <OpenGL/gl.h>

#define OBJC_OPENGL_CONTEXT reinterpret_cast<NSOpenGLContext*>(openGlContext_)


KD_NAMESPACE_BEGIN

RenderContext::RenderContext()
	: openGlContext_(nullptr)
{
}

RenderContext::~RenderContext()
{
	
}

void RenderContext::initFromWindow(const Window* cppWindow)
{
	NSWindow* window = reinterpret_cast<NSWindow*>(cppWindow->getWindow());
	NSView* view = [window contentView];
	NSOpenGLPixelFormat* pixelFormat = [NSOpenGLPixelFormat alloc];
	NSOpenGLContext* openGlContext = [NSOpenGLContext alloc];
	
	NSOpenGLPixelFormatAttribute attributes[] =	{
		NSOpenGLPFADoubleBuffer,
		NSOpenGLPFAColorSize, 24,
		NSOpenGLPFAAlphaSize, 8,
		NSOpenGLPFADepthSize, 24,
		NSOpenGLPFAAccelerated,
		0
	};
	
	[pixelFormat initWithAttributes:attributes];
	[openGlContext initWithFormat:pixelFormat shareContext:nil];
	[openGlContext setView:view];
	[openGlContext makeCurrentContext];
	
	// Get OpenGL version
	const GLubyte* glVersion = glGetString(GL_VERSION);
	if (!glVersion)
	{
		throw Exception("Failed to fetch GL version");
	}
	
	// Print OpenGL version
	KD_LOGGER.log(reinterpret_cast<const char*>(glVersion), LOG_RENDERING);
	
	glEnable(GL_DEPTH_TEST);
	glViewport(0, 0, cppWindow->getWidth(), cppWindow->getHeight());
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	
	openGlContext_ = openGlContext;
}

void RenderContext::destroy()
{
	[OBJC_OPENGL_CONTEXT dealloc];
}

void RenderContext::clear()
{
	[OBJC_OPENGL_CONTEXT update];
	[OBJC_OPENGL_CONTEXT flushBuffer];
}

KD_NAMESPACE_END
