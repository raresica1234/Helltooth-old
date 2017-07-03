#include "SponzaTest.h"

SponzaTest::SponzaTest(Window* window)
	: Layer(htnew Camera(window), false) {
	
	VFS::mount("res", "res/Sponza-out/");

	Layer::setMatrix(mat4::createPerspective(70.0f, 0.1f, 10000.0f, WIDTH / HEIGHT));
	Layer::createResourceStack();

	String components[] = {
		String("arch"), String("background"), String("blue_curtains"), String("blue_fabric"),
		String("bricks"), String("celling"), String("chains"), String("column_a"),
		String("column_b"), String("column_c"), String("details"), String("flag_pole"),
		String("floor"), String("green_curtains"), String("green_fabric"), String("leaves"),
		String("lion"), String("red_curtains"), String("red_fabric"), String("roof"),
		String("vase"), String("vase_hanging"), String("vase_plant"), String("vase_round")
	};

	String resources[] = {
		String("model.obj"), String("albedo.tga")//, String("normal.tga") , String("metallic.tga"), String("roughness.tga")
	};

	//skybox
	Stack(0).addSkyboxPath("/res/violentdays.htcubemap");

	for (int i = 0; i < sizeof(components) / sizeof(String); i++) {
		String data = String("/res/") + components[i] + "/" + resources[0];
		Stack(i + 1).addModelPath(data);
		for (int j = 1; j < sizeof(resources) / sizeof(String); j++) {
			String data = String("/res/") + components[i] + "/" + resources[j];
			Stack(i + 1).addTexturePath(data);
		}
	}

	//Stack size - skybox (1)
	for (int i = 0; i < stack->getSize() - 1; i++) {
		sponzaScene.push_back(htnew DynamicEntity(nullptr, 0.f, 0.f, 0.f));
		sponzaScene[i]->scale(0.000005f, 0.000005f, 0.000005f);
	}
	lamp = htnew PointLight(vec3(500, 10.f, 0), vec3(0, 0, 1), vec3(0.23, .0025f, 0.f));
	lamp2 = htnew PointLight(vec3(-500, 10.f, 0), vec3(1, 0, 0), vec3(0.23, .0025f, 0.f));
	sun = htnew DirectionalLight(vec3(1, 1, 1), vec3(-0.25, -1, -0.25));
	sun2 = htnew DirectionalLight(vec3(1, 1, 1), vec3(0.25, -1, 0.25));
	lantern = htnew SpotLight(camera->getPosition(), vec3(1.f, 1.f, 1.f), camera->getDirection(), vec3(0.23, 0.0025, 0.f), vec2(25,3));

	Renderable* renderable = htnew Renderable();
	renderable->loadRawModel(API::loadObjFile("/res/cube.obj"));
	cube = htnew DynamicEntity(renderable, vec3(1293, 89, -538));
	cube->scale(3, 3, 3);

	uint32 id = AudioManager::Get()->createAudioFromFile("/res/bloop.wav");
	source = htnew Source(id);
	source->setPosition(cube->getPosition());
}

SponzaTest::~SponzaTest() {
	forceCleanUP();
	for (int i = 0; i < sponzaScene.size(); i++)
		del sponzaScene[i];
	del box;
	del lamp, lamp2, sun, sun2;
}

void SponzaTest::init() {
	Layer::init();
	pushLight(lamp);
	pushLight(lamp2);
	pushLight(lantern);
	pushLight(sun);
	//pushLight(sun2);
}

void SponzaTest::update(const utils::Event& e)  {
	if (!stack->isLoaded())
		return;

	if (loaded == false && stack->isLoaded()) {
		for (int i = 0; i < stack->getSize() - 1; i++) {
			sponzaScene[i]->renderable = stack->getAsModel(i + 1);
		}
		box = stack->getAsSkybox(0);
		submit(box);
		loaded = true;
	}

	lantern->setDirection(camera->getDirection());
	lantern->setPosition(camera->getPosition());

	AudioManager::Get()->setListenerPosition(camera->getPosition());
	AudioManager::Get()->setListenerDirection(camera->generateViewMatrix());

	if (e.isPressed(GLFW_KEY_P)) {
		if (play) source->pause();
		else source->play();

		play = !play;
	}
	Layer::update(e);
}
void SponzaTest::render() {
	if (!loaded)
		return;

	for (unsigned int i = 0; i < sponzaScene.size(); i++)
		submit(sponzaScene[i]);

	submit(cube);

	Layer::render();
	cleanUP();
}

void SponzaTest::tick() {

}


