#pragma once

#include <iostream>
#include <src/Helltooth.h>

namespace sandbox{
	class Sandbox {

	private:
		ht::graphics::Window* m_Window;
	public:
		Sandbox();
		~Sandbox();
		void update() const;
	};
};
