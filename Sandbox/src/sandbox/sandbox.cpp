#include "sandbox.h"

using namespace sandbox;

Sandbox::Sandbox()
	: Application("Sandbox", WIDTH, HEIGHT) {
	glClearColor(0.3f, 0.4f, 0.7f, 1.0f);

	API::API(TYPE, MODE);

	ShaderProgram* program = htnew ShaderProgram("src/shaders/shader.vert", "src/shaders/shader.frag");
	Camera* camera = htnew Camera(window);
	layer = htnew Layer(program, camera);

	entity = htnew Entity3D(vec3(0, -20, -50));

	mat4 projectionMatrix = mat4::createPerspective(70, 0.1f, 1000.0f, WIDTH / HEIGHT);
	layer->setMatrix(projectionMatrix);

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);


	rawModel = API::loadObjFile("res/stall.obj");

	model = htnew Renderable();
	model->loadRawModel(rawModel);

	model->setTexture(API::loadTextureFromFile("res/stallTexture.png"));

	entity->rotate(vec3(0, 180, 0));
	Application::start();
}

void Sandbox::init(){
	entity->scale(vec3(10, 10, 10));

	Application::init();
}

void Sandbox::update() {
	layer->update();
}

void Sandbox::render() {
	layer->submit(model, *entity);
	layer->render();
}

Sandbox::~Sandbox()  {

	delete layer;
	delete model;

	delete entity;
}