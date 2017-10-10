#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>

#include <FreeImage.h>

#include <iostream>
#include <stdio.h>
#include <fstream>

#include <sstream>

#include "Cereal/Cereal.h"

#include "ImGUI/src/imgui.h"
#include "ImGUI/src/imgui_internal.h"

using namespace ImGui;
using namespace Cereal;

struct TextureData {
	BYTE* pixels;
	GLuint width, height, bpp, pitch;
	~TextureData() {
		delete[] pixels;
	}
};

struct TexturesID {
	GLuint textures[6];
	BYTE *pixels_top, *pixels_left, *pixels_front, *pixels_right, *pixels_back, *pixels_bottom;
	GLuint size;

	TexturesID() {
		glGenTextures(6, textures);
		
		for (int i = 0; i < 6; i++) {
			glBindTexture(GL_TEXTURE_2D, textures[i]);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
			glBindTexture(GL_TEXTURE_2D, 0);
		}
	}

	~TexturesID() {
		glDeleteTextures(1, textures);
	}

	void load(TextureData* data) {
		GLuint width = data->width / 4;
		GLuint height = data->height / 3;
		GLuint component = data->bpp / 8;
		size = width * height * component;

		pixels_top = new BYTE[size];
		pixels_left = new BYTE[size];
		pixels_front = new BYTE[size];
		pixels_right = new BYTE[size];
		pixels_back = new BYTE[size];
		pixels_bottom = new BYTE[size];
		for (int i = 0; i < width; i++) {
			memcpy(pixels_top + (i * width * component), data->pixels + width * component + (i * data->width * component), width * component);
			memcpy(pixels_left + (i * width * component), data->pixels + ((i + width) * data->width * component), width * component);
			memcpy(pixels_front + (i * width * component), data->pixels + width * component + ((i + width) * data->width * component), width * component);
			memcpy(pixels_right + (i * width * component), data->pixels + width * component * 2 + ((i + width) * data->width * component), width * component);
			memcpy(pixels_back + (i * width * component), data->pixels + width * component * 3 + ((i + width) * data->width * component), width * component);
			memcpy(pixels_bottom + (i * width * component), data->pixels + width * component + ((i + width * 2) * data->width * component), width * component);
		}

		switch (data->bpp) {
		case 24:
			glBindTexture(GL_TEXTURE_2D, textures[0]);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, pixels_top);
			glBindTexture(GL_TEXTURE_2D, textures[1]);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, pixels_left);
			glBindTexture(GL_TEXTURE_2D, textures[2]);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, pixels_front);
			glBindTexture(GL_TEXTURE_2D, textures[3]);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, pixels_right);
			glBindTexture(GL_TEXTURE_2D, textures[4]);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, pixels_back);
			glBindTexture(GL_TEXTURE_2D, textures[5]);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, pixels_bottom);
			break;
		case 32:
			glBindTexture(GL_TEXTURE_2D, textures[0]);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_BGRA, GL_UNSIGNED_BYTE, pixels_top);
			glBindTexture(GL_TEXTURE_2D, textures[1]);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_BGRA, GL_UNSIGNED_BYTE, pixels_left);
			glBindTexture(GL_TEXTURE_2D, textures[2]);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_BGRA, GL_UNSIGNED_BYTE, pixels_front);
			glBindTexture(GL_TEXTURE_2D, textures[3]);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_BGRA, GL_UNSIGNED_BYTE, pixels_right);
			glBindTexture(GL_TEXTURE_2D, textures[4]);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_BGRA, GL_UNSIGNED_BYTE, pixels_back);
			glBindTexture(GL_TEXTURE_2D, textures[5]);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_BGRA, GL_UNSIGNED_BYTE, pixels_bottom);
			break;
		}
	}
};

GLFWwindow* _window;
GLuint _shaderProgram, _fontTexture, _vao, _vbo, _ibo, _texAttribLocation, _projMtxAttribLocation, _positionAttribLocation, _uvAttribLocation, _colorAttribLocation;
bool _mousePress[3] = { false, false, false }, _keyboardPress[65536], _loaded = false, somethingTrue = true, _faces;
float _mouseWheel;
TextureData* _textureData = nullptr;
TexturesID* _textureIds = nullptr;

