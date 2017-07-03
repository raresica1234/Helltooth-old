#pragma once

#include "Logo"
#pragma region Helltooth
#pragma region assets
#include "assets/Asset.h"
#include "assets/ObjLoader.h"
#include "assets/ResourceStack.h"
#include "assets/ResourceManager.h"

#include "assets/FileSystem/FileSystem.h"
#pragma endregion

#pragma region audio
#include "audio/Audio.h"
#include "audio/AudioManager.h"
#include "audio/Source.h"
#pragma endregion

#pragma region graphics
#include "graphics/API.h"
#include "graphics/Camera.h"
#include "graphics/Layer.h"

#include "graphics/rendering/Renderable.h"
#include "graphics/rendering/Entity.h"
#include "graphics/rendering/FBO.h"
#include "graphics/rendering/Skybox.h"
#include "graphics/rendering/Light.h"

#include "graphics/rendering/2D/Sprite.h"

#include "graphics/rendering/renderers/Renderer.h"
#include "graphics/rendering/renderers/ForwardRenderer.h"
#include "graphics/rendering/renderers/DeferredRenderer.h"

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
#include "graphics/ui/items/Button.h"
#include "graphics/ui/items/Image.h"
#include "graphics/ui/items/Slider.h"

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

#pragma region Cool macros
#define Stack(x) (*stack)[x]
#pragma endregion

class Application {
protected:
	std::vector<ht::graphics::Layer*> layers;
	ht::graphics::Window* window;
	ht::utils::FpsCounter *counter;

	ht::graphics::GUILayer* layer;
	ht::graphics::ui::Image* logoImage;

public:
#pragma region Application
	Application(const char* title, int width, int height, int MAX_UPS = 60) {
		FreeImage_Initialise();
		ht::graphics::WindowManager::Init();
		ht::audio::AudioManager::Init();
		ht::graphics::TextureManager::Init();
		ht::graphics::ShaderManager::Init();
		ht::graphics::FontManager::Init();
		ht::assets::ResourceManager::Init();
		ht::assets::FileSystem::Init();
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
		layer = htnew ht::graphics::GUILayer(1, 1);
		layer->setMatrix(ht::maths::mat4::createOrthographic(0, 1, 1, 0, 1.1f, -1.1f));
		unsigned int id = ht::graphics::TextureManager::Get()->createTextureFromMemory(veryfuckinglongnamesoitdoesntconflictwithotherfiles,
			sizeof(veryfuckinglongnamesoitdoesntconflictwithotherfiles));
		logoImage = layer->createImage(id, 0, 0, 1, 1);
	}

	~Application() {
		while (!layers.empty()) {
			del PopLayer();
		}
		FreeImage_DeInitialise();
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

		ht::audio::AudioManager::End();
		ht::utils::Input::End();
		ht::assets::FileSystem::End();
		ht::assets::ResourceManager::End();
		ht::graphics::FontManager::End();
		ht::graphics::ShaderManager::End();
		ht::graphics::TextureManager::End();
		ht::graphics::WindowManager::End();
	}

	virtual void init() {
	}

	virtual void render() {
		if (!ht::assets::ResourceManager::Get()->isAllLoaded()) {
			layer->begin();
			layer->submitGUI();
			layer->render();
			return;
		}

		for (unsigned int i = 0; i < layers.size(); i ++) {
			layers[i]->render();
		}
	}

	virtual void update() {
		if(!ht::assets::ResourceManager::Get()->isAllLoaded())
			for (unsigned int i = 0; i < layers.size(); i++)
					layers[i]->load();
		
		const ht::utils::Event& e = ht::utils::Input::Get()->pullEvents();

		for (unsigned int i = layers.size(); i > 0; i--)
			layers[i - 1]->update(e);
	}

	virtual void tick() {
		for (ht::graphics::Layer* layer : layers)
			layer->tick();
	}
#pragma endregion Basic functions

	void PushLayer(ht::graphics::Layer* layer) {
		layers.push_back(layer);
		layer->init();
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

};