#pragma once
#include "Core.h"
#include "Logger.h"
#include "Clock.h"
#include "Input/InputSystem.h"

#define KD_ENGINE kd::Engine::get()
#define KD_LOGGER KD_ENGINE.logger
#define KD_CLOCK KD_ENGINE.clock
#define KD_INPUT KD_ENGINE.inputSystem

KD_NAMESPACE_BEGIN

class KD_CORE_DLL Engine
{
public:
	Engine();
	~Engine();

	void update();

	Logger logger;
	Clock clock;
	InputSystem inputSystem;

	static Engine& get();
private:
	static Engine* engine_;
};

KD_NAMESPACE_END