double _time;

std::string _consolebuffer;

#define WIDTH 1280
#define HEIGHT 720

void createWindow();
void initShaderBuffer();
void newFrame();

void openFile(const char* buffer);

void renderFunc(ImDrawData* draw_data);

std::vector<std::string> split(const std::string &s, char delim) {
	std::vector<std::string> strings;
	std::stringstream ss;
	ss.str(s);
	std::string item;
	while (std::getline(ss, item, delim)) {
		strings.push_back(item);
	}
	return strings;
}

void save(const char* filename) {
	_consolebuffer.append("Saving...");
	Database* database = new Database("skybox", VERSION_LATEST);
	Object* object = new Object("faces");
	Field *tWidthField = new Field("textureWidth", (int)_textureData->width / 4);
	Field *tHeightField = new Field("textureHeight", (int)_textureData->height / 3);
	Field *tBppField = new Field("textureBpp", (int)_textureData->bpp);

	Array *top = new Array("top", _textureIds->pixels_top, _textureIds->size);
	Array *left = new Array("left", _textureIds->pixels_left, _textureIds->size);
	Array *front = new Array("front", _textureIds->pixels_front, _textureIds->size);
	Array *right = new Array("right", _textureIds->pixels_right, _textureIds->size);
	Array *back = new Array("back", _textureIds->pixels_back, _textureIds->size);
	Array *bottom = new Array("bottom", _textureIds->pixels_bottom, _textureIds->size);

	object->addArray(top);
	object->addArray(left);
	object->addArray(front);
	object->addArray(right);
	object->addArray(back);
	object->addArray(bottom);

	object->addField(tWidthField);
	object->addField(tHeightField);
	object->addField(tBppField);

	database->addObject(object);
	Buffer buffer = Buffer(database->getSize());
	database->write(buffer);

	std::string path = filename;
	auto strings = split(path, '.');
	std::string outName;
	for (int i = 0; i < strings.size() - 1; i++)
		outName += strings[i];
	outName += ".htcubemap";

	buffer.writeFile(outName);
	delete database;
}

