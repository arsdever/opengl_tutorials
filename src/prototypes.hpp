#pragma once

#include <memory>

#define CLASS(clazz)                                                                                                   \
    class clazz;                                                                                                       \
    using clazz##_ptr  = std::shared_ptr<clazz>;                                                                       \
    using clazz##_wptr = std::weak_ptr<clazz>;                                                                         \
    using clazz##_uptr = std::unique_ptr<clazz>;

namespace gl
{
    CLASS(object);
    CLASS(component);
    CLASS(scene);
    CLASS(camera);
    CLASS(transform);
} // namespace gl