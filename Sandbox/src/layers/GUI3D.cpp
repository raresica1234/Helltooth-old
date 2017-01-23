#include "GUI3D.h"

GUI::GUI(Window* window)
	: GUILayer() {
	GUILayer::setMatrix(mat4::createOrthographic(-1., 1., 1., -1., -1., 1.));

	FontManager::Get()->addFont("/res/arial.ttf", "Arial", 10);

	texture = FontManager::Get()->getFont().texture;

	sprite = htnew Sprite(-.33, -.33, .44, .44, texture);

}

GUI::~GUI() {
	//del sprite;
}

void GUI::render() {
	GUILayer::begin();

	GUILayer::submit(sprite);

	GUILayer::submit("I hope this works", -0.7, -0.7, maths::vec4(1.0, 0.0, 1.0, 1.0));

	GUILayer::render();
}

void GUI::update() {}