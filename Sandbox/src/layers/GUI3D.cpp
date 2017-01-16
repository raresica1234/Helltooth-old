#include "GUI3D.h"

GUI::GUI() {
	sprite = htnew Sprite(-.33, -.33, .44, .44, vec4(0.3, 0.223, 0.82, 1.0));
	GUILayer::setMatrix(mat4::createOrthographic(-1., 1., 1., -1., -1., 1.));
}

GUI::~GUI() {
	del sprite;
}

void GUI::render() {
	GUILayer::submit(sprite);
	GUILayer::render();
}

void GUI::update() {}