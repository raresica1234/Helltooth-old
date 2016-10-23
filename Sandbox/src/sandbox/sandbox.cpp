#include "sandbox.h"

using namespace sandbox;

Sandbox::Sandbox()
	: Application("Sandbox", WIDTH, HEIGHT) {
	glClearColor(0.3f, 0.4f, 0.7f, 1.0f);

	API::API(TYPE, MODE);

	VFS::mount("shaders", "src/shaders");
	VFS::mount("res", "res/");
	VFS::mount("res", "res/unused/");

	Camera* camera = htnew Camera(window);
	layer = htnew Layer(API::createShader("/shaders/shader.vert", "/shaders/shader.frag"), camera);
	guis = htnew Layer(API::createShader("/shaders/quad.vert", "/shaders/quad.frag"));

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	fbo = htnew FBO(WIDTH, HEIGHT);
	fbo->createColorTexture();
	fbo->createDepthTexture(false);

	guis->setMatrix(mat4::createOrthographic(-9.0f, 9.0f, 16.0f, -16.0f, -1.0f, 1.0f));
	layer->setMatrix(mat4::createPerspective(70, 0.1f, 1000.0f, WIDTH / HEIGHT));

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); 
	Renderable* guiRenderable = htnew Renderable();

	quad = htnew Quad();
	guiRenderable->loadRawModel(quad->getModel());
	guiRenderable->addTexture(fbo->getColorTexture());
	sentity = htnew StaticEntity(guiRenderable, 5.0f, -12.0f, 1.0f);
	sentity->scale(3, 3, 3);

	Renderable* model = htnew Renderable();
	model->loadRawModel(API::loadObjFile("/res/stall.obj"));

	model->addTexture(API::loadTextureFromFile("/res/stallTexture.png"));
	model->addTexture(API::loadTextureFromFile("/res/stallTextureSpecular.png"));

	terrain = htnew Terrain(vec2(1, 1));
	layer->submit(terrain);
	guis->submit(sentity);

	dentity = htnew DynamicEntity(model, vec3(0.0f, -1.0f, -55.0f));
	dentity->rotate(vec3(0, 180, 0));

	Application::start();
}

void Sandbox::init(){
	dentity->scale(vec3(1, 1, 1));

	Application::init();
}

void Sandbox::update() {
	layer->update();
	guis->update();

	if (Input::getKey(GLFW_KEY_R))
		compile = true;
}

void Sandbox::render() {
	layer->submit(dentity);

	fbo->bind();
	layer->render();
	fbo->unbind(window->getWidth(), window->getHeight());

	layer->render();
	guis->render();

	layer->cleanUP();
	guis->cleanUP();
}

void Sandbox::tick() {
	if (compile) {
		ShaderManager::reCompile();
		layer->reloadTextures();
		guis->reloadTextures();
		compile = false;
	}
}

Sandbox::~Sandbox()  {
	layer->forceCleanUP();
	guis->forceCleanUP();

	del terrain;

	del guis;
	del layer;

	del dentity;
	del sentity;

	del quad;
}