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
public:
	GUI();

	~GUI();

	void render() override;

	void update() override;
};