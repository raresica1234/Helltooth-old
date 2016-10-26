#pragma once

#ifdef _WINDOWS_
	#undef _WINDOWS_
#endif

#include <Windows.h>
#include <iostream>
#include <stdio.h>

//Color definitions
#define HT_LEVEL_FATAL		0x04
#define HT_LEVEL_ERROR		0x0C
#define HT_LEVEL_WARNING	0x0E
#define HT_LEVEL_INFO		0x0F
#define HT_LEVEL_MESSAGE	0x07

//Log level
#define HT_LOG_LEVEL		3

//Log levels
#define HT_LOG_FATAL		0
#define HT_LOG_ERROR		1
#define HT_LOG_WARNING		2
#define HT_LOG_INFO			3
#define HT_LOG_MESSAGE		4

#if HT_LOG_LEVEL >= HT_LOG_FATAL
#define HT_FATAL(...) ht::utils::Log::log(HT_LEVEL_FATAL, true, __VA_ARGS__)
#define _HT_FATAL(...) ht::utils::Log::log(HT_LEVEL_FATAL, false, __VA_ARGS__)
#else
#define HT_FATAL(...) //nothing
#define _HT_FATAL(...) //nothing
#endif

#if HT_LOG_LEVEL >= HT_LOG_ERROR
#define HT_ERROR(...) ht::utils::Log::log(HT_LEVEL_ERROR, true, __VA_ARGS__)
#define _HT_ERROR(...) ht::utils::Log::log(HT_LEVEL_ERROR, false, __VA_ARGS__)
#else
#define HT_ERROR(...) //nothing
#define _HT_ERROR(...) //nothing
#endif

#if HT_LOG_LEVEL >= HT_LOG_WARNING
#define HT_WARN(...) ht::utils::Log::log(HT_LEVEL_WARNING, true, __VA_ARGS__)
#define _HT_WARN(...) ht::utils::Log::log(HT_LEVEL_WARNING, false, __VA_ARGS__)
#else
#define HT_WARN(...) //nothing
#define _HT_WARN(...) //nothing
#endif

#if HT_LOG_LEVEL >= HT_LOG_INFO
#define HT_INFO(...) ht::utils::Log::log(HT_LEVEL_INFO, true, __VA_ARGS__)
#define _HT_INFO(...) ht::utils::Log::log(HT_LEVEL_INFO, false, __VA_ARGS__)
#else
#define HT_INFO(...) //nothing
#define _HT_INFO(...) //nothing
#endif

#if HT_LOG_LEVEL >= HT_LOG_MESSAGE
#define HT_MSG(...) ht::utils::Log::log(HT_LEVEL_MESSAGE, true, __VA_ARGS__)
#define _HT_MSG(...) ht::utils::Log::log(HT_LEVEL_MESSAGE, false, __VA_ARGS__)
#else
#define HT_MSG(...) //nothing
#define _HT_MSG(...) //nothing
#endif

namespace ht { namespace utils {

	class Log {
	private:
		static void setColor(const int logLevel) {
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), logLevel);
		}
		
	public:
		template<typename First, typename ... Args>
		static void log(const int logLevel, bool newline, First arg, Args... message) {
			setColor(logLevel);

			printf(arg, std::forward<Args>(message)...);
			if (newline)
				printf("\n");
		}
	};

} }

#ifdef DEBUG
#define HT_ASSERT(x, ...)  \
					if (!(x)) { \
					HT_ERROR("*************************"); \
					 HT_ERROR("    ASSERTION FAILED!    "); \
					 HT_ERROR("*************************"); \
										HT_ERROR(__FILE__, ": ", __LINE__); \
					 HT_ERROR("Condition: ", #x); \
					 HT_ERROR(__VA_ARGS__); \
					 __debugbreak(); \
					}
#else
#define HT_ASSERT(x, ...)
#endif