int main(int argc, char* argv[]) {
	createWindow();
	initShaderBuffer();
	glClearColor(.3f, .4f, .7f, 1.f);

	FreeImage_Initialise();

	char file_name[100];
	strcpy_s(file_name, "File name");
	_consolebuffer = "Initialized!\n";
	_consolebuffer.reserve(1024);
	while (!glfwWindowShouldClose(_window)) {
		glfwPollEvents();
		glClear(GL_COLOR_BUFFER_BIT);
	
		newFrame();
		
		Begin("main", &somethingTrue, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoSavedSettings);
		SetWindowFontScale(2.f);
		SetWindowPos("main", ImVec2(0, 0));
		int width, height;
		glfwGetWindowSize(_window, &width, &height);
		SetWindowSize("main", ImVec2(width, height));
		{
			
			Columns(2);
			Separator();

			Text("This is the Skybox Splitter tool!");
			Text(u8"Copyright © Ciorba Rares-Nicolaie 2017");
			Text(
				"How to use:\n"
				"Open the skybox file you want to choose.\n"
				"Mess around with the settings.\n",
				"Save it!\n"
				"And done!"
			);
			NextColumn();

			InputTextMultiline("", &_consolebuffer[0], 1024, ImVec2(700, 150), ImGuiInputTextFlags_ReadOnly);
			NextColumn();

			Columns(1);
			Separator();

			InputTextEx("##something", file_name, 100, ImVec2(625, 30), 0);
			SameLine();
			if (Button("Open", ImVec2(630, 30))) openFile(file_name);

		}
		//Settings tab:
		if (_loaded) {
			Columns(3);
			Separator();
			Text("Info:");
			Text("Image Size: %dx%d", _textureData->width, _textureData->height);
			Text("Image BPP: %d", _textureData->bpp);
			Text("Image Pitch: %d", _textureData->pitch);
			NextColumn();

			Text("Layout:");
			TextWrapped("Currently there's only one layout supported");
			Text("Hover over me");
			if (IsItemHovered()) {
				BeginTooltip();
				Text(" X   - top");
				Text("XXXX - left, front, right, back");
				Text(" X   - bottom");
				EndTooltip();
			}
			NextColumn();

			Text("Functions:");
			if (Button("Save")) save(file_name);
			if (Button("Show faces")) _faces ^= true;
			Columns(1);
			Separator();

			if (_faces) {
				Columns(6);

				Image((ImTextureID)_textureIds->textures[0], ImVec2(256, 256));
				NextColumn();

				Image((ImTextureID)_textureIds->textures[1], ImVec2(256, 256));
				NextColumn();

				Image((ImTextureID)_textureIds->textures[2], ImVec2(256, 256));
				NextColumn();

				Image((ImTextureID)_textureIds->textures[3], ImVec2(256, 256));
				NextColumn();

				Image((ImTextureID)_textureIds->textures[4], ImVec2(256, 256));
				NextColumn();

				Image((ImTextureID)_textureIds->textures[5], ImVec2(256, 256));
				NextColumn();

				Columns(1);
				Separator();
			}

		}

		End();

		Render();

		glfwSwapBuffers(_window);
	}
	FreeImage_DeInitialise();
	Shutdown();

	glDeleteProgram(_shaderProgram);
	glDeleteTextures(1, &_fontTexture);
	GetIO().Fonts->TexID = 0;

	glDeleteVertexArrays(1, &_vao);
	glDeleteBuffers(1, &_vbo);
	glDeleteBuffers(1, &_ibo);

	glfwDestroyWindow(_window);
}

void openFile(const char* file) {
	std::ifstream f(file);
	if (f.good()) {
		_consolebuffer.append("File exists!\n");
	}
	else {
		_consolebuffer.append("File does not exists!\n");
	}
	f.close();

	//Reading with FreeImage!
	FREE_IMAGE_FORMAT fif = FreeImage_GetFileType(file);
	FIBITMAP* dib = nullptr;

	if (fif == FIF_UNKNOWN)
		fif = FreeImage_GetFIFFromFilename(file);

	if (FreeImage_FIFSupportsReading(fif)) dib = FreeImage_Load(fif, file);
	else {
		_consolebuffer.append("Could not read file!");
		return;
	}
	FreeImage_FlipVertical(dib);
	if (_textureData)
		delete _textureData;

	_textureData = new TextureData();
	_textureData->width = FreeImage_GetWidth(dib);
	_textureData->height = FreeImage_GetHeight(dib);
	_textureData->bpp = FreeImage_GetBPP(dib);
	_textureData->pitch = FreeImage_GetPitch(dib);

	unsigned int size = _textureData->width * _textureData->height * (_textureData->bpp / 8);
	_textureData->pixels = new BYTE[size];
	BYTE* pixels = FreeImage_GetBits(dib);
	memcpy(_textureData->pixels, pixels, size);

	FreeImage_Unload(dib);
	_loaded = true;
	_consolebuffer.append("File loaded!\n");

	if (_textureIds)
		delete _textureIds;

	_textureIds = new TexturesID();
	_textureIds->load(_textureData);
}

