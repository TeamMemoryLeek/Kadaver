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
};

KD_NAMESPACE_END
