#pragma once

#include "Core.h"
#include <chrono>

KD_NAMESPACE_BEGIN

class KD_CORE_DLL Clock
{
public:
	Clock();

	void update();
	const float deltaTime() const
	{
		return FLOAT_S(deltaTime_);
	}
	const float time() const
	{
		return FLOAT_S(time_);
	}

private:
	double getCurrentTime(bool resetStartTime = false);

	std::chrono::time_point<std::chrono::system_clock> startTime_;
	double deltaTime_;
	double time_;
};

KD_NAMESPACE_END