void renderFunc(ImDrawData* draw_data) {
	auto& io = GetIO();
	int fb_width = (int)(io.DisplaySize.x * io.DisplayFramebufferScale.x);
	int fb_height = (int)(io.DisplaySize.y * io.DisplayFramebufferScale.y);
	if (fb_width == 0 || fb_height == 0)
		return;

	draw_data->ScaleClipRects(io.DisplayFramebufferScale);

	glEnable(GL_BLEND);
	glBlendEquation(GL_FUNC_ADD);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_CULL_FACE);
	glDisable(GL_DEPTH_TEST);
	glEnable(GL_SCISSOR_TEST);
	glActiveTexture(GL_TEXTURE0);

	glViewport(0, 0, fb_width, fb_height);

	const float ortho_projection[4][4] =
	{
		{ 2.0f / io.DisplaySize.x, 0.0f,                   0.0f, 0.0f },
		{ 0.0f,                  2.0f / -io.DisplaySize.y, 0.0f, 0.0f },
		{ 0.0f,                  0.0f,                  -1.0f, 0.0f },
		{ -1.0f,                  1.0f,                   0.0f, 1.0f },
	};
	glUseProgram(_shaderProgram);
	glUniform1i(_texAttribLocation, 0);
	glUniformMatrix4fv(_projMtxAttribLocation, 1, GL_FALSE, &ortho_projection[0][0]);
	glBindVertexArray(_vao);

	for (int i = 0; i < draw_data->CmdListsCount; i++) {
		const ImDrawList* cmd_list = draw_data->CmdLists[i];
		const ImDrawIdx* idx_buffer_offset = 0;

		glBindBuffer(GL_ARRAY_BUFFER, _vbo);
		glBufferData(GL_ARRAY_BUFFER, cmd_list->VtxBuffer.Size * sizeof(ImDrawVert), cmd_list->VtxBuffer.Data, GL_STREAM_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ibo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, cmd_list->IdxBuffer.Size * sizeof(ImDrawIdx), cmd_list->IdxBuffer.Data, GL_STREAM_DRAW);

		for (int j = 0; j < cmd_list->CmdBuffer.Size; j++) {
			const ImDrawCmd* pcmd = &cmd_list->CmdBuffer[j];

			if (pcmd->UserCallback)
				pcmd->UserCallback(cmd_list, pcmd);
			else {
				glBindTexture(GL_TEXTURE_2D, (GLuint)pcmd->TextureId);
				glScissor(pcmd->ClipRect.x, (int)(fb_height - pcmd->ClipRect.w), (int)(pcmd->ClipRect.z - pcmd->ClipRect.x), (int)(pcmd->ClipRect.w - pcmd->ClipRect.y));
				glDrawElements(GL_TRIANGLES, (GLsizei)pcmd->ElemCount, sizeof(ImDrawIdx) == 2 ? GL_UNSIGNED_SHORT : GL_UNSIGNED_INT, idx_buffer_offset);
			}
			idx_buffer_offset += pcmd->ElemCount;
		}
	}
}

void newFrame() {
	auto& io = GetIO();
	
	int w, h;
	int display_w, display_h;
	glfwGetWindowSize(_window, &w, &h);
	glfwGetFramebufferSize(_window, &display_w, &display_h);

	io.DisplaySize = ImVec2(w, h);
	io.DisplayFramebufferScale = ImVec2(w > 0 ? ((float)display_w / w) : 0, h > 0 ? ((float)display_h / h) : 0);

	double current_time = glfwGetTime();
	io.DeltaTime = _time > 0.0 ? (float)(current_time - _time) : (float)(1.f / 60.f);
	_time = current_time;

	if (glfwGetWindowAttrib(_window, GLFW_FOCUSED)) {
		double mx, my;
		glfwGetCursorPos(_window, &mx, &my);
		io.MousePos = ImVec2(mx, my);
	}
	else io.MousePos = ImVec2(-1, -1);

	for (int i = 0; i < 3; i++) {
		io.MouseDown[i] = _mousePress[i] || glfwGetMouseButton(_window, i) != 0;
		_mousePress[i] = false;
	}

	io.MouseWheel = _mouseWheel;
	_mouseWheel = 0.0f;

	glfwSetInputMode(_window, GLFW_CURSOR, io.MouseDrawCursor ? GLFW_CURSOR_HIDDEN : GLFW_CURSOR_NORMAL);

	NewFrame();
}

