#include "sandbox.h"


using namespace sandbox;
using namespace ht;
using namespace graphics;

Sandbox::Sandbox() {
	std::cout << "SandBox constructed!" <<std::endl;
	m_Window = new Window(m_Title, m_width, m_height);
}

void Sandbox::update() const {
	glClearColor(0.3,0.4,0.7,1.0);
	while (!m_Window->closed()) {
		m_Window->update();
		m_Window->clear();
	}
}

Sandbox::~Sandbox() {
	std::cout << "SandBox deconstructed!"<<std::endl;
	delete m_Window;
}