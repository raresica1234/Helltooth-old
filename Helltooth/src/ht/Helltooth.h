#pragma once

#pragma region Helltooth
#pragma region assets
#include "assets/Asset.h"
#include "assets/ObjLoader.h"
#include "assets/ResourceStack.h"

#include "assets/FileSystem/FileSystem.h"
#pragma endregion

#pragma region graphics
#include "graphics/API.h"
#include "graphics/Camera.h"
#include "graphics/Layer.h"


#include "graphics/rendering/Renderable.h"
#include "graphics/rendering/Entity.h"
#include "graphics/rendering/FBO.h"

#include "graphics/rendering/2D/Sprite.h"

#include "graphics/rendering/renderers/Renderer.h"
#include "graphics/rendering/renderers/SimpleRenderer.h"

#include "graphics/rendering/renderers/2D/BatchRenderer2D.h"

#include "graphics/rendering/model/Cube.h"
#include "graphics/rendering/model/Quad.h"

#include "graphics/rendering/types/StaticEntity.h"
#include "graphics/rendering/types/DynamicEntity.h"

#include "graphics/shaders/ShaderProgram.h"
#include "graphics/shaders/ShaderManager.h"
#include "graphics/shaders/DynamicShader.h"

#include "graphics/terrain/World.h"

#include "graphics/textures/Texture.h"
#include "graphics/textures/TextureManager.h"

#include "graphics/ui/font/FontManager.h"

#include "graphics/ui/GUILayer.h"
#include "graphics/ui/GUIItem.h"

#include "graphics/ui/items/Label.h"

#include "graphics/window/Window.h"
#include "graphics/window/WindowManager.h"

#pragma endregion

#pragma region maths
#include "maths/vec2.h"
#include "maths/vec3.h"
#include "maths/vec4.h"

#include "maths/mat4.h"
#pragma endregion

#pragma region utils + tools
#include "utils/input/Input.h"
#include "utils/FileUtils.h"
#include "utils/FpsCounter.h"
#include "utils/String.h"

//UTILS -> MEMORY
#include "utils/memory/MemoryManager.h"

//TOOLS
#include "tools/Cereal/Cereal.h"
#include "tools/VFS/VFS.h"
#pragma endregion
#pragma endregion Engine includes

class Application {
private:
	ht::graphics::Layer* loadingScreen;
	ht::graphics::DynamicEntity* e;
	ht::graphics::ShaderProgram* program;
	ht::graphics::DynamicShader vertex;
	ht::graphics::DynamicShader fragment;
	
protected:
	std::vector<ht::graphics::Layer*> layers;
	ht::graphics::Window* window;
	ht::utils::FpsCounter *counter;

	bool loaded[50];

	bool loadeds = false;

public:
#pragma region Application
	Application(const char* title, int width, int height, int MAX_UPS = 60)
		:vertex(330, true), fragment(330, true) {
		ht::graphics::WindowManager::Init();
		ht::graphics::TextureManager::Init();
		ht::graphics::ShaderManager::Init();
		ht::assets::FileSystem::Init();
		ht::graphics::FontManager::Init();
		ht::utils::Input::Init();

		HT_WARN("%s", std::string(" _   _      _ _ _              _   _     "));
		HT_WARN("%s", std::string("| | | |    | | | |            | | | |    "));
		HT_WARN("%s", std::string("| |_| | ___| | | |_ ___   ___ | |_| |__  "));
		HT_WARN("%s", std::string("|  _  |/ _ \\ | | __/ _ \\ / _ \\| __| '_ \\ "));
		HT_WARN("%s", std::string("| | | |  __/ | | || (_) | (_) | |_| | | |"));
		HT_WARN("%s", std::string("\\_| |_/\\___|_|_|\\__\\___/ \\___/ \\__|_| |_|"));
		unsigned int wID = ht::graphics::API::createWindow(title, width, height);
		window = ht::graphics::WindowManager::Get()->getWindow(wID);
		counter = htnew ht::utils::FpsCounter(MAX_UPS);
	}

