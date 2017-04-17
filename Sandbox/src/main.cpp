#ifdef _WINDOWS_
#	undef _WINDOWS_
#endif
#include <Windows.h>

#include <src/ht/Helltooth.h>

#include "layers/Test3D.h"
#include "layers/GUI3D.h"
#include "layers/SponzaTest.h"

using namespace ht;
using namespace graphics;
using namespace maths;
using namespace assets;
using namespace utils;

class Main : public Application {
private:
	bool compile = false;

public:
	Main()
		: Application("Vand gaini", 1280, 720, 60) {
		glClearColor(0.3f, 0.4f, 0.7f, 1.0f);

		API::API(API_OPENGL, API_MODE_3D);

		VFS::mount("shaders", "src/shaders");
		VFS::mount("res", "res/models/");
		VFS::mount("res", "res/textures/");
		VFS::mount("res", "res/fonts/");
		VFS::mount("res", "res/skybox/");
	}

	~Main() {

	}
	void init() override {
		PushLayer(htnew SponzaTest(window));
		//PushLayer(htnew Test3D(window));
		PushLayer(htnew GUI(window, counter));
		Application::init();
	}

	void update() override {
		//if (Input::getKey(GLFW_KEY_R))
		//	compile = true;
		Application::update();
	}

	void render() override {
		Application::render();
	}

	void tick() override {
		if (compile) {
			ShaderManager::Get()->reCompile();
			for (ht::graphics::Layer* layer : layers)
				layer->reloadTextures();
			compile = false;
		}
		Application::tick();
	}
};

void main() {
	Main* something = htnew Main();
	something->start();
	del something;
}