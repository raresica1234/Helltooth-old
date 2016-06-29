//#include "sandbox/sandbox.h"
#include <Windows.h>
#include "src/ht/Helltooth.h"
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
	

	serialization::byte* dest = htnew serialization::byte[300];
	unsigned char* dest = htnew unsigned char[300];
	memset(dest, 0, 300);

	int* array_data = htnew int[4]{
		1,2,3,4
	};

	int value = 4;

	const serialization::Array* array = new serialization::Array("test", array_data, 4);

	const serialization::Field* field = new serialization::Field("test", value);

	serialization::Object* object = new serialization::Object("Test");

	serialization::Database* db = new serialization::Database("Test");

	object->addField(field);
	object->addArray(array);

	//db->addObject(*object);
	//db->findObject("Test").addField(field);
	//db->findObject("Test").addArray(array);



	object->writeBytes(dest, 0);

	for (int i = 0; i < 300; i++) {
		printf("0x%x ", dest[i]);
	}

	printf("\n\n");
	//Array field2 = Array::readBytes(dest, 0);

	delete[] dest;
	delete array;
	delete field;
	delete object;
	delete db;

	//int* data = field2.getArray<int>();

	//for (int i = 0; i < 4; i++) {
	//printf("0x%x ", data[i]);
	//}

	//delete object;

	system("PAUSE");
}