	~Application() {
		del e;
		del program;
		del counter;
		while (!layers.empty()) {
			del PopLayer();
		}
	}
#pragma endregion Constructor - Deconstructor
public:
#pragma region Application
	void start() {
		counter->init();

		init();
		while (!window->closed()) {
			window->clear();

			if (counter->update()) update();

			counter->render();
			
			render();
			if(counter->tick()) tick();

			window->update();
		}

		ht::graphics::FontManager::End();
		ht::graphics::ShaderManager::End();
		ht::graphics::TextureManager::End();
		ht::graphics::WindowManager::End();
		ht::assets::FileSystem::End();
	}

	virtual void init() {
		vertex.addInputVariable("position", ht::graphics::VEC3, ht::graphics::POSITIONS);
		vertex.addInputVariable("textureCoords", ht::graphics::VEC2, ht::graphics::TEXTURECOORDINATES);
		vertex.addOutputVariable("textureCoordinates", ht::graphics::VEC2);

		vertex.addVariable("projectionMatrix", ht::graphics::MAT4, ht::graphics::UNIFORM);
		vertex.addVariable("viewMatrix", ht::graphics::MAT4, ht::graphics::UNIFORM);
		vertex.addVariable("modelMatrix", ht::graphics::MAT4, ht::graphics::UNIFORM);

		vertex.addMainCode("gl_Position = vec4(position.x *2, position.y *2, position.z, 1.0)");
		vertex.addMainCode("textureCoordinates.x = textureCoords.x");
		vertex.addMainCode("textureCoordinates.y = 1 - textureCoords.y");

		fragment.addInputVariable("textureCoordinates", ht::graphics::VEC2, ht::graphics::FRAGMENT);
		fragment.addVariable("textures[32]", ht::graphics::SAMPLER2D, ht::graphics::UNIFORM);

		fragment.addOutputVariable("color", ht::graphics::VEC4);

		fragment.addMainCode("color = texture(textures[0], textureCoordinates)");

		program = htnew ht::graphics::ShaderProgram(vertex.toString(), fragment.toString(), false);
		
		loadingScreen = htnew ht::graphics::Layer(program);
		loadingScreen->setMatrix(ht::maths::mat4::createOrthographic(-1.0f, 1.0f, 1.0f, -1.0f, 1.0f, -1.0f));

		auto r = htnew ht::graphics::Renderable();

		ht::graphics::Cube* cube = htnew ht::graphics::Cube();
		r->loadRawModel(cube->getModel());
		r->addTexture(ht::graphics::TextureManager::Get()->createTextureFromFile("../Sandbox/res/textures/logo.jpg"));

		e = htnew ht::graphics::DynamicEntity(r);
		e->move(ht::maths::vec3(0.0f, 0.0f, 1.0f));

		if (!loaded) {
			loadingScreen->submit(e);
			loadingScreen->render();
			loadingScreen->cleanUP();
		}
	}

	virtual void render() {
		if (!allLoaded()) {
			loadingScreen->submit(e);
			loadingScreen->render();
			loadingScreen->cleanUP();
			return;
		}

		for (unsigned int i = 0; i < layers.size(); i ++) {
			layers[i]->render();
		}
	}

	virtual void update() {
		if(!allLoaded())
			for (unsigned int i = 0; i < layers.size(); i++)
				if (loaded[i] != true)
					layers[i]->load(loaded[i]);		
		
		const ht::utils::Event& e = ht::utils::Input::Get()->pullEvents();

		for (ht::graphics::Layer* layer : layers)
			layer->update(e);
	}

	virtual void tick() {
		for (ht::graphics::Layer* layer : layers)
			layer->tick();
	}
#pragma endregion Basic functions

	void PushLayer(ht::graphics::Layer* layer) {
		layer->init();
		layers.push_back(layer);
	}

	ht::graphics::Layer* PopLayer() {
		ht::graphics::Layer* layer = layers.back();
		layers.pop_back();
		return layer;
	}

	void PopLayer(ht::graphics::Layer* layer) {
		for (unsigned int i = 0; i < layers.size(); i++) 
			if (layers[i] == layer) {
				layers.erase(layers.begin() + i);
				break;
			}
	}

	private:
		bool allLoaded() {
			if (loadeds)
				return loadeds;

			loadeds = true;
			for (unsigned int i = 0; i < layers.size(); i++)
				loadeds = (loadeds == true && loaded[i] == true) ? true : false;
			return loadeds;
		}

};