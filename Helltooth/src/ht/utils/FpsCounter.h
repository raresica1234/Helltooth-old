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

		void(*update(void));
		void(*render(void));

	public:
		FpsCounter(unsigned int &MAX_UPS, void(*update(void)), void(*render(void))) {
			this->MAX_UPS = MAX_UPS;
			this->update = update;
			this->render = render;

			ups = 0;
			fps = 0;
			updateTick = 1.0f / MAX_UPS;

			lastTime = getTime();
		}
		~FpsCounter() {
		}
		
		void updateCounter() {
			currentTime = getTime();

			if (currentTime - time >= updateTick) {
				update();
				ups++;
				time += updateTick;
			}

			render();
			fps++;

			if ((lastTime - currentTime) > 1) {
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
