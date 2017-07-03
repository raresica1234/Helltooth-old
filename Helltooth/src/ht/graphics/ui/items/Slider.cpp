#include "Slider.h"

namespace ht { namespace graphics { namespace ui {

	Slider::Slider(const f32 &x, const f32 &y, const f32 &width, const f32 &height, const uint32 &steps, bool vertical)
		: GUIItem(x, y, width, height), vertical(vertical), sliderPosition(x, y), steps(steps) {
		border = htnew Sprite(0, 0, width, height);
		border->setColor(maths::vec4(0.f, 0.f, 0.f, 1.f));
		background = htnew Sprite(1, 1, width - 2, height - 2);
		background->setColor(maths::vec4(1.f, 1.f, 1.f, 1.f));

		if (vertical)
			slider = htnew Sprite(1, 1, width - 2, (height - 2) / (f32)steps);
		else
			slider = htnew Sprite(1, 1, (width - 2) / (f32)steps, height - 2);

		slider->setColor(maths::vec4(.5f, .5f, .5f, 1.f));

		sprites.push_back(slider);
		sprites.push_back(background);
		sprites.push_back(border);
	}

	Slider::~Slider(){
		if (background) del background;
		if (border) del border;
		del slider; // slider is necessary
	}

	void Slider::update(const utils::Event &e) {
		if (e.handled)
			return;

		f32 mx = e.mouseX;
		f32 my = e.mouseY;

		if (mx >= size.x && mx <= (size.x + size.z) && my >= size.y && my <= (size.y + size.w)) {
			f_OnHover(e);
			
			for (unsigned int i = 0; i < MAX_BUTTONS; i++)
				if (e.mouse_buttons[i]) {
					f_OnClick(e);
					f_OnDrag(e);
					updateSlider(mx, my);
				}
			e.handled = true;
			if (!e.mouse_buttons[0]) firstClick = true;
		}
	}

	void Slider::updateSlider(f32 &mx, f32 &my) {
		if (vertical) {
			if (my > (slider->data.y + size.y) && my < (slider->data.y + slider->data.w + size.y) && firstClick)
				return;
			else
				firstClick = false;

			slider->data.y = (my - size.y - (slider->data.w / 2));

			if ((slider->data.y + slider->data.w) > (background->data.w + background->data.y)) slider->data.y = (background->data.w + background->data.y) - slider->data.w;
			if ((slider->data.y) < background->data.y) slider->data.y = background->data.y;
		}
		else {
			if (mx > (slider->data.x + size.x) && mx < (slider->data.x + slider->data.z + size.x) && firstClick)
				return;
			else
				firstClick = false;

			slider->data.x = (mx - size.x - (slider->data.z / 2));

			if ((slider->data.x + slider->data.z) >(background->data.z + background->data.x)) slider->data.x = (background->data.z + background->data.x) - slider->data.z;
			if ((slider->data.x) < background->data.x) slider->data.x = background->data.x;
		}
	}

} } }