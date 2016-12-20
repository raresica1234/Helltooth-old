#include "sandbox.h"
#include <stdlib.h>
#include <time.h>

using namespace sandbox;
using namespace ht;
using namespace graphics;
using namespace utils;
using namespace maths;

Sandbox::Sandbox()
	: Application("Sandbox", WIDTH, HEIGHT) {
	glClearColor(0.3f, 0.4f, 0.7f, 1.0f);

	API::API(API_OPENGL, API_MODE_3D);

	VFS::mount("shaders", "src/shaders");
	VFS::mount("res", "res/models/");
	VFS::mount("res", "res/textures/");

	Camera* camera = htnew Camera(window);
	layer = htnew Layer(API::createShader("/shaders/shader.vert", "/shaders/shader.frag"), camera);
	guis = htnew Layer(API::createShader("/shaders/quad.vert", "/shaders/quad.frag"));

	fbo = htnew FBO(WIDTH, HEIGHT);
	fbo->createColorTexture();
	fbo->createDepthTexture(false);

	guis->setMatrix(mat4::createOrthographic(-9.0f, 9.0f, 16.0f, -16.0f, -1.0f, 1.0f));
	layer->setMatrix(mat4::createPerspective(70, 0.1f, 10000.0f, WIDTH / HEIGHT));

	Renderable* guiRenderable = htnew Renderable();

	quad = htnew Quad();
	guiRenderable->loadRawModel(quad->getModel());
	guiRenderable->addTexture(fbo->getColorTexture());

	sentity = htnew StaticEntity(guiRenderable, 5.0f, -11.9f, 1.0f);
	sentity->scale(3, 3, 3);

	world = htnew World(800, vec4(1, 1, -1,-1));

	//Texture loading
	world->addTexture(TextureManager::Get()->createTextureFromFile("/res/grass.jpg"));

	Renderable* model = htnew Renderable();
	model->loadRawModel(API::loadObjFile("/res/stall.obj"));
	model->addTexture(TextureManager::Get()->createTextureFromFile("/res/stallTexture.png"));
	model->addTexture(TextureManager::Get()->createTextureFromFile("/res/stallTextureSpecular.png"));

	dentity = htnew DynamicEntity(model, vec3(0.0f, 0.0f, -55.0f));
	dentity->rotate(vec3(0, 180, 0));
	dentity->scale(3, 3, 3);
	unsigned int id = TextureManager::Get()->createTextureFromFile("/res/cobble.png");

	srand(time(nullptr));
	for (float i = 0; i < 200; i++) {
		int x = rand() % 100 - 50;
		int z = rand() % 100 - 50;
		Cube* cube = htnew Cube();
		Renderable* model = htnew Renderable();
		model->loadRawModel(cube->getModel());
		del cube;
		model->addTexture(id);
		DynamicEntity* entity = htnew DynamicEntity(model, vec3((float)x, 0.5f, (float)z));
		entity->scale(1, 1, 1);
		dentities.push_back(entity);
	}
	Application::start();
}

void Sandbox::init(){
	dentity->scale(vec3(1, 1, 1));

	layer->submit(world);
	guis->submit(sentity);

	Application::init();
}

void Sandbox::update() {
	layer->update();
	guis->update();

	for (unsigned int i = 0; i < dentities.size(); i++) 
		dentities[i]->rotate(vec3(0, 1.0f, 0));
	

	if (Input::getKey(GLFW_KEY_R))
		compile = true;

}

void Sandbox::render() {
	layer->submit(dentity);

	//for (unsigned int i = 0; i < dentities.size(); i++) {
	//	layer->submit(dentities[i]);
	//}
	
	fbo->bind();
	layer->render();
	fbo->unbind(window->getWidth(), window->getHeight());

	layer->render();
	guis->render();

	layer->cleanUP();
	guis->cleanUP();
}

void Sandbox::tick() {
	if (compile) {
		ShaderManager::Get()->reCompile();
		layer->reloadTextures();
		guis->reloadTextures();
		compile = false;
	}
}

Sandbox::~Sandbox()  {
	layer->forceCleanUP();
	guis->forceCleanUP();

	del world;

	del guis;
	del layer;

	del dentity;
	del sentity;

	del quad;
}