#pragma once

#define API_MODE 2
#define API_TYPE 1

#include <stdio.h>
#include <iostream>
#include <Windows.h>
#include <src/ht/Helltooth.h>

#define WIDTH	1024
#define HEIGHT	768

namespace sandbox{
	class Sandbox {

	private:
		ht::graphics::Window* m_Window;
		ht::graphics::ShaderProgram* program;
		ht::graphics::Renderable *renderable3D;
		ht::graphics::Cube *cube;

		ht::utils::FpsCounter *counter;

		ht::maths::mat4 view;

		float z = 0;
	public:
		Sandbox();
		~Sandbox();

		void init();
		void start();

		void update(void);
		void render(void);
	};
};
