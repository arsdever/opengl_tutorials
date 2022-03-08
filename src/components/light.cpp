#include "light.hpp"

namespace gl
{
    glm::vec4 light::color() const { return _color; }

    float light::intencity() const { return _intencity; }

    void light::set_color(glm::vec4 const& v) { _color = v; }

    void light::set_intencity(float v) { _intencity = v; }
} // namespace gl