#include <Kadaver/Core/Engine.h>
#include <Kadaver/Core/Window.h>
#include <Kadaver/Core/Audio/AudioSystem.h>
#include <Kadaver/Core/Audio/AudioBuffer.h>
#include <Kadaver/Core/Audio/AudioListener.h>
#include <Kadaver/Core/Audio/AudioSource.h>
#include <Kadaver/Core/Math/Vector3.h>

#include <iostream>

void keyCallback(int action, int key)
{
	if (action == KD_ACTION_DOWN)
	{
		KD_LOGGER.log("Key pressed: " + std::to_string(key));
	}
	else
	{
		KD_LOGGER.log("Key released: " + std::to_string(key));
	}
}

void mouseMoveCallback(int x, int y)
{
	KD_LOGGER.log("x: " + std::to_string(x) + " y: " + std::to_string(y));
}

void mouseButtonCallback(int action, int button)
{
	if(action == KD_ACTION_DOWN)
	{
		KD_LOGGER.log("Button clicked: " + std::to_string(button));
	}
	else
	{
		KD_LOGGER.log("Button released: " + std::to_string(button));
	}
}

void mouseWheelCallback(int delta)
{
	KD_LOGGER.log("Scrolling: " + std::to_string(delta));
}

int main(int argc, char** argv)
{
	KD_UNUSED(argc);
	KD_UNUSED(argv);

	kd::Window::setKeyCallback(keyCallback);
	kd::Window::setMouseMoveCallback(mouseMoveCallback);
	kd::Window::setMouseButtonCallback(mouseButtonCallback);
	kd::Window::setMouseWheelCallback(mouseWheelCallback);

	try
	{
		kd::Engine engine;
		kd::Window window(600, 400, "Demo");
		
		float timer = 0.0f;
		static const float intervals = 0.25f;
		
		while (kd::Window::pollEvents())
		{
			engine.update();
			
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
		}
	}
	catch (const kd::Exception& err)
	{
		std::cerr << err.what();
		std::cin.get();
	}
	
	return 0;
}
