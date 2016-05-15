#include "sandbox/sandbox.h"

using namespace sandbox;

void main()
{
	Sandbox* sandbox = new Sandbox();
	sandbox->start();

	delete sandbox;

	system("PAUSE");
}