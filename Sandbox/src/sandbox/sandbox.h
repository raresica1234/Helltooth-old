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
		Layer *guis;

		RawModel *rawModel;

		FBO *fbo;

		Quad *quad;
		World* world;
		StaticEntity* sentity;
		DynamicEntity* dentity;

		List<DynamicEntity*> dentities;

		unsigned int id;

		bool compile = false;

		float y = 0.0f;

	public:
		Sandbox();
		~Sandbox();

		void init() override;

		void update() override;
		void render() override;

		void tick() override;
	};
};
