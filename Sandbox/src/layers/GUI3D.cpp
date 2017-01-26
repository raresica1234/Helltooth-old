#include "GUI3D.h"

#include <string>

#define GUI_SIZE_H 768
#define GUI_SIZE_W GUI_SIZE_H * 16 / 9

GUI::GUI(Window* window, FpsCounter *counter)
	: GUILayer(), counter(counter), window(window) {
	GUILayer::setMatrix(mat4::createOrthographic(0, GUI_SIZE_W, GUI_SIZE_H, 0, 1.1f, -1.1f));

	FontManager::Get()->addFont("res/fonts/arial.ttf", "Arial", 32);

	Font& f = FontManager::Get()->getFont();

	sprite = htnew Sprite(500, 400, 200, 200, f.atlas->id);
}

GUI::~GUI() {
	del sprite;
}

void GUI::render() {
	GUILayer::begin();

	//GUILayer::submit(sprite);

	std::string fps = std::to_string(counter->getFPS());

	GUILayer::submit(fpsDisplay, 20, GUI_SIZE_H - 40, maths::vec4(1.f, 1.f, 1.f, 1.f));

	GUILayer::render();
}

void GUI::tick() {
	fpsDisplay = "FPS: ";
	fpsDisplay += std::to_string(counter->getFPS()).c_str();
	fpsDisplay += " UPS:";
	fpsDisplay += std::to_string(counter->getUPS()).c_str();
}

void GUI::update() {}