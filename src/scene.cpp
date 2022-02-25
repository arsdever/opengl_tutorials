#include "scene.hpp"

namespace gl
{
	scene_ptr scene::_current_scene = nullptr;

	void scene::add_object(object_ptr obj) { _objects.push_back(obj); }

	void scene::load() { _current_scene = shared_from_this(); }

	camera_ptr scene::main_camera() const { return _main_camera; }

	void scene::set_main_camera(camera_ptr cam) { _main_camera = cam; }

	scene_ptr scene::current_scene() { return _current_scene; }

	std::list<object_ptr>::iterator scene::begin() { return _objects.begin(); }

	std::list<object_ptr>::iterator scene::end() { return _objects.end(); }
} // namespace gl