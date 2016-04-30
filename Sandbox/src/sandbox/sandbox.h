#pragma once

#include <iostream>
#include <src/ht/Helltooth.h>

#define WIDTH	1024
#define HEIGHT	768

namespace sandbox{
	class Sandbox {

	private:
		ht::graphics::Window* m_Window;
		ht::graphics::ShaderProgram* program;
		ht::graphics::Renderable3D *renderable3D;
		float z = 0;
	public:
		Sandbox();
		~Sandbox();
		void update();
	};
};
