#include "Engine.h"

#include <iostream>
#include <assert.h>

KD_NAMESPACE_BEGIN

Engine* Engine::engine_ = nullptr;

Engine::Engine()
{
	engine_ = this;
	logger.log("Initializing Kadaver Engine");
}

Engine::~Engine()
{
	logger.log("Shutting down Kadaver Engine");
	engine_ = nullptr;
}

void kd::Engine::update()
{
	clock.update();
}

Engine& Engine::get()
{
	assert(engine_ && "Engine not created!");
	return *engine_;
}

KD_NAMESPACE_END