void initShaderBuffer() {
	_shaderProgram = glCreateProgram();
	GLuint vertexID = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragmentID = glCreateShader(GL_FRAGMENT_SHADER);

	const GLchar *vertex_shader =
		"#version 330\n"
		"uniform mat4 projectionMatrix;\n"
		"in vec2 position;\n"
		"in vec2 uv;\n"
		"in vec4 color;\n"
		"out vec2 out_uv;\n"
		"out vec4 out_color;\n"
		"void main()\n"
		"{\n"
		"	out_uv = uv;\n"
		"	out_color = color;\n"
		"	gl_Position = projectionMatrix * vec4(position.xy,0,1);\n"
		"}\n";

	const GLchar* fragment_shader =
		"#version 330\n"
		"uniform sampler2D tex;\n"
		"in vec2 out_uv;\n"
		"in vec4 out_color;\n"
		"out vec4 color;\n"
		"void main()\n"
		"{\n"
		"	color = out_color * texture( tex, out_uv.st);\n"
		"}\n";

	glShaderSource(vertexID, 1, &vertex_shader, 0);
	glShaderSource(fragmentID, 1, &fragment_shader, 0);
	glCompileShader(vertexID);
	glCompileShader(fragmentID);
	glAttachShader(_shaderProgram, vertexID);
	glAttachShader(_shaderProgram, fragmentID);
	glLinkProgram(_shaderProgram);
	glDeleteShader(vertexID);
	glDeleteShader(fragmentID);

	//Get locations
	_texAttribLocation = glGetUniformLocation(_shaderProgram, "tex");
	_projMtxAttribLocation = glGetUniformLocation(_shaderProgram, "projectionMatrix");
	_positionAttribLocation = glGetAttribLocation(_shaderProgram, "position");
	_uvAttribLocation = glGetAttribLocation(_shaderProgram, "uv");
	_colorAttribLocation = glGetAttribLocation(_shaderProgram, "color");

	//Initialize buffers + bind
	glGenVertexArrays(1, &_vao);
	glGenBuffers(1, &_vbo);
	glGenBuffers(1, &_ibo);
	glBindVertexArray(_vao);
	glBindBuffer(GL_ARRAY_BUFFER, _vbo);

	//enable vertex attrib arrays
	glEnableVertexAttribArray(_positionAttribLocation);
	glEnableVertexAttribArray(_uvAttribLocation);
	glEnableVertexAttribArray(_colorAttribLocation);

	//weird vertexattribpointer shit
#define OFFSETOF(TYPE, ELEMENT) ((size_t)&(((TYPE *)0)->ELEMENT))
	glVertexAttribPointer(_positionAttribLocation, 2, GL_FLOAT, GL_FALSE, sizeof(ImDrawVert), (GLvoid*)OFFSETOF(ImDrawVert, pos));
	glVertexAttribPointer(_uvAttribLocation, 2, GL_FLOAT, GL_FALSE, sizeof(ImDrawVert), (GLvoid*)OFFSETOF(ImDrawVert, uv));
	glVertexAttribPointer(_colorAttribLocation, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(ImDrawVert), (GLvoid*)OFFSETOF(ImDrawVert, col));
#undef OFFSETOF

	//this is where you should create the font texture

	using namespace ImGui;
	ImGuiIO& io = GetIO();
	unsigned char* pixels;
	int width, height;
	io.Fonts->GetTexDataAsRGBA32(&pixels, &width, &height);

	glGenTextures(1, &_fontTexture);
	glBindTexture(GL_TEXTURE_2D, _fontTexture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);

	io.Fonts->TexID = (void*)_fontTexture;

	//unbinding
	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
}

