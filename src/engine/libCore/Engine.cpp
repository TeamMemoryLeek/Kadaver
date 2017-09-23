#include "Engine.h"

#include <iostream>
#include <assert.h>

KD_NAMESPACE_BEGIN

Engine* Engine::engine_ = nullptr;

Engine::Engine()
{
	std::cout << "Initializing Kadaver Engine" << std::endl;
	engine_ = this;
}

Engine::~Engine()
{
	std::cout << "Shutting down Kadaver Engine" << std::endl;
	engine_ = nullptr;
}

Engine& Engine::get()
{
	assert(engine_ && "Engine not created!");
	return *engine_;
}

KD_NAMESPACE_END
