#include <timer.hpp>

#include "rotate_around_center.hpp"

#include <components/transform.hpp>

namespace gl
{
    void rotate_around_center::set_speed(float v) { _speed = v; }

    void rotate_around_center::update()
    {
        get_component<transform>()->set_position(
            { std::sin(timer::now() * _speed), 0.0f, std::cos(timer::now() * _speed) });
    }
} // namespace gl