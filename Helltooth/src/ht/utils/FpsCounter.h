#pragma once

#include <Windows.h>
#include <iostream>

namespace ht { namespace utils {

	class FpsCounter
	{
	private:
		unsigned int ups, fps, MAX_UPS;

		float updateTick;
		float time = 0.0f;

		__int64 freq;
		__int64 begin;

		unsigned __int64 currentTime, lastTime;

	private:
		inline void restart()
		{
			begin = getCounter();
		}

		inline float getElapsedTime()
		{
			return (float)(getCounter() - begin) / freq;
		};

		inline bool isOver(float secs)
		{
			if (secs >= getElapsedTime())
			{
				restart();
				return true;
			}
			return false;
		};


	public:

		FpsCounter(const unsigned int MAX_UPS) {
			this->MAX_UPS = MAX_UPS;

			ups = 0;
			fps = 0;
			updateTick = 1.0f / MAX_UPS;

			lastTime = getTime();
			freq = getFrequency();
			restart();
		}

		~FpsCounter() { }

		void init() {
			lastTime = getTime();
		}

		bool update() {
			currentTime = getTime();
			if (getElapsedTime() - time >= updateTick) {
				ups++;
				time += updateTick;
				return true;
			}
			return false;
		}

		void render() {
			fps++;
		}

		void show() {
			if ((currentTime - lastTime) > 0.5) {
				std::cout << "fps " << fps << " ups " << ups << std::endl;
				ups = 0;
				fps = 0;
				lastTime = currentTime;
			}
		}

		unsigned __int64 getTime() {
			LARGE_INTEGER time, frequency;

			QueryPerformanceCounter(&time);
			QueryPerformanceFrequency(&frequency);

			return time.QuadPart / frequency.QuadPart;
		}

		unsigned __int64 getCounter() {
			LARGE_INTEGER time;

			QueryPerformanceCounter(&time);

			return time.QuadPart;
		}

		unsigned __int64 getFrequency() {
			LARGE_INTEGER time;

			QueryPerformanceFrequency(&time);

			return time.QuadPart;
		}

	};

} }
