#include "sandbox.h"

using namespace sandbox;
using namespace ht;
using namespace graphics;
using namespace utils;

Sandbox::Sandbox()
{
	std::cout << "SandBox constructed!" << std::endl;

	m_Window = htnew Window("First Window!", WIDTH, HEIGHT);

	glClearColor(0.3f, 0.4f, 0.7f, 1.0f);

	API::API(TYPE, MODE);

	program = htnew ShaderProgram("src/shaders/shader.vert", "src/shaders/shader.frag");

	entity = htnew Entity3D(vec3(1, 1, -5));

	cube = htnew Cube();

	camera = htnew Camera(m_Window);

	renderer = htnew EntityRenderer(program);

	mat4 projectionMatrix = mat4::createPerspective(70, 0.1f, 1000.0f, WIDTH / HEIGHT);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	program->start();
	program->uniformMat4("projectionMatrix", projectionMatrix);
	program->uniformMat4("viewMatrix", mat4::createIdentity());
	program->stop();

	model = htnew Renderable();
	model->loadRawModel(cube->getModel());

	model->setTexture(assets::Asset::loadTextureFromFile("res/bitch.tga"));

	counter = htnew FpsCounter(60);
}

void Sandbox::init()
{
	entity->scale(vec3(1, 1, 1));

	program->start();
	program->uniformMat4("modelMatrix", entity->getModelMatrix());

	std::default_random_engine generator;
	std::uniform_int_distribution<int> distributionPOS(-100, 100);
	std::uniform_int_distribution<int> distributionPOSz(-100, 250);
	std::uniform_int_distribution<int> distributionROT(1, 1000);

	for (int i = 0; i < 10000; i++)
	{
		Entity3D entity = Entity3D((float)distributionPOS(generator), (float)distributionPOS(generator), (float)-distributionPOSz(generator));
		entity.rotate(vec3((float)distributionROT(generator), (float)distributionROT(generator), (float)distributionROT(generator)));
		entity.scale(1, 1, 1);

		entities.push_back(entity);
	}

	renderer->setCamera(camera);

	counter->init();
}

void Sandbox::start()
{
	init();

	while (!m_Window->closed())
	{
		m_Window->clear();

		if(counter->update()) update();

		counter->render();
		render();

		counter->show();

		m_Window->update();
	}
}

void Sandbox::update() { 
	entity->rotate(vec3(1, 1, 1));
	camera->update();
}

void Sandbox::render() {
	
	renderer->pushEntityList(model, entities);
	renderer->pushEntity(model, *entity);
	renderer->render();
	renderer->cleanUP();
}

Sandbox::~Sandbox() {

	delete counter;

	delete renderer;
	delete model;

	delete cube;

	delete entity;

	delete m_Window;

	std::cout << "SandBox deconstructed!" << std::endl;
}