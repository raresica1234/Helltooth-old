#include "SponzaTest.h"

SponzaTest::SponzaTest(Window* window)
	:Layer(htnew Camera(window)) {
	
	VFS::mount("res", "res/Sponza-out");

	Layer::setMatrix(mat4::createPerspective(70.0f, 0.1f, 10000.0f, WIDTH / HEIGHT));

	glEnable(GL_DEPTH_TEST);

	String components[] = {
		String("arch"), String("background"), String("blue_curtains"), String("blue_fabric"),
		String("bricks"), String("celling"), String("chains"), String("column_a"),
		String("column_b"), String("column_c"), String("details"), String("flag_pole"),
		String("floor"), String("green_curtains"), String("green_fabric"), String("leaves"),
		String("lion"), String("red_curtains"), String("red_fabric"), String("roof"),
		String("vase"), String("vase_hanging"), String("vase_plant"), String("vase_round")
	};

	String resources[] = {
		String("model.obj"), String("albedo.tga"), String("normal.tga") , String("metallic.tga"), String("roughness.tga")
	};

	//skybox
	stack[0].addSkyboxPath("/res/violentdays.htcubemap");


	for (int i = 0; i < sizeof(components) / sizeof(String); i++) {
		String data = String("/res/") + components[i] + "/" + resources[0];
		stack[i + 1].addModelPath(data);
		for (int j = 1; j < sizeof(resources) / sizeof(String); j++) {
			String data = String("/res/") + components[i] + "/" + resources[j];
			stack[i + 1].addTexturePath(data);
		}
	}

	//Stack size - skybox (1)
	for (int i = 0; i < stack.getSize() - 1; i++) {
		sponzaScene.push_back(htnew DynamicEntity(nullptr, 0.f, 0.f, 0.f));
		sponzaScene[i]->scale(0.000005f, 0.000005f, 0.000005f);
	}
	lamp = htnew PointLight(vec3(0, 5000, 0), vec3(0, 0, 1), vec3(0,0,0));
	lamp2 = htnew PointLight(vec3(0, 5, 0), vec3(1, 0, 0), vec3(0, 0, 0));
}

SponzaTest::~SponzaTest() {
	forceCleanUP();
	for (int i = 0; i < sponzaScene.size(); i++)
		del sponzaScene[i];
	del box;
}

void SponzaTest::init() {
	stack.queueUp();
	pushLight(lamp);
	pushLight(lamp2);
}

void SponzaTest::load(bool &loaded) {
	if (!stack.isLoaded()) {
		stack.prepareResources();
	}
	loaded = this->loaded;
}

void SponzaTest::update(const utils::Event& e)  {
	if (!stack.isLoaded())
		return;

	if (loaded == false && stack.isLoaded()) {
		for (int i = 0; i < stack.getSize() - 1; i++) {
			sponzaScene[i]->renderable = stack.getAsModel(i + 1);
		}
		box = stack.getAsSkybox(0);
		submit(box);
		loaded = true;
	}

	Layer::update(e);
}
void SponzaTest::render() {
	if (!loaded)
		return;

	for (unsigned int i = 0; i < sponzaScene.size(); i++)
		submit(sponzaScene[i]);

	Layer::render();
	cleanUP();
}

void SponzaTest::tick() {

}


