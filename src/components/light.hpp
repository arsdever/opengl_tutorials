#pragma once

#include <components/component.hpp>
#include <glm/ext.hpp>

namespace gl
{
    class light : public component
    {
    public:
        light(object_wptr o);
        glm::vec4 color() const;
        float     intencity() const;

        void set_color(glm::vec4 const& v);
        void set_intencity(float v);

    protected:
        float     _intencity;
        glm::vec4 _color;
    };
} // namespace gl