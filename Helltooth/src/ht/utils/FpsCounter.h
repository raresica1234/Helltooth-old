#pragma once

#include <Windows.h>
#include <iostream>



namespace ht { namespace utils {

	class FpsCounter {

	private:
		unsigned int ups, fps, MAX_UPS;
		
		float updateTick;
		float time = 0.0f;

		unsigned __int64 currentTime, lastTime;
		
	public:

		FpsCounter(unsigned int &MAX_UPS) {
			this->MAX_UPS = MAX_UPS;

			ups = 0;
			fps = 0;
			updateTick = 1.0f / MAX_UPS;

			lastTime = getTime();
		}

		~FpsCounter() {
		}
		
		void init() {
			lastTime = getTime();
		}

		bool update() {
			currentTime = getTime();
			if (currentTime - time >= updateTick) {
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
			if ((currentTime - lastTime) > 1) {
				std::cout << "fps " << fps << " ups " << ups << std::endl;
				ups = 0;
				fps = 0;
				lastTime = currentTime;
				time = 0.0f;
			}
		}

		unsigned __int64 getTime() {
			LARGE_INTEGER time, frequency;

			QueryPerformanceCounter(&time);
			QueryPerformanceFrequency(&frequency);

			return time.QuadPart / frequency.QuadPart;
		}

	};

} }
