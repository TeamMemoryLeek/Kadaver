#pragma once

#include "Core.h"
#include <string>
#include "Kadaver/Core/Threads/Mutex.h"

KD_NAMESPACE_BEGIN

enum
{
	LOG_DEFAULT = 0b0000'0000'0000'0001,
	LOG_IO = 0b0000'0000'0000'0010,
	LOG_RENDERING = 0b0000'0000'0000'0100,
	LOG_MEMORY = 0b0000'0000'0000'1000,
	LOG_GAME_OBJECT = 0b0000'0000'0001'0000,
	LOG_SYSTEM = 0b0000'0000'0010'0000,
};

class KD_CORE_DLL Logger
{
public:
	Logger();
private:
	void print(std::string message, uint level);
public:
	void log(const std::string& message, uint flag = LOG_DEFAULT);
	void logWarning(const std::string& message, uint flag = LOG_DEFAULT);
	void logError(const std::string& message, uint flag = LOG_DEFAULT);

	// Enables/disables the output from trace and warning
	// log calls with the specified flag.
	void setFlag(uint flag, bool value);
	void setFlagTrace(uint flag, bool value);
	void setFlagWarning(uint flag, bool value);
	void setFlagError(uint flag, bool value);
private:
	uint traceFlags_;
	uint warningFlags_;
	uint errorFlags_;

	Mutex mutex_;
};

KD_NAMESPACE_END