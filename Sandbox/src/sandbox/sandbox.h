#pragma once

#define API_MODE 2
#define API_TYPE 1

#include <random>
#include <stdio.h>
#include <iostream>

#ifdef _WINDOWS_
#	undef _WINDOWS_
#endif
#include <Windows.h>

#include <src/ht/Helltooth.h>

#define WIDTH	1024
#define HEIGHT	768

namespace sandbox {

	class Sandbox {
	private:
		ht::graphics::Window* m_Window;
		ht::graphics::ShaderProgram *program;

		ht::graphics::Cube *cube;
		ht::graphics::Entity3D *entity;

		ht::graphics::Renderable *model;

		ht::graphics::EntityRenderer *renderer;

		ht::utils::FpsCounter *counter;

		ht::graphics::Camera *camera;

		unsigned int id;

		unsigned int TYPE = API_OPENGL;
		unsigned int MODE = API_MODE_3D;

		std::vector<ht::graphics::Entity3D> entities;

	public:
		Sandbox();
		~Sandbox();

		void init();
		void start();

		void update();
		void render();
	};
};
