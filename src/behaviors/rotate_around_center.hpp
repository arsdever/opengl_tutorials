#pragma once

#include <components/component.hpp>

namespace gl
{
    class rotate_around_center : public component
    {
    public:
        void update() override;
        void set_speed(float v);

    private:
        float _speed;
    };
} // namespace gl