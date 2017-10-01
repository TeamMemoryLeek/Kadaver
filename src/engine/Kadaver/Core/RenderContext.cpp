#include "RenderContext.h"

#include "Engine.h"
#include "Window.h"

#if defined(_WIN32)
#include <gl/GL.h>
#endif


KD_NAMESPACE_BEGIN

RenderContext::RenderContext()
	: hglrc_(nullptr)
{
}

RenderContext::~RenderContext()
{
	destroy();
}

void RenderContext::initFromWindow(const Window* window)
{
#if defined(_WIN32)
	PIXELFORMATDESCRIPTOR pixelFormatDesc;
	int pixel_format;

	// Describe pixel format
	ZeroMemory(&pixelFormatDesc, sizeof(PIXELFORMATDESCRIPTOR));
	pixelFormatDesc.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pixelFormatDesc.nVersion = 1;
	pixelFormatDesc.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL |
		PFD_DOUBLEBUFFER;
	pixelFormatDesc.iPixelType = PFD_TYPE_RGBA;
	pixelFormatDesc.cColorBits = 24;
	pixelFormatDesc.cDepthBits = 24;
	pixelFormatDesc.iLayerType = PFD_MAIN_PLANE;

	// Choose pixel format
	pixel_format = ChoosePixelFormat(window->getHDC(), &pixelFormatDesc);
	if (pixel_format == 0)
	{
		throw Exception("ChoosePixelFormat failed");
	}

	// Set pixel format
	if (!SetPixelFormat(window->getHDC(), pixel_format, &pixelFormatDesc))
	{
		throw Exception("SetPixelFormat failed");
	}

	// Create the render context
	hglrc_ = wglCreateContext(window->getHDC());
	if (!hglrc_)
	{
		throw Exception("wglCreateContext failed");
	}

	// Make context current
	if (!wglMakeCurrent(window->getHDC(), hglrc_))
	{
		throw Exception("wglMakeCurrent failed");
	}
#endif

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
	glViewport(0, 0, window->getWidth(), window->getHeight());
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

void RenderContext::destroy()
{
#if defined(_WIN32)
	wglDeleteContext(hglrc_);
#endif
}

void RenderContext::clear()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

KD_NAMESPACE_END