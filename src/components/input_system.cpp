#include <algorithm>
#include <iostream>
#include <profiler.hpp>
#include <scene.hpp>

#include "input_system.hpp"

#include <GLFW/glfw3.h>

namespace gl
{
    void input_system::set_window(GLFWwindow* wind) { _window = wind; }

    void input_system::start() { }

    void input_system::update()
    {
        auto scoped_profiler_instance =
            prof::profiler::profile(std::string { "input_system::" } + object().lock()->id() + "::" + __func__);
        for (auto action : _mapping)
            {
                if (action_ctx context = check_action(action.first))
                    action.second(context);
            }
    }

    action_ctx input_system::check_action(std::string action)
    {
        auto scoped_profiler_instance =
            prof::profiler::profile(std::string { "input_system::" } + object().lock()->id() + "::" + __func__);
        std::for_each(action.begin(), action.end(), [](auto& ch) { ch = tolower(ch); });
        auto        sep_pos  = action.find_first_of(":");
        std::string device   = action.substr(0, sep_pos);
        std::string variable = action.substr(sep_pos + 1);

        if (device == "mouse") // Mouse action
            {
                if (variable == "position")
                    {
                        double x, y;
                        glfwGetCursorPos(_window, &x, &y);
                        return action_ctx { true, glm::vec2 { x, y } };
                    }
                if (variable == "left_release")
                    {
                        int state = glfwGetMouseButton(_window, GLFW_MOUSE_BUTTON_LEFT);
                        if (state == GLFW_RELEASE && _was_clicked)
                            {
                                _was_clicked = false;
                                double x, y;
                                glfwGetCursorPos(_window, &x, &y);
                                return action_ctx { true, glm::vec2 { x, y } };
                            }
                    }
                if (variable == "left_click")
                    {
                        int state = glfwGetMouseButton(_window, GLFW_MOUSE_BUTTON_LEFT);
                        if (state == GLFW_PRESS && !_was_clicked)
                            {
                                _was_clicked = true;
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
        auto scoped_profiler_instance =
            prof::profiler::profile(std::string { "input_system::" } + object().lock()->id() + "::" + __func__);
        _mapping.insert({ action, cb });
    }
} // namespace gl