#include "input_system.hpp"

#include <GLFW/glfw3.h>
#include <algorithm>
#include <iostream>
#include <scene.hpp>

namespace gl
{
	void input_system::set_window(GLFWwindow* wind) { _window = wind; }

	void input_system::start() { }

	void input_system::update()
	{
		for (auto action : _mapping)
			{
				if (action_ctx context = check_action(action.first))
					action.second(context);
			}
	}

	action_ctx input_system::check_action(std::string action)
	{
		std::for_each(action.begin(), action.end(), [](auto& ch) { ch = tolower(ch); });
		auto		sep_pos	 = action.find_first_of(":");
		std::string device	 = action.substr(0, sep_pos);
		std::string variable = action.substr(sep_pos + 1);

		if (device == "mouse") // Mouse action
			{
				if (variable == "position")
					{
						double x, y;
						glfwGetCursorPos(_window, &x, &y);
						return action_ctx { true, glm::vec2 { x, y } };
					}
				if (variable == "left_click")
					{
						int state = glfwGetMouseButton(_window, GLFW_MOUSE_BUTTON_LEFT);
						if (state == GLFW_PRESS)
							{
								double x, y;
								glfwGetCursorPos(_window, &x, &y);
								return action_ctx { true, glm::vec2 { x, y } };
							}
					}
				if (variable == "right_click")
					{
						int state = glfwGetMouseButton(_window, GLFW_MOUSE_BUTTON_RIGHT);
						if (state == GLFW_PRESS)
							{
								double x, y;
								glfwGetCursorPos(_window, &x, &y);
								return action_ctx { true, glm::vec2 { x, y } };
							}
					}
			}
		else if (device == "keyboard")
			{
				if (glfwGetKey(_window, std::toupper(variable[ 0 ])) == GLFW_PRESS)
					{
						return action_ctx { true, 1 };
					}
			}

		return action_ctx { false, {} };
	}

	void input_system::on_action(const std::string& action, std::function<void(const action_ctx&)> cb)
	{
		_mapping.insert({ action, cb });
	}
} // namespace gl