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
}

void Sandbox::update(){
	program->start();
	mat4 projectionMatrix = mat4::createProjection(70, 0.1f, 1000.0f, WIDTH, HEIGHT);
	program->uniformMat4("projectionMatrix", projectionMatrix);
	
	while (!m_Window->closed()) {
		m_Window->clear();
		if (Input::getKey(GLFW_KEY_Q))
			z += 0.001f;
			
		if (Input::getKey(GLFW_KEY_W))
			z -= 0.001f;

		glColor3f(0.0, 1.0, 1.0);
		glBegin(GL_TRIANGLES);
		glVertex3f(-0.5f ,-0.5f , z);
		glVertex3f( 0.0f , 0.5f , z);
		glVertex3f( 0.5f ,-0.5f , z);
		glEnd();
		std::cout << z << std::endl;
		m_Window->update();
	}
}

Sandbox::~Sandbox() {
	std::cout << "SandBox deconstructed!"<<std::endl;
	delete m_Window;
	delete program;
}