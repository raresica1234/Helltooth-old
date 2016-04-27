#include "sandbox.h"

using namespace sandbox;
using namespace ht;
using namespace graphics;

Sandbox::Sandbox() {
	std::cout << "SandBox constructed!" <<std::endl;
	m_Window = new Window("First Window!", 1024, 768);
	glClearColor(0.3f, 0.4f, 0.7f, 1.0f);
}

void Sandbox::update() const{
	maths::vec2 vector(123, 32);
	maths::vec2 vector2(2, 77);
	maths::vec2 vector3 = vector + vector2;
	vector3.print();
	vector3 = vector * vector2;
	vector3.print();
	vector3 = vector - vector2;
	vector3.print();
	vector3.print();

	while (!m_Window->closed()) {
		m_Window->clear();
		glColor3f(0.0, 1.0, 1.0);
		glBegin(GL_TRIANGLES);
		glVertex2f(-0.5, -0.5);
		glVertex2f(0.0f, 0.5f);
		glVertex2f(0.5f, -0.5f);
		glEnd();
		m_Window->update();
	}
}

Sandbox::~Sandbox() {
	std::cout << "SandBox deconstructed!"<<std::endl;
	delete m_Window;
}