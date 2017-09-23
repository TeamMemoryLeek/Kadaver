#pragma once
#include "Core.h"
#include "Logger.h"

#define KD_ENGINE kd::Engine::get()
#define KD_LOG(MESSAGE) KD_ENGINE.logger.log(MESSAGE)
#define KD_LOG_WARNING(MESSAGE) KD_ENGINE.logger.logWarning(MESSAGE)
#define KD_LOG_ERROR(MESSAGE) KD_ENGINE.logger.logError(MESSAGE)

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
