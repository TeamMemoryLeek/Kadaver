#pragma once
#include "Core.h"
#include "Logger.h"

#define KD_ENGINE kd::Engine::get()
#define KD_LOGGER KD_ENGINE.logger

KD_NAMESPACE_BEGIN

class KD_CORE_DLL Engine
{
public:
	Engine();
	~Engine();

	Logger logger;

	static Engine& get();
private:
	static Engine* engine_;
};

KD_NAMESPACE_END
