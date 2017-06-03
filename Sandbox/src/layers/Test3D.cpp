#include "Test3D.h"

Test3D::Test3D(Window* window)
	: Layer(htnew Camera(window)){
	//renderer = htnew ForwardRenderer(camera);
	setMatrix(mat4::createPerspective(70, 0.1f, 500.0f, WIDTH / HEIGHT));

	stack[0].addTexturePath("/res/grass.jpg");

	stack[1].addModelPath("/res/stall.obj");
	stack[1].addTexturePath("/res/stallTexture.png");

	stack[2].addTexturePath("/res/cobble.jpg");

	stack[3].addSkyboxPath("/res/violentdays.htcubemap");

	dentity = htnew DynamicEntity(nullptr, vec3(0.0f, 10.0f, -55.0f));
	dentity->rotate(vec3(0, 180, 0));
	dentity->scale(3, 3, 3);

	for (float i = 0; i < 200; i++) {
		int x = rand() % 100 - 50;
		int z = rand() % 100 - 50;
		Cube* cube = htnew Cube();
		Renderable* model = htnew Renderable();
		model->loadRawModel(cube->getModel());
		del cube;
		DynamicEntity* entity = htnew DynamicEntity(model, vec3((float)x, 0.5f, (float)z));
		entity->scale(1, 1, 1);
		dentities.push_back(entity);
	}
}

void Test3D::update(const Event& e) {
	if (!stack.isLoaded())
		return;

	if (loaded == false && stack.isLoaded()) {
		dentity->renderable = stack.getAsModel(1);
		Texture* texture = stack.getAsTexture(2);
		box = stack.getAsSkybox(3);

		submit(box);

		for (DynamicEntity* dentity : dentities)
			dentity->getRenderable()->addTexture(texture);
		loaded = true;
	}

	for (unsigned int i = 0; i < dentities.size(); i++) {
		dentities[i]->rotate(maths::vec3(0, 1.0f, 0));
	}

	Layer::update(e);
}

void Test3D::render() {
	if (!loaded)
		return;

	for (DynamicEntity* dentity : dentities)
		submit(dentity);

	submit(dentity);

	Layer::render();

	cleanUP();
}

void Test3D::load(bool &loaded) {
	if (!stack.isLoaded()) {
		stack.prepareResources();
	}
	loaded = this->loaded;
}

Test3D::~Test3D() {
	for (DynamicEntity* e : dentities)
		del e;
	del sentity;
	del dentity;
	del box;
}