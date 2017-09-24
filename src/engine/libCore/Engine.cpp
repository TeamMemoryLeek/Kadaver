#include "Engine.h"

#include <iostream>
#include <assert.h>

KD_NAMESPACE_BEGIN

Engine* Engine::engine_ = nullptr;

Engine::Engine()
{
	engine_ = this;
	KD_LOG("Initializing Kadaver Engine", LOG_SYSTEM);
}

Engine::~Engine()
{
	KD_LOG("Shutting down Kadaver Engine", LOG_SYSTEM);
	engine_ = nullptr;
}

Engine& Engine::get()
{
	assert(engine_ && "Engine not created!");
	return *engine_;
}

KD_NAMESPACE_END
