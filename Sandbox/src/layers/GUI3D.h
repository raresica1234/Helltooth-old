#pragma once
#ifdef _WINDOWS_
#	undef _WINDOWS_
#endif
#include <Windows.h>

#include <src/ht/Helltooth.h>

using namespace ht;
using namespace graphics;
using namespace maths;
using namespace assets;
using namespace utils;


class GUI : public GUILayer {
	Sprite* sprite = nullptr;
	Texture* texture;
	Window* window;
	FpsCounter *counter;

	String fpsDisplay;

	int save = 0;

	mat4 transform;

public:
	GUI(Window* window, FpsCounter *counter);

	~GUI();

	void render() override;
	void update() override;

	void tick() override;
};