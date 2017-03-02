#include "GUI3D.h"

#include <string>

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

	sprite = htnew Sprite(100, 100, 200, 300, vec4(1.0, 0.3, 0.5, 0.7));
}

GUI::~GUI() {
}

void GUI::render() {
	GUILayer::begin();

	std::string fps = std::to_string(counter->getFPS());
	FontManager::Get()->selectFont("Arial");
	GUILayer::submit(fpsDisplay, 20, 50, maths::vec4(1.f, 1.f, 1.f, 1.f));

	FontManager::Get()->selectFont("Jenna");
	GUILayer::submit(String("GLVersion: ") + (const char*)glGetString(GL_VERSION), 20, 80, vec4(1.f,1.f,1.f,1.f));

	//GUILayer::submit(sprite);

	GUILayer::render();
}

void GUI::tick() {
	fpsDisplay = "FPS: ";
	fpsDisplay += std::to_string(counter->getFPS()).c_str();
	fpsDisplay += " UPS:";
	fpsDisplay += std::to_string(counter->getUPS()).c_str();
}

void GUI::update(const Event& e) {}