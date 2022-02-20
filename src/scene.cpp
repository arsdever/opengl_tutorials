#include "scene.hpp"

namespace gl
{
	scene_ptr scene::_current_scene = nullptr;

	void scene::add_object(object_ptr obj)
	{
		_objects.push_back(obj);
	}

	void scene::load()
	{
		_current_scene = shared_from_this();
	}

	scene_ptr scene::current_scene()
	{
		return _current_scene;
	}

	std::list<object_ptr>::iterator scene::begin()
	{
		return _objects.begin();
	}

	std::list<object_ptr>::iterator scene::end()
	{
		return _objects.end();
	}
}