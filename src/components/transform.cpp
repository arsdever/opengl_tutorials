#include <profiler.hpp>

#include "transform.hpp"

namespace gl
{
    transform::transform()
        : _position {}
        , _rotation {}
        , _scale { 1 }
    {
    }

    void transform::set_position(glm::vec3 position) { _position = position; }

    void transform::set_rotation(glm::quat rotation) { _rotation = rotation; }

    void transform::set_scale(glm::vec3 scale) { _scale = scale; }

    void transform::move(glm::vec3 movement)
    {
        auto scoped_profiler_instance = prof::profiler::profile(object().lock()->id() + "::" + __func__);
        _position += movement;
    }

    void transform::rotate(glm::quat rotation)
    {
        auto scoped_profiler_instance = prof::profiler::profile(object().lock()->id() + "::" + __func__);
        _rotation += rotation;
    }

    void transform::resize(glm::vec3 scale)
    {
        auto scoped_profiler_instance = prof::profiler::profile(object().lock()->id() + "::" + __func__);
        _scale += scale;
    }

    glm::mat4 transform::get_matrix() const
    {
        auto      p = prof::profiler::profile(object().lock()->id() + "::" + __func__);
        glm::mat4 t { 1 };
        t           = glm::translate(t, _position);
        glm::mat4 r = glm::mat4_cast(_rotation);
        t           = t * t;
        t           = glm::scale(t, _scale);
        return t;
    }

    glm::vec3 transform::position() const { return _position; }

    glm::quat transform::rotation() const { return _rotation; }

    glm::vec3 transform::scale() const { return _scale; }

    glm::vec3 transform::forward() const
    {
        auto scoped_profiler_instance = prof::profiler::profile(object().lock()->id() + "::" + __func__);
        return _rotation * glm::vec3 { 0, 0, -1 };
    }

    glm::vec3 transform::right() const
    {
        auto scoped_profiler_instance = prof::profiler::profile(object().lock()->id() + "::" + __func__);
        return glm::cross(forward(), glm::vec3 { 0, 1, 0 });
    }

    glm::vec3 transform::up() const
    {
        auto scoped_profiler_instance = prof::profiler::profile(object().lock()->id() + "::" + __func__);
        return glm::cross(right(), forward());
    }
} // namespace gl