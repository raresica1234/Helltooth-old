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


	unsigned int max_ups = 60;
	counter = new FpsCounter(max_ups);
}

void Sandbox::init() {
	program->start();

	mat4 projectionMatrix = mat4::createPerspective(70, 0.1f, 1000.0f, WIDTH / HEIGHT);
	mat4 model = mat4::createIdentity();
	view = mat4::createIdentity();

	model.translate(vec3(0, 0, -5.0f));
	view.rotate(vec3(z, z, z));


	program->uniformMat4("projectionMatrix", projectionMatrix);
	program->uniformMat4("modelMatrix", model);
	program->uniformMat4("viewMatrix", view);

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

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
	++z;
	view.rotate(vec3(z, 0, 0));
	program->uniformMat4("viewMatrix", view);

}

void Sandbox::render() {
	renderable3D->flush();
}

Sandbox::~Sandbox() {
	std::cout << "SandBox deconstructed!"<< std::endl;

	delete cube;
	delete counter;
	delete renderable3D;
	delete program;
	delete m_Window;
}