#include "GUI3D.h"

GUI::GUI(Window* window)
	: GUILayer() {
	GUILayer::setMatrix(mat4::createOrthographic(0, window->getWidth(), 0, window->getHeight(), -1.1f, 1.1f));

	FontManager::Get()->addFont("/res/arial.ttf", "Arial", 50);

	texture = FontManager::Get()->getFont().texture;

	sprite = htnew Sprite(500, 400, 200, 200, texture);

}

GUI::~GUI() {
	del sprite;
}

void GUI::render() {
	GUILayer::begin();

	GUILayer::submit(sprite);

	//GUILayer::submit("!", 50, 50, maths::vec4(1.0, 0.0, 1.0, 1.0));

	GUILayer::render();
}

void GUI::update() {}