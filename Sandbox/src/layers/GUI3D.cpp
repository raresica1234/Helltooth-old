#include "GUI3D.h"

#include <string>

vec4 color = vec4();

#define GUI_SIZE_H 768
#define GUI_SIZE_W GUI_SIZE_H * 16 / 9

#define HAS_TRANSFORMATION_STACK  1

GUI::GUI(Window* window, FpsCounter *counter)
	: GUILayer(1920, 1080), counter(counter), window(window) {
	GUILayer::setMatrix(mat4::createOrthographic(0, 1920, 1080, 0, 1.1f, -1.1f));

	FontManager::Get()->addFont("/res/arial.ttf", "Arial", 48);
	FontManager::Get()->addFont("/res/verdana.ttf", "Verdana", 18);
	FontManager::Get()->addFont("/res/consola.ttf", "Jenna", 24);
	Font& f = FontManager::Get()->getFont();

	sprite = htnew Sprite(100, 100, 250, 300);
	sprite->setColor(vec4(0.3f, 0.4f, 0.7f, 1.0f));

	label = createLabel("Don't look", 20, 10, 200, 30, "Arial", vec2(10, 2));
	label->setBackgroundColor(vec4(0.3f, 0.4f, 0.7f, 1.f));
	label->setTextColor(vec4(0.7, 0.3, 0.3, 1.0));
	color.w = 1.0f;
	utils::String s = String("GLVersion: ") + (const char*)glGetString(GL_VERSION);

	label2 = createLabel(s, 20, 40, s.size * 15, 30, "Jenna", vec2(10, 2));
	label2->setBackgroundColor(vec4(0.3, 0.4, 0.7, 1.f));
	label2->onHover([](const Event &e, GUIItem* item) {
		color.z += 0.01f;

		if (color.z > 1.0f) {
			color.z = 0.0f;
			color.y += 0.1f;
		}

		if (color.y > 1.0f) {
			color.y = 0.0f;
			color.x += 0.2f;
		}

		if (color.x > 1.0f) {
			color.x = 0.0f;
		}
		Label* label = (Label*)item;
		label->setBackgroundColor(color);
	});

	box = createTextbox(50, 50, 1000, 100, "Arial", 13, vec2(5, 5));
	box->setBackgroundColor(vec4(0.7, 0.5, 0.6, 1.0));
	box->setTextColor(vec4(0.5, 0.5, 0.5, 1.0));
}

GUI::~GUI() {
	del sprite;
	del label;
}

void GUI::render() {
	GUILayer::begin();
	GUILayer::submitGUI();
	GUILayer::render();
}

void GUI::tick() {
	fpsDisplay = "FPS: ";
	fpsDisplay += std::to_string(counter->getFPS()).c_str();
	fpsDisplay += " UPS:";
	fpsDisplay += std::to_string(counter->getUPS()).c_str();
	label->setText(fpsDisplay);
}

void GUI::update(const Event &e) {
	GUILayer::update(e);
}