#include "Logger.h"
#include <cstdio>
#include <iostream>
#ifdef _WIN32
#include <windows.h>
#endif

KD_NAMESPACE_BEGIN

Logger::Logger()
	: traceFlags_(UINT_S(-1))
	, warningFlags_(UINT_S(-1))
	, errorFlags_(UINT_S(-1))
{
}

void Logger::print(std::string message, uint level) const
{
	// Set message prefix based on level
	static const char* prefixes[3] = {
		"", "WARNING: ", "ERROR: "
	};

	message = prefixes[level] + message;
	
	// Set console color
#ifdef _WIN32
	// TODO: Make this thread safe
	CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
	WORD consolePrevAttribs;
	HANDLE consoleHandle;

	consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(consoleHandle, &consoleInfo);
	consolePrevAttribs = consoleInfo.wAttributes;

	static const WORD attributes[3] =
	{
		7u, 14u, 12u
	};

	SetConsoleTextAttribute(consoleHandle, attributes[level]);
#else
	static const char* colorPrefixes[3] = 
	{
		"", "\033[1;33m", "\033[1;31m"
	};
	
	

	message = colorPrefixes[level] + message;
#endif

	printf((message + "\n").c_str());

	// Reset console attributes
#ifdef _WIN32
	SetConsoleTextAttribute(consoleHandle, consolePrevAttribs);
#else
	printf("\033[1;37m");
#endif
}

void Logger::log(
	const std::string& message,
	uint flag /*= LOG_DEFAULT*/
) const
{
	if (traceFlags_ & flag)
	{
		print(message, 0);
	}
}

void Logger::logWarning(
	const std::string& message,
	uint flag /*= LOG_DEFAULT*/
) const
{
	if (warningFlags_ & flag)
	{
		print(message, 1);
	}
}

void Logger::logError(
	const std::string& message,
	uint flag /*= LOG_DEFAULT*/
) const
{
	if (errorFlags_ & flag)
	{
		print(message, 2);
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

