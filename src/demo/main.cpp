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
		kd::SoundBuffer soundBuffer(&audioSystem);
		soundBuffer.loadFromWave("data/audio/cymbal.wav");
		kd::SoundBuffer soundBuffer2(&audioSystem);
		soundBuffer2.loadFromWave("data/audio/snare.wav");

		soundBuffer.play();
		soundBuffer2.play();
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
