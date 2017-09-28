#include "Clock.h"

KD_NAMESPACE_BEGIN

Clock::Clock()
	: deltaTime_(0.0)
	, time_(0.0)
{
	time_ = getCurrentTime(true);
}

void Clock::update()
{
	double now = getCurrentTime();
	deltaTime_ = now - time_;
	time_ = now;
}

double Clock::getCurrentTime(bool resetStartTime /*= false*/)
{
	auto now = std::chrono::system_clock::now();
	if (resetStartTime)
		startTime_ = now;
	std::chrono::duration<double> elapsedSeconds = now - startTime_;
	return elapsedSeconds.count();
}

KD_NAMESPACE_END
