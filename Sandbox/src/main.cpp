#include "sandbox/sandbox.h"
using namespace sandbox;

void main() {
	Sandbox* sandbox = htnew Sandbox();

	del sandbox;
}