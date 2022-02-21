#include "timer.hpp"

#include <GLFW/glfw3.h>

namespace gl
{
	float timer::_last{};

	float timer::now()
	{
		return glfwGetTime();
	}

	void timer::update()
	{
		_last = now();
	}

	float timer::delta()
	{
		return now() - _last;
	}
}