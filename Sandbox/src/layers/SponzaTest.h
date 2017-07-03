#pragma once
#ifdef _WINDOWS_
#	undef _WINDOWS_
#endif
#include <Windows.h>

#include <src/ht/Helltooth.h>
#include <vector>

using namespace ht;

using namespace audio;
using namespace assets;
using namespace graphics;
using namespace maths;
using namespace utils;

#define WIDTH (float)1280
#define HEIGHT (float)720

class SponzaTest : public Layer {
private:
	std::vector<DynamicEntity*> sponzaScene;
	Skybox* box;

	bool loaded = false;

	PointLight* lamp;
	PointLight* lamp2;

	SpotLight* lantern;

	DirectionalLight* sun;
	DirectionalLight* sun2;

	DynamicEntity *cube;
	Source *source;

	bool loop = false, play = false;

	maths::vec3 direction = vec3(1,0,0);

public:
	SponzaTest(Window* window);
	~SponzaTest();

	void init() override;

	void update(const utils::Event& e) override;
	void tick() override;
	void render() override;
};
