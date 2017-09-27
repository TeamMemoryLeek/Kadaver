#include <Kadaver/Core/Engine.h>
#include <Kadaver/Core/Window.h>
#include <Kadaver/Core/Audio/AudioSystem.h>
#include <Kadaver/Core/Audio/SoundBuffer.h>

#include <iostream>


int main(int argc, char** argv)
{
	KD_UNUSED(argc);
	KD_UNUSED(argv);

	try
	{
		kd::Engine engine;
		kd::Window window(600, 400, "Demo");
		kd::AudioSystem audioSystem(&window);
		kd::SoundBuffer startUpAudio(&audioSystem);
		startUpAudio.loadFromWave("data/audio/startup_sound.wav");
		startUpAudio.play();

		while (kd::Window::pollEvents())
		{
		}
	}
	catch (const std::exception& err)
	{
		std::cerr << err.what();
		std::cin.get();
	}
	
	return 0;
}
