#pragma once

#include <components/component.hpp>
#include <glm/ext.hpp>

namespace gl
{
    class transform : public component
    {
    public:
        transform();

        void set_position(glm::vec3 position);
        void set_rotation(glm::quat rotation);
        void set_scale(glm::vec3 scale);

        void move(glm::vec3 movement);
        void rotate(glm::quat rotation);
        void resize(glm::vec3 scale);

        glm::vec3 position() const;
        glm::quat rotation() const;
        glm::vec3 scale() const;

        glm::vec3 forward() const;
        glm::vec3 right() const;
        glm::vec3 up() const;

        glm::mat4 get_matrix() const;

    private:
        glm::vec3 _position;
        glm::quat _rotation;
        glm::vec3 _scale;
    };
} // namespace gl