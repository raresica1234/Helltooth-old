#pragma once

#include <iostream>
#include "Helltooth.h"

namespace sandbox{
	class Sandbox {

	private:
		int m_width = 1024;
		int m_height = 768;
		char *m_Title = "First window!";
		ht::graphics::Window* m_Window;
	public:
		Sandbox();
		~Sandbox();
		void update() const;
	};
};
