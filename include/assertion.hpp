#pragma once

#include <cstdio>
#include <cstdlib>

#ifdef _DEBUG
#define LOG(...) printf(__VA_ARGS__)
#define ASSERT(x, ...)    \
	if (!(x))             \
	{                     \
		printf(__VA_ARGS__); \
		printf("\nAt %s:%d\n", __FILE__, __LINE__); \
		fflush(stdout);      \
		exit(1);             \
	}
#else
#define LOG(...)
#define ASSERT(x, ...)
#endif // _DEBUG

#define RELEASE_ASSERT(x, ...)\
	if (!(x))                 \
	{                         \
		printf(__VA_ARGS__); \
		printf("\nAt %s:%d\n", __FILE__, __LINE__); \
		fflush(stdout);      \
		exit(1);             \
	}
