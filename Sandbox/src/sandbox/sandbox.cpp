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
}

void Sandbox::update(){
	GLfloat data[] = {
		-0.5f, -0.5f, -0.5f,
		 0.0f,  0.5f, -0.5f,
		 0.5f, -0.5f, -0.5f
	};

	GLint indices[] = {
		0,1,2
	};

	renderable3D->addBufferData(data, sizeof(data), RENDERABLE_3DCOORDS);
	renderable3D->addBufferData(indices, sizeof(data));

	program->start();
	mat4 projectionMatrix = mat4::createPerspective(70, 0.1f, 1000.0f, WIDTH / HEIGHT);
	program->uniformMat4("projectionMatrix", projectionMatrix);

	renderable3D->init();

	vec2 position;
	while (!m_Window->closed()) {
		m_Window->clear();
		
		renderable3D->flush();

		m_Window->update();
	}
}

Sandbox::~Sandbox() {
	std::cout << "SandBox deconstructed!"<< std::endl;
	delete renderable3D;
	delete program;
	delete m_Window;
}