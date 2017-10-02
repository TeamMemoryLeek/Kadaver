#pragma once
#include "Kadaver/Core/Core.h"

#if defined(_WIN32)
#include <Windows.h>
#elif defined(__linux__)
#include <GL/gl.h>
#include <GL/glx.h>
#endif


KD_NAMESPACE_BEGIN

class Window;

class KD_CORE_DLL RenderContext
{
public:
	RenderContext();
	~RenderContext();

	void initFromWindow(const Window* window);
	void destroy();

	void clear();

private:
#if defined(_WIN32)
	HGLRC hglrc_;
#elif defined(__linux__)
	GLXContext glxContext_;
#endif
};

KD_NAMESPACE_END
