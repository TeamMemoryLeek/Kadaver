#include "Mutex.h"
#include "Engine.h"

KD_NAMESPACE_BEGIN

Mutex::Mutex()
	: interlock_(0)
{
}

void Mutex::lock()
{
#ifdef _WIN32
	while (interlock_ == 1 || InterlockedCompareExchange(&interlock_, 1, 0) == 1){}
#else
	while (interlock_ == 1 || __sync_lock_test_and_set(&interlock_, 1) == 1) {}
#endif
}

void Mutex::unlock()
{
	interlock_ = 0;
}

KD_NAMESPACE_END