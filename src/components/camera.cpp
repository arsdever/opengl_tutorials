#include <object.hpp>
#include <profiler.hpp>
#include <scene.hpp>

#include "camera.hpp"

#include <components/renderer.hpp>
#include <components/transform.hpp>
#include <glad/glad.h>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace gl
{
    camera::camera()
        : _viewport(0, 0, 0, 0)
    {
    }

    void camera::set_main()
    {
        scene::current_scene()->set_main_camera(static_pointer_cast<camera>(shared_from_this()));
    }

    void camera::set_viewport(rect viewport) { _viewport = viewport; }

    camera::rect camera::viewport() const { return _viewport; }

    void camera::update() { render(); }

    glm::mat4 camera::get_perspective() const
    {
        auto scoped_profiler_instance =
            prof::profiler::profile(std::string { "camera::" } + object().lock()->id() + "::" + __func__);
        return glm::perspective<double>(120.0, _viewport.w / _viewport.h, 0.001f, 300.0);
    }

    glm::mat4 camera::get_matrix() const
    {
        auto scoped_profiler_instance =
            prof::profiler::profile(std::string { "camera::" } + object().lock()->id() + "::" + __func__);
        std::shared_ptr<transform> t = get_component<transform>();

        return get_perspective() * glm::lookAt(t->position(),
                                               t->position() + t->rotation() * glm::vec3 { 0, 0, -1 },
                                               glm::vec3 { 0, 1, 0 });
    }

    void camera::render()
    {
        auto scoped_profiler_instance =
            prof::profiler::profile(std::string { "camera::" } + object().lock()->id() + "::" + __func__);
        glViewport(_viewport.x, _viewport.y, _viewport.w, _viewport.h);
        glClearColor(0.f, 0.f, 0.f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glMatrixMode(GL_PROJECTION);
        glLoadMatrixf(glm::value_ptr(get_perspective()));

        glDepthFunc(GL_LESS);
        glEnable(GL_DEPTH_TEST);

        for (auto obj : *scene::current_scene())
            {
                std::shared_ptr<renderer> r = obj->get_component<renderer>();
                if (!r)
                    continue;

                r->render(std::static_pointer_cast<camera>(shared_from_this()));
            }
    }
} // namespace gl