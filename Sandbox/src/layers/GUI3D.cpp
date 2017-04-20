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

	sprite = htnew Sprite(100, 100, 200, 300);
	sprite->setColor(vec4(0.3, 0.4, 0.7, 1.0));

	label = createLabel("Don't look", 20, 10, 400, 40, "Arial", vec2(10, 2));
	label->setBackgroundColor(vec4(0.3, 0.4, 0.7, 1.f));

	color.w = 1.0f;
	utils::String s = String("GLVersion: ") + (const char*)glGetString(GL_VERSION);

	label2 = createLabel(s, 20, 50, 1800, 40, "Jenna", vec2(10, 2));
	label2->setBackgroundColor(vec4(0.3, 0.4, 0.7, 1.f));
	label2->onHover([](const Event &e) {
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
	});

	//button = createButton("Don't press me!", 700, 800, 600, 150, "Verdana", vec2(100, 40));
	//button->setBackgroundColor(0xFF0000db);
	//button->setPressedColor(0xFF03db00);
	//button->onClick([](const Event& e) {
	//	unsigned int i = 0;
	//	if (e.mouse_buttons[0])
	//		glfwSetWindowShouldClose(WindowManager::Get()->getWindow(i)->getWindow(), 1);
	//});
	//
	//texture = TextureManager::Get()->getTexture(TextureManager::Get()->createTextureFromFile("/res/logo.jpg"));
	//
	diffuse = createImage((unsigned int)0, 40.f, 40.f, 700.f, 500.f);
	position = createImage((unsigned int)1, 740.f, 40.f, 700.f, 500.f);
	//uvs = createImage((unsigned int)2, 40.f, 540.f, 700.f, 500.f);
	normal = createImage((unsigned int)2, 740.f, 540.f, 700.f, 500.f);
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
	label2->setBackgroundColor(color);
	GUILayer::update(e);
}