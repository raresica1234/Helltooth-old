#include "GUI3D.h"

GUI::GUI()
	: GUILayer() {
	sprite = htnew Sprite(-.33, -.33, .44, .44, vec4(0.f, 0.f, 0.f, 1.f));
	GUILayer::setMatrix(mat4::createOrthographic(-1., 1., 1., -1., -1., 1.));
}

GUI::~GUI() {
	del sprite;
}

void GUI::render() {
	GUILayer::begin();

	GUILayer::submit(sprite);

	GUILayer::render();
}

void GUI::update() {}