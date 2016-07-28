#include "sandbox.h"

using namespace sandbox;

Sandbox::Sandbox()
	: Application("Sandbox", WIDTH, HEIGHT) {
	glClearColor(0.3f, 0.4f, 0.7f, 1.0f);

	API::API(TYPE, MODE);

	Camera* camera = htnew Camera(window);
	layer = htnew Layer(API::createShader("src/shaders/shader.vert", "src/shaders/shader.frag"), camera);

	entity = htnew Entity3D(vec3(0, -20, -50));

	layer->setMatrix(mat4::createPerspective(70, 0.1f, 1000.0f, WIDTH / HEIGHT));

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); 

	model = htnew Renderable();
	model->loadRawModel(API::loadObjFile("res/stall.obj"));

	model->addTexture(API::loadTextureFromFile("res/stallTexture.png"));
	model->addTexture(API::loadTextureFromFile("res/stallTextureSpecular.png"));

	entity->rotate(vec3(0, 180, 0));
	Application::start();
}

void Sandbox::init(){
	entity->scale(vec3(10, 10, 10));

	Application::init();
}

void Sandbox::update() {
	layer->update();
	if (Input::getKey(GLFW_KEY_R))
		compile = true;
}

void Sandbox::render() {
	layer->submit(model, *entity);
	layer->render();
}

void Sandbox::tick() {
	if (compile) {
		ShaderManager::reCompile();
		layer->reloadTextures();
		compile = false;
	}
}

Sandbox::~Sandbox()  {

	delete layer;
	delete model;

	delete entity;
}