#pragma once

#include <list>

#include <prototypes.hpp>

namespace gl
{
	class scene
		: public std::enable_shared_from_this<scene>
	{
	public:
		void add_object(object_ptr obj);

		//void remove_object(object_ptr obj);

		void load();

		static scene_ptr current_scene();

		std::list<object_ptr>::iterator begin();

		std::list<object_ptr>::iterator end();

	private:
		std::list<object_ptr> _objects;
		static scene_ptr _current_scene;
	};
}