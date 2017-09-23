#pragma once
#include "Core.h"
#include "Logger.h"

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
