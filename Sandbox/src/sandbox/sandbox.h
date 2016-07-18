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

	class Sandbox : public Application {
	private:
		Layer* layer;

		Entity3D *entity;

		Renderable *model;

		RawModel *rawModel;

		unsigned int id;

		unsigned int TYPE = API_OPENGL;
		unsigned int MODE = API_MODE_3D;

		std::vector<Entity3D> entities;
		bool compile;

	public:
		Sandbox();
		~Sandbox();

		void init() override;

		void update() override;
		void render() override;

		void tick() override;
	};
};
