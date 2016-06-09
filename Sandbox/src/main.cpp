//#include "sandbox/sandbox.h"
#include "src/ht/tools/Serialization/Serialization.h"
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

	

	byte* dest = new byte[100];
	memset(dest, 0, 100);

	int* array_data = new int[4]{
		1,2,3,4
	};
	
	Array array = Array("test", array_data, 4);

	array.writeBytes(dest, 0);

	for (int i = 0; i < 100; i++) {
		printf("0x%x ", dest[i]);
	}
	printf("\n\n");
	Array array2 = Array::readBytes(dest, 0);


	int* data = array2.getArray<int>();

	for (int i = 0; i < 4; i++) {
		printf("0x%x ", data[i]);
	}

	system("PAUSE");
}