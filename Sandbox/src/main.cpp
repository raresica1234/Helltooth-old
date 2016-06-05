//#include "sandbox/sandbox.h"
#include "src/ht/tools/Serialization/src/Writer.h"
//using namespace sandbox;

#include <iostream>
#include <string>

void main()
{
	//Sandbox* sandbox = htnew Sandbox();
	//sandbox->start();

	//delete sandbox;

	using namespace ht;
	using namespace tools;
	using namespace serialization;

	byte* data = new byte[16]{
		0x0, 0x4, 0x73, 0x68, 0x69, 0x74, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0
	};


	short value = SerializationWriter::readBytes<short>(data, 0);
	std::string value1 = SerializationWriter::readBytes<std::string>(data, 0);
	/*std::string shit = "shit";
	int pointer = 0;
	//pointer = SerializationWriter::writeBytes(data, pointer, value);
	pointer = SerializationWriter::writeBytes(data, pointer, shit);

	for (int i = 0; i < 2; i++)
		printf("0x%x ", data[i]);

	for (int i = 2; i < 16; i++)
		printf("0x%x ", data[i]);

	printf("\n");*/
	printf("Value (short): %i \n", value);
	std::cout << value1 << std::endl;
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