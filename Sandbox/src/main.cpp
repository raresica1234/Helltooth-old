//#include "sandbox/sandbox.h"
#include "src/ht/tools/Serialization/Serialization.h"
//#include "src/ht/Helltooth.h"
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

	unsigned char* dest = htnew unsigned char[300];
	memset(dest, 0, 300);

	int* array_data = htnew int[4]{
		1,2,3,4
	};

	int value = 4;

	Array array = Array("test", array_data, 4);

	Field field = Field("test", value);

	Object object = Object("Test");

	//object.addField(field);
	object.addArray(array);

	object.writeBytes(dest, 0);

	for (int i = 0; i < 300; i++) {
		printf("0x%x ", dest[i]);
	}

	printf("\n\n");
	//Array field2 = Array::readBytes(dest, 0);


	//int* data = field2.getArray<int>();

	//for (int i = 0; i < 4; i++) {
	//printf("0x%x ", data[i]);
	//}

	//delete object;

	system("PAUSE");
}