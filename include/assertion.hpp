#include <cstdio>

#ifdef _DEBUG
#define LOG(...) printf(__VA_ARGS__)
#define ASSERT(x, ...)    \
	if (!(x))             \
	{                     \
		printf(__VA_ARGS__); \
		while (1);        \
	}
#else
#define LOG(...)
#define ASSERT(x, ...)
#endif // _DEBUG

#define RELEASE_ASSERT(x, ...)\
	if (!(x))                 \
	{                         \
		printf(__VA_ARGS__);  \
		while (1);            \
	}
