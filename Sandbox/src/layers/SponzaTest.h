#pragma once
#ifdef _WINDOWS_
#	undef _WINDOWS_
#endif
#include <Windows.h>

#include <src/ht/Helltooth.h>
#include <vector>

using namespace ht;
using namespace graphics;
using namespace maths;
using namespace assets;
using namespace utils;

#define WIDTH (float)1280
#define HEIGHT (float)720

class SponzaTest : public Layer {
private:
	std::vector<DynamicEntity*> sponzaScene;
	Skybox* box;
	ResourceStack stack;

	bool loaded = false;

	PointLight* lamp;
	PointLight* lamp2;

	maths::vec3 direction = vec3(1,0,0);
public:
	SponzaTest(Window* window);
	~SponzaTest();

	void init() override;
	void load(bool &loaded) override;

	void update(const utils::Event& e) override;
	void tick() override;
	void render() override;

	void defaultRenderer() override { /*no renderer -> otherwise memory leak*/ }
};
