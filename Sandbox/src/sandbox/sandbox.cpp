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

	counter = htnew FpsCounter(60);
}

void Sandbox::init()
{
	entity->scale(vec3(1, 1, 1));

	program->start();
	program->uniformMat4("modelMatrix", entity->generateModelMatrix());

	std::default_random_engine generator;
	std::uniform_int_distribution<int> distributionPOS(-100, 100);
	std::uniform_int_distribution<int> distributionPOSz(-100, 250);
	std::uniform_int_distribution<int> distributionROT(1, 1000);

	for (int i = 0; i < 2500; i++)
	{
		Entity3D entity = Entity3D(distributionPOS(generator), distributionPOS(generator), -distributionPOSz(generator));
		entity.rotate(vec3(distributionROT(generator), distributionROT(generator), distributionROT(generator)));
		entity.scale(3, 3, 3);

		entities.push_back(entity);
	}

	

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
	program->start();
	program->uniformMat4("viewMatrix", camera->generateViewMatrix());
	program->stop();
	renderer->render();
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