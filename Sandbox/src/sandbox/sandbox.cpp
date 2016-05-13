#include "sandbox.h"



using namespace sandbox;
using namespace ht;
using namespace graphics;
using namespace utils;

Sandbox::Sandbox() {
	std::cout << "SandBox constructed!" << std::endl;
	
	m_Window = new Window("First Window!", WIDTH, HEIGHT);

	glClearColor(0.3f, 0.4f, 0.7f, 1.0f);

	API::API(TYPE, MODE);


	program = new ShaderProgram("src/shaders/shader.vert", "src/shaders/shader.frag");

	renderable3D = new Renderable();
	cube = new Cube(renderable3D);
	
	program->start();

	mat4 projectionMatrix = mat4::createPerspective(70, 0.1f, 1000.0f, WIDTH / HEIGHT);
	view = mat4::createIdentity();

	program->uniformMat4("projectionMatrix", projectionMatrix);

	program->uniformMat4("viewMatrix", view);

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	program->stop();

	renderer = new BatchRenderer(renderable3D, program);


	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	

	unsigned int max_ups = 60;
	counter = new FpsCounter(max_ups);
}

void Sandbox::init() {
	std::default_random_engine generator;
	std::uniform_int_distribution<int> distributionPOS(-50, 50);
	std::uniform_int_distribution<int> distributionPOSz(10, 250);
	std::uniform_int_distribution<int> distributionROT(1, 1000);

	for (int i = 0; i < 5000; i++) {
		Entity3D entity = Entity3D(distributionPOS(generator), distributionPOS(generator), -distributionPOSz(generator));
		entity.rotate(vec3(distributionROT(generator), distributionROT(generator), distributionROT(generator)));
		renderer->addEntity(entity);
	}
	

	renderer->prepare();

	counter->init();
}

void Sandbox::start() {
	init();
	while (!m_Window->closed()) {
		m_Window->clear();

		if(counter->update())
			update();

		counter->render();
		render();


		counter->show();

		m_Window->update();
	}
}

void Sandbox::update(){

}

void Sandbox::render() {
	renderer->render();
}

Sandbox::~Sandbox() {
	std::cout << "SandBox deconstructed!"<< std::endl;

	delete counter;

	delete renderable3D;
	delete cube;

	delete program;
	delete renderer;

	delete m_Window;
}