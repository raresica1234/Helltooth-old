#pragma once

/*
	#define DEBUG makes a lot of DEBUG messages appear
	#define MEMORY makes all the memory stuff appear
	#define PRINT makes all the printing appear

*/

//GRAPHICS
#include "graphics/Window.h"
#include "graphics/API.h"
#include "graphics/Camera.h"

#include "graphics/shaders/ShaderProgram.h"

#include "graphics/rendering/Renderable.h"
#include "graphics/rendering/Entity3D.h"
#include "graphics/rendering/EntityRenderer.h"

#include "graphics/rendering/model/Cube.h"
#include "graphics/rendering/model/Pyramid.h"

#include "graphics/textures/Texture.h"


//MATHS
#include "maths/vec2.h"
#include "maths/vec3.h"
#include "maths/vec4.h"
#include "maths/mat4.h"

//UTILS
#include "utils/Input.h"
#include "utils/FileUtils.h"
#include "utils/FpsCounter.h"

//UTILS -> MEMORY
#include "utils/memory/MemoryManager.h"

//ASSETS
#include "assets/Asset.h"