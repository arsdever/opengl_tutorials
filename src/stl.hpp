#pragma once

#include <string_view>

namespace gl
{
    struct stl
    {
        struct triangle;
        struct triangle_iterator;

        stl(const void* data);

        std::string_view header() const;

        uint32_t number_of_triangles() const;

        triangle_iterator begin() const;
        triangle_iterator end() const;

#pragma pack(push, 1)
        struct triangle
        {
            float    normal[ 3 ];
            float    v1[ 3 ];
            float    v2[ 3 ];
            float    v3[ 3 ];
            uint16_t attribute_byte_count;
        };
#pragma pack(pop)

        struct triangle_iterator
        {
            using iterator_category = std::input_iterator_tag;
            using difference_type   = std::ptrdiff_t;
            using value_type        = triangle;
            using reference         = triangle const&;
            using pointer           = triangle const*;

            triangle_iterator(const void* ptr)
                : _ptr { ptr }
            {
            }

            reference operator*() const { return *reinterpret_cast<triangle const*>(_ptr); }
            pointer   operator->() const { return reinterpret_cast<triangle const*>(_ptr); }

            triangle_iterator& operator++()
            {
                _ptr = reinterpret_cast<triangle const*>(_ptr) + 1;
                return *this;
            }
            triangle_iterator operator++(int)
            {
                triangle_iterator tmp = *this;
                ++(*this);
                return tmp;
            }

            bool operator==(triangle_iterator const& o) { return _ptr == o._ptr; }
            bool operator!=(triangle_iterator const& o) { return _ptr != o._ptr; }

        private:
            const void* _ptr;
        };

    private:
        const void* _data;
    };

    stl::stl(const void* data)
        : _data(data)
    {
    }

    std::string_view stl::header() const { return std::string_view { static_cast<const char*>(_data), 80 }; }

    uint32_t stl::number_of_triangles() const
    {
        return *reinterpret_cast<const uint32_t*>(reinterpret_cast<const char*>(_data) + 80);
    }

    stl::triangle_iterator stl::begin() const { return { static_cast<const uint8_t*>(_data) + 84 }; }

    stl::triangle_iterator stl::end() const
    {
        return { static_cast<const uint8_t*>(_data) + 84 + number_of_triangles() * sizeof(triangle) };
    }
} // namespace gl