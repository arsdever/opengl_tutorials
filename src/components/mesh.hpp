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

    protected:
        std::vector<vertex>       _vertices;
        std::vector<unsigned int> _indices;
    };
} // namespace gl