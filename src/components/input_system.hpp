#pragma once

#include <action_ctx.hpp>
#include <functional>
#include <unordered_map>

#include <components/component.hpp>
#include <glm/ext.hpp>

struct GLFWwindow;

namespace gl
{
    class input_system : public component
    {
    public:
        void set_window(GLFWwindow* wind);

        virtual void start();
        virtual void update();

        action_ctx check_action(std::string action);
        void       on_action(const std::string& action, std::function<void(const action_ctx&)> cb);

    private:
        std::unordered_map<std::string, std::function<void(const action_ctx&)>> _mapping;
        glm::vec<2, double>                                                     _mouse_coordinates;
        GLFWwindow*                                                             _window;
    };
} // namespace gl