#pragma once

#include <prototypes.hpp>

#include <object.hpp>

namespace gl
{
    class component : public std::enable_shared_from_this<component>
    {
    public:
        component();
        virtual ~component() = default;

        void        set_object(object_wptr obj);
        object_wptr object() const;

        virtual void start();
        virtual void update();

        template <typename component_t>
        typename std::enable_if<std::is_base_of<component, component_t>::value, std::shared_ptr<component_t>>::type
        get_component() const
        {
            if (auto o = _object.lock())
                {
                    auto c = o->get_component<component_t>();
                    if (c)
                        return c;
                }

            return nullptr;
        }

        virtual void draw_helpers();

    private:
        object_wptr _object;
    };
} // namespace gl