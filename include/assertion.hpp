#pragma once

#include "std.hpp"

#if defined(_GNU)
#define DEBUG_BREAK asm("int3")
#elif defined(_MSVC)
#define DEBUG_BREAK _asm { int 3 }
#elif defined(_CLANG)
#define DEBUG_BREAK __builtin_debugtrap
#else
#define DEBUG_BREAK exit(1)
#endif


#ifdef _DEBUG
#define LOG(...) printf(__VA_ARGS__)
#define ASSERT(x, ...)    \
	if (!(x))             \
	{                     \
		printf("Assertion failed at %s:%d : ", __FILE__, __LINE__); \
		printf(__VA_ARGS__); \
		printf("\n");        \
		fflush(stdout);      \
		DEBUG_BREAK;         \
	}
#else
#define LOG(...)
#define ASSERT(x, ...)
#endif // _DEBUG

#define EXIT_ON_FAIL(x, ...)\
	if (!(x))                 \
	{                         \
		printf("Assertion failed at %s:%d : ", __FILE__, __LINE__); \
		printf(__VA_ARGS__); \
		printf("\n");        \
		fflush(stdout);      \
		exit(1);             \
	}
