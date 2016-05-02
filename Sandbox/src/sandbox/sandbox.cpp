#include "sandbox.h"

using namespace sandbox;
using namespace ht;
using namespace graphics;
using namespace utils;

Sandbox::Sandbox() {
	std::cout << "SandBox constructed!" << std::endl;
	m_Window = new Window("First Window!", WIDTH, HEIGHT);
	glClearColor(0.3f, 0.4f, 0.7f, 1.0f);
	program = new ShaderProgram("src/shaders/shader.vert", "src/shaders/shader.frag");
	renderable3D = new Renderable3D();

	unsigned int max_ups = 60;
	counter = new FpsCounter(max_ups);
}

void Sandbox::init() {
	GLfloat data[] = {
		-0.5f, -0.5f, -0.5f,
		0.0f,  0.5f, -0.5f,
		0.5f, -0.5f, -0.5f
	};

	GLint indices[] = {
		0,2,1
	};

	renderable3D->bindVAO();

	renderable3D->addBufferData(data, sizeof(data), RENDERABLE_3DCOORDS);
	renderable3D->addBufferData(indices, sizeof(indices));

	renderable3D->unbindVAO();

	program->start();
	mat4 projectionMatrix = mat4::createPerspective(70, 0.1f, 1000.0f, WIDTH / HEIGHT);
	program->uniformMat4("projectionMatrix", projectionMatrix);
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
	
	//update

}

void Sandbox::render() {
	renderable3D->flush();
}

Sandbox::~Sandbox() {
	std::cout << "SandBox deconstructed!"<< std::endl;

	delete counter;
	delete renderable3D;
	delete program;
	delete m_Window;
}