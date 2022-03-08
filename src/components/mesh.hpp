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
        mesh();

        virtual std::vector<vertex>&       vertices();
        virtual std::vector<unsigned int>& indices();

        virtual const std::vector<vertex>&       vertices() const;
        virtual const std::vector<unsigned int>& indices() const;

        bool is_dirty() const;
        void upload_data() const;

    protected:
        std::vector<vertex>       _vertices;
        std::vector<unsigned int> _indices;
        mutable bool              _is_dirty { true };
    };
} // namespace gl