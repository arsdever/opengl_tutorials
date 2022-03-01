#pragma once

#include <components/component.hpp>
#include <glm/ext.hpp>

namespace gl
{
    class camera : public component
    {
    public:
        struct rect
        {
            rect(float _x, float _y, float _w, float _h)
                : x { _x }
                , y { _y }
                , w { _w }
                , h { _h }
            {
            }

            rect(const rect& o)
                : rect(o.x, o.y, o.w, o.h)
            {
            }

            float x { 0 };
            float y { 0 };
            float w { 0 };
            float h { 0 };
        };

    public:
        camera();

        virtual void update() override;

        void set_main();

        void set_viewport(rect viewport);
        rect viewport() const;

        glm::mat4 get_matrix() const;
        glm::mat4 get_perspective() const;

        void render();

    private:
        rect _viewport;
    };
} // namespace gl