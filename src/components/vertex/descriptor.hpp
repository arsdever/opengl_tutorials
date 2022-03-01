#pragma once

#include <tuple>

namespace gl::vertex_attributes
{
    using descriptor_t = std::tuple<unsigned, int, bool, unsigned>;
    namespace descriptor
    {
        static constexpr int count  = 0;
        static constexpr int gltype = 1;
        static constexpr int glnorm = 2;
        static constexpr int size   = 3;
    } // namespace descriptor
} // namespace gl::vertex_attributes