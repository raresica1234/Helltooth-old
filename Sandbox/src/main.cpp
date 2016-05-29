#include "sandbox/sandbox.h"

using namespace sandbox;

void main()
{
	Sandbox* sandbox = htnew Sandbox();
	sandbox->start();

	delete sandbox;

	/*ht::assets::HelltoothTexture::openTexture("res/texture.httexture");

	void* data = malloc(22);
	char* temp = (char*)data;
	temp = "#w ";
	temp += 4;
	memcpy(data, temp, 22);

	int* temp2 = (int*)data;
	*temp2 = 1024;
	memcpy(data, temp2, 22);

	ht::utils::FileUtils::write_file("res/texture.httexture", data, 22);
	
	delete[] data;
	delete[] temp;*/
	system("PAUSE");
}