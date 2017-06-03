#pragma once
#ifdef _WINDOWS_
#	undef _WINDOWS_
#endif
#include <Windows.h>

#include <src/ht/Helltooth.h>

using namespace ht;
using namespace graphics;
using namespace maths;
using namespace assets;
using namespace utils;

#define WIDTH 1280
#define HEIGHT 720

class Test3D : public Layer {
private:
	Quad *quad;
	StaticEntity* sentity;
	DynamicEntity* dentity;
	Skybox* box;

	ResourceStack stack;

	std::vector<ht::graphics::DynamicEntity*> dentities;

	bool loaded = false;

	unsigned int width;
	unsigned int height;


public:
	Test3D(Window* window);
	~Test3D();

	void init() override {
		dentity->scale(5, 5, 5);


		stack.queueUp();
	}

	void load(bool &loaded);

	void update(const Event& e) override;
	void render() override;

	void defaultRenderer() override { /*no renderer -> otherwise memory leak*/ }

};
