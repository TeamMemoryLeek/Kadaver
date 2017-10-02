#include <Kadaver/Core/Engine.h>
#include <Kadaver/Core/Window.h>
#include <Kadaver/Core/Audio/AudioSystem.h>
#include <Kadaver/Core/Audio/AudioBuffer.h>
#include <Kadaver/Core/Audio/AudioListener.h>
#include <Kadaver/Core/Audio/AudioSource.h>

#if defined(_WIN32)
#include <gl/GL.h>
#elif defined(__linux__)
#include <GL/gl.h>
#elif defined(__APPLE__)
#include <OpenGL/gl.h>
#endif

#include <iostream>

void mouseWheelCallback(int delta)
{
	KD_LOGGER.log("Scrolling: " + std::to_string(delta));
}

int main(int argc, char** argv)
{
	KD_UNUSED(argc);
	KD_UNUSED(argv);

	try
	{
		kd::Engine engine;
		kd::Window window(600, 400, "Demo");
		
		kd::AudioSystem as(&window);
		kd::AudioBuffer ab(&as);
		ab.loadFromWave("data/audio/startup_sound.wav");
		ab.play();

		float timer = 0.0f;
		static const float intervals = 0.25f;
		while (kd::Window::pollEvents())
		{
			if (KD_INPUT.getKeyPressed('W'))
				KD_LOGGER.log("The sauce");

			timer += KD_CLOCK.deltaTime();
			while(timer >= intervals)
			{
				timer -= intervals;
				window.setTitle(
					"Demo    | Time: " + 
					std::to_string(UINT_S(KD_CLOCK.time())) +
					" FPS: " +
					std::to_string(UINT_S(1.0f / KD_CLOCK.deltaTime()))
				);
			}

			window.swapBuffers();

			glBegin(GL_TRIANGLES);
			glVertex2f(-0.5f, -0.5f);
			glVertex2f(0.0f, 0.5f);
			glVertex2f(0.5f, -0.5f);
			glEnd();

			engine.update();
		}
	}
	catch (const kd::Exception& err)
	{
		std::cerr << err.what();
		std::cin.get();
	}
	
	return 0;
}
