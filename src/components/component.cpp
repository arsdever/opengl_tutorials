#include "component.hpp"

namespace gl
{
    component::component(object_wptr obj)
        : _object { obj }
    {
    }

    void component::start() { }

    void component::update() { }

    void component::set_object(object_wptr obj) { _object = obj; }

    object_wptr component::object() const { return _object; }

    void component::draw_helpers() { }
} // namespace gl