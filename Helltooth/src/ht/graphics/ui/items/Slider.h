#pragma once

#include "../GUIItem.h"
#include "maths/vec2.h"

namespace ht { namespace graphics { namespace ui {

	class Slider : public GUIItem {
	private:
		Sprite *background = nullptr, *border = nullptr, *slider = nullptr;

		maths::vec2 sliderPosition;

		uint32 steps;
		uint32 backgroundColor, sliderColor, borderColor;

		uint16 borderSize;
		
		bool vertical;

		bool firstClick = true;

	public:
		Slider(const f32 &x, const f32 &y, const f32 &width, const f32 &height, const uint32 &steps, bool vertical = true);
		~Slider();

		__forceinline void setBorderSize(uint16 size) {
			background->data.x = size;
			background->data.y = size;
			background->data.z = this->size.z - size * 2;
			background->data.w = this->size.w - size * 2;

			slider->data.x = background->data.x;
			slider->data.y = background->data.y;

			if (vertical) {
				slider->data.z = (this->size.z - size * 2);
				slider->data.w = (this->size.w - size * 2) / steps;
			}
			else {
				slider->data.z = (this->size.z - size * 2) / steps;
				slider->data.w = (this->size.w - size * 2);
			}
		}

		const maths::vec2& getPosition() { return sliderPosition; }

		void update(const utils::Event &e) override;

		__forceinline void setBorderColor(maths::vec4 color) { border->setColor(color); }
		__forceinline void setBorderColor(uint32 color) { border->setColor(color); }

		__forceinline void setBackgroundColor(maths::vec4 color) { background->setColor(color); }
		__forceinline void setBackgroundColor(uint32 color) { background->setColor(color); }

		__forceinline void setSliderColor(maths::vec4 color) { slider->setColor(color); }
		__forceinline void setSliderColor(uint32 color) { slider->setColor(color); }

		__forceinline f32 getSliderStep() {
			if(vertical)

		}

	protected:
		void updateSlider(f32 &mx, f32 &my);

	};

} } }