void createWindow() {
	if (!glfwInit())
		glfwTerminate();

	glfwWindowHint(GLFW_RESIZABLE, 0);

	_window = glfwCreateWindow(WIDTH, HEIGHT, "Skybox Splitter", NULL, NULL);
	glfwMakeContextCurrent(_window);
	//callbacks

	glfwSetWindowSizeCallback(_window, [](GLFWwindow *window, int width, int height) {
		glViewport(0, 0, width, height);
	});

	glfwSetMouseButtonCallback(_window, [](GLFWwindow*, int button, int action, int /*mods*/) {
		if (action == GLFW_PRESS && button >= 0 && button < 3)
			_mousePress[button] = true;
	});

	glfwSetKeyCallback(_window, [](GLFWwindow* window, int key, int, int action, int) {
		ImGuiIO& io = ImGui::GetIO();
		if (action == GLFW_PRESS)
			io.KeysDown[key] = true;
		if (action == GLFW_RELEASE)
			io.KeysDown[key] = false;
	
		io.KeyCtrl = io.KeysDown[GLFW_KEY_LEFT_CONTROL] || io.KeysDown[GLFW_KEY_RIGHT_CONTROL];
		io.KeyShift = io.KeysDown[GLFW_KEY_LEFT_SHIFT] || io.KeysDown[GLFW_KEY_RIGHT_SHIFT];
		io.KeyAlt = io.KeysDown[GLFW_KEY_LEFT_ALT] || io.KeysDown[GLFW_KEY_RIGHT_ALT];
		io.KeySuper = io.KeysDown[GLFW_KEY_LEFT_SUPER] || io.KeysDown[GLFW_KEY_RIGHT_SUPER];
	});
	
	glfwSetCharCallback(_window, [](GLFWwindow* window, unsigned int c) {
		ImGuiIO& io = GetIO();
		if (c > 0 && c < 0x10000)
			io.AddInputCharacter((unsigned short)c);
	});

	glfwSetScrollCallback(_window, [](GLFWwindow* window, double, double yoffset) {
		_mouseWheel += (float)yoffset;
	});

	glfwSwapInterval(0);

	if (glewInit() != GLEW_OK) {
		printf("Could not initalize GLEW!");
	}

	//ADD MORE SHIT BECAUSE THIS SHIT IS NOT ENOUGH WTF
	ImGuiIO& io = GetIO();
	io.KeyMap[ImGuiKey_Tab] = GLFW_KEY_TAB;
	io.KeyMap[ImGuiKey_LeftArrow] = GLFW_KEY_LEFT;
	io.KeyMap[ImGuiKey_RightArrow] = GLFW_KEY_RIGHT;
	io.KeyMap[ImGuiKey_UpArrow] = GLFW_KEY_UP;
	io.KeyMap[ImGuiKey_DownArrow] = GLFW_KEY_DOWN;
	io.KeyMap[ImGuiKey_PageUp] = GLFW_KEY_PAGE_UP;
	io.KeyMap[ImGuiKey_PageDown] = GLFW_KEY_PAGE_DOWN;
	io.KeyMap[ImGuiKey_Home] = GLFW_KEY_HOME;
	io.KeyMap[ImGuiKey_End] = GLFW_KEY_END;
	io.KeyMap[ImGuiKey_Delete] = GLFW_KEY_DELETE;
	io.KeyMap[ImGuiKey_Backspace] = GLFW_KEY_BACKSPACE;
	io.KeyMap[ImGuiKey_Enter] = GLFW_KEY_ENTER;
	io.KeyMap[ImGuiKey_Escape] = GLFW_KEY_ESCAPE;
	io.KeyMap[ImGuiKey_A] = GLFW_KEY_A;
	io.KeyMap[ImGuiKey_C] = GLFW_KEY_C;
	io.KeyMap[ImGuiKey_V] = GLFW_KEY_V;
	io.KeyMap[ImGuiKey_X] = GLFW_KEY_X;
	io.KeyMap[ImGuiKey_Y] = GLFW_KEY_Y;
	io.KeyMap[ImGuiKey_Z] = GLFW_KEY_Z;

	io.ClipboardUserData = _window;
	io.SetClipboardTextFn = [](void* user_data, const char* text) {
		glfwSetClipboardString((GLFWwindow*)user_data, text);
	};

	io.GetClipboardTextFn = [](void* user_data) {
		return glfwGetClipboardString((GLFWwindow*)user_data);
	};

	io.RenderDrawListsFn = renderFunc;

	io.IniFilename = NULL;
}
