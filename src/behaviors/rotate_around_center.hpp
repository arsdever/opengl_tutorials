#pragma once

#include <components/component.hpp>

namespace gl
{
    class rotate_around_center : public component
    {
    public:
        rotate_around_center(object_wptr o);
        void update() override;
        void set_speed(float v);

    private:
        float _speed { 1.0f };
    };
} // namespace gl