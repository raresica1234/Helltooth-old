#pragma once

//ASSETS
#include "assets/Asset.h"

//GRAPHICS
#include "graphics/Window.h"
#include "graphics/API.h"
#include "graphics/Camera.h"
#include "graphics/Layer.h"
#include "graphics/ObjLoader.h"

#include "graphics/lighting/Light.h"
#include "graphics/lighting/Sun.h"

#include "graphics/rendering/Renderable.h"
#include "graphics/rendering/Entity3D.h"
#include "graphics/rendering/EntityRenderer3D.h"
#include "graphics/rendering/FBO.h"

#include "graphics/rendering/model/Cube.h"
#include "graphics/rendering/model/Quad.h"

#include "graphics/shaders/ShaderProgram.h"
#include "graphics/shaders/ShaderManager.h"

#include "graphics/textures/Texture.h"

//MATHS
#include "maths/vec2.h"
#include "maths/vec3.h"
#include "maths/vec4.h"
#include "maths/mat4.h"

//UTILS
#include "utils/Input.h"
#include "utils/FileUtils.h"
#include "utils/FpsCounter.h"

//UTILS -> MEMORY
#include "utils/memory/MemoryManager.h"

//TOOLS

using namespace ht;
using namespace graphics;
using namespace assets;

class Application {
protected:
	Window* window;
	FpsCounter *counter;

public:
	Application(const char* title, int width, int height, int MAX_UPS = 60) {
		window = htnew Window(title, width, height);
		counter = htnew FpsCounter(MAX_UPS);
	}

	~Application() {
		ShaderManager::cleanUP();
		delete counter;
		delete window;
	}
protected:
	void start() {
		init();
		while (!window->closed()) {
			window->clear();

			if (counter->update()) update();

			counter->render();
			render();

			if(counter->tick()) tick();

			window->update();
		}
	}

	virtual void init() {
		Input::init();
		counter->init();
	}

	virtual void render() = 0;

	virtual void update() = 0;

	virtual void tick() {}
};