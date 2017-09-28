#include <Kadaver/Core/Engine.h>
#include <Kadaver/Core/Window.h>
#include <Kadaver/Core/Audio/AudioSystem.h>
#include <Kadaver/Core/Audio/AudioBuffer.h>
#include <Kadaver/Core/Audio/AudioListener.h>
#include <Kadaver/Core/Audio/AudioSource.h>
#include <Kadaver/Core/Math/Vector3.h>

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
		kd::AudioBuffer startUpAudio(&audioSystem);
		startUpAudio.loadFromWave("data/audio/startup_sound.wav");
		kd::AudioSource source(kd::Vector3(0.0f, 0.0f, 1.0f));
		kd::AudioListener listener(kd::Vector3::zero, 0.f);

		source.playBuffer(&startUpAudio);

		while (kd::Window::pollEvents())
		{
			source.update();
			listener.rotation_ = startUpAudio.getProgress() * 360.0f;
		}
	}
	catch (const std::exception& err)
	{
		std::cerr << err.what();
		std::cin.get();
	}
	
	return 0;
}
