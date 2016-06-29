#include "sandbox/sandbox.h"
using namespace sandbox;

#include <iostream>
#include <string>

void main() {

	Sandbox* sandbox = htnew Sandbox();
	sandbox->start();

	delete sandbox;
	system("PAUSE");
}