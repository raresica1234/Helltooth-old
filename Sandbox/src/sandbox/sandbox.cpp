#include "sandbox.h"

using namespace sandbox;

Sandbox::Sandbox()
	: Application("Sandbox", WIDTH, HEIGHT) {
	glClearColor(0.3f, 0.4f, 0.7f, 1.0f);

	API::API(TYPE, MODE);

	Camera* camera = htnew Camera(window);
	layer = htnew Layer(API::createShader("src/shaders/shader.vert", "src/shaders/shader.frag"), camera);
	guis = htnew Layer(API::createShader("src/shaders/quad.vert", "src/shaders/quad.frag"));

	entity = htnew Entity3D(vec3(0, -20, -50));

	fbo = htnew FBO(window->getWidth(), window->getHeight());
	fbo->createColorTexture();
	fbo->createDepthTexture(false);

	guis->setMatrix(mat4::createOrthographic(9.0f, -9.0f, 16.0f, -16.0f, -1.0f, 1.0f));
	layer->setMatrix(mat4::createPerspective(70, 0.1f, 1000.0f, WIDTH / HEIGHT));

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); 
	gui = htnew Renderable();
	quad = htnew Quad();
	gui->loadRawModel(quad->getModel());
	gui->addTexture(fbo->getColorTexture());

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
	guis->update();

	if (Input::getKey(GLFW_KEY_R))
		compile = true;
}

void Sandbox::render() {
	layer->submit(model, *entity);
	Entity3D e = Entity3D(-5.0f, -12.0f, 1.0f);
	e.scale(2, 2, 2);
	guis->submit(gui, e);

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
		ShaderManager::reCompile();
		layer->reloadTextures();
		guis->reloadTextures();
		compile = false;
	}
}

Sandbox::~Sandbox()  {
	delete guis;
	delete layer;

	delete model;
	delete gui;

	delete entity;
	delete quad;
}