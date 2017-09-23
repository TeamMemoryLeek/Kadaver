#include "Logger.h"
#include <cstdio>
#include <iostream>

KD_NAMESPACE_BEGIN

Logger::Logger()
	: traceFlags_(-1)
	, warningFlags_(-1)
	, errorFlags_(-1)
{
}

void Logger::log(
	const std::string& message, 
	uint flag /*= LOG_DEFAULT*/
) const
{
	if (traceFlags_ & flag)
	{
		printf((message + "\n").c_str());
	}
}

void Logger::logWarning(
	const std::string& message, 
	uint flag /*= LOG_DEFAULT*/
) const
{
	if (warningFlags_ & flag)
	{
		fprintf(stderr, ("WARNING: " + message + "\n").c_str());
	}
}

void Logger::logError(
	const std::string& message, 
	uint flag /*= LOG_DEFAULT*/
) const
{
	if (errorFlags_ & flag)
	{
		fprintf(stderr, ("ERROR: " + message + "\n").c_str());
	}
}

void Logger::setFlag(uint flag, bool value)
{
	setFlagTrace(flag, value);
	setFlagWarning(flag, value);
}

#define KD_LOGGER_SET_FLAG(MASK, FLAG, VALUE) \
if (VALUE) \
	MASK |= FLAG; \
else \
	MASK &= ~FLAG;

void Logger::setFlagTrace(uint flag, bool value)
{
	KD_LOGGER_SET_FLAG(traceFlags_, flag, value);
}

void Logger::setFlagWarning(uint flag, bool value)
{
	KD_LOGGER_SET_FLAG(warningFlags_, flag, value);
}

void Logger::setFlagError(uint flag, bool value)
{
	KD_LOGGER_SET_FLAG(errorFlags_, flag, value);
}

#undef KD_LOGGER_SET_FLAG

KD_NAMESPACE_END

