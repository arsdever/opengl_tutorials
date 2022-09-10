#pragma once

#include <shader_prog.h>
#include <vector>

#include <components/component.hpp>
#include <components/vertex/vertex.hpp>

namespace gl
{
    class mesh : public component
    {
    public:
        mesh(object_wptr o);

        virtual std::vector<vertex>&       vertices();
        virtual std::vector<unsigned int>& indices();

        virtual const std::vector<vertex>&       vertices() const;
        virtual const std::vector<unsigned int>& indices() const;

        bool is_dirty() const;
        void upload_data() const;
        unsigned int buffer_array() const;

    protected:
        std::vector<vertex>       _vertices;
        std::vector<unsigned int> _indices;
        mutable bool              _is_dirty { true };
        unsigned int              _vao { 0 };
        unsigned int              _vbo { 0 };
        unsigned int              _ebo { 0 };
    };
} // namespace gl