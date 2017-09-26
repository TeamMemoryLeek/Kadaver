#include <Kadaver/Core/Engine.h>
#include <Kadaver/Core/Window.h>

#include <iostream>


int main(int argc, char** argv)
{
	KD_UNUSED(argc);
	KD_UNUSED(argv);

	try
	{
		kd::Engine engine;
		kd::Window window(600, 400, "Demo");

		while (kd::Window::pollEvents());
	}
	catch (const std::exception& err)
	{
		std::cerr << err.what();
		std::cin.get();
	}
	
	return 0;
}
