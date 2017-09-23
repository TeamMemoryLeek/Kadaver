#include "Engine.h"

#include <iostream>


KD_NAMESPACE_BEGIN

Engine::Engine()
{
	std::cout << "Initializing Kadaver Engine" << std::endl;
}

Engine::~Engine()
{
	std::cout << "Shutting down Kadaver Engine" << std::endl;
}

KD_NAMESPACE_END
