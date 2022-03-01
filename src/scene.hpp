#pragma once

#include <prototypes.hpp>

#include <list>

namespace gl
{
    class scene : public std::enable_shared_from_this<scene>
    {
    public:
        void add_object(object_ptr obj);

        // void remove_object(object_ptr obj);

        void load();

        camera_ptr main_camera() const;
        void       set_main_camera(camera_ptr cam);

        static scene_ptr current_scene();

        std::list<object_ptr>::iterator begin();

        std::list<object_ptr>::iterator end();

    private:
        std::list<object_ptr> _objects;
        camera_ptr            _main_camera;
        static scene_ptr      _current_scene;
    };
} // namespace gl