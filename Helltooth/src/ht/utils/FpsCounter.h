#pragma once

#include "Log.h"

namespace ht { namespace utils {

	class FpsCounter {
	private:
		uint32 ups, fps, MAX_UPS, lastFps, lastUps;

		f32 updateTick, time = 0.0f;

		int64 freq, begin;

		uint64 currentTime, lastTime;

	private:
		__forceinline void restart()
		{
			begin = getCounter();
		}

		__forceinline f32 getElapsedTime()
		{
			return (f32)(getCounter() - begin) / freq;
		};

		__forceinline bool isOver(f32 secs)
		{
			if (secs >= getElapsedTime())
			{
				restart();
				return true;
			}
			return false;
		};


	public:

		__forceinline FpsCounter(const uint32 MAX_UPS) {
			this->MAX_UPS = MAX_UPS;

			ups = 0;
			fps = 0;
			updateTick = 1.0f / MAX_UPS;

			lastTime = getTime();
			freq = getFrequency();
			restart();
		}

		__forceinline void init() {
			lastTime = getTime();
		}

		__forceinline bool update() {
			currentTime = getTime();
			if (getElapsedTime() - time >= updateTick) {
				ups++;
				time += updateTick;
				return true;
			}
			return false;
		}

		__forceinline void render() {
			fps++;
		}

		__forceinline bool tick() {
			if ((currentTime - lastTime) > 0.5) {
				HT_INFO("fps %i ups %i", fps, ups);
				lastFps = fps;
				lastUps = ups;
				ups = 0;
				fps = 0;
				lastTime = currentTime;
				return true;
			}
			return false;
		}

		__forceinline uint32 getFPS() { return lastFps; }
		__forceinline uint32 getUPS() { return lastUps; }

		__forceinline uint64 getTime() {
			LARGE_INTEGER time, frequency;

			QueryPerformanceCounter(&time);
			QueryPerformanceFrequency(&frequency);

			return time.QuadPart / frequency.QuadPart;
		}

		__forceinline uint64 getCounter() {
			LARGE_INTEGER time;

			QueryPerformanceCounter(&time);

			return time.QuadPart;
		}

		__forceinline uint64 getFrequency() {
			LARGE_INTEGER time;

			QueryPerformanceFrequency(&time);

			return time.QuadPart;
		}

	};

} }
