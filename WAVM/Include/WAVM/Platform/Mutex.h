#pragma once

#include "WAVM/Inline/Assert.h"
#include "WAVM/Inline/BasicTypes.h"
#include "WAVM/Platform/Defines.h"

namespace WAVM { namespace Platform {
	// Platform-independent mutexes.
	struct Mutex
	{
		PLATFORM_API Mutex();
		PLATFORM_API ~Mutex();

		// Don't allow copying or moving a Mutex.
		Mutex(const Mutex&) = delete;
		Mutex(Mutex&&) = delete;
		void operator=(const Mutex&) = delete;
		void operator=(Mutex&&) = delete;

		PLATFORM_API void lock();
		PLATFORM_API void unlock();

		PLATFORM_API bool isLockedByCurrentThread();

	private:
#ifdef WIN32
		struct CriticalSection
		{
			Uptr data[5];
		} criticalSection;
		bool isLocked;
#elif defined(__linux__)
		struct PthreadMutex
		{
			Uptr data[5];
		} pthreadMutex;
#elif defined(__APPLE__)
		struct PthreadMutex
		{
			Uptr data[8];
		} pthreadMutex;
#elif defined(__WAVIX__)
		struct PthreadMutex
		{
			Uptr data[6];
		} pthreadMutex;
#else
#error unsupported platform
#endif
	};
}}

#define wavmAssertMutexIsLockedByCurrentThread(mutex) wavmAssert(mutex.isLockedByCurrentThread())