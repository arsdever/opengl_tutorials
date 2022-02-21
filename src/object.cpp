#include "object.hpp"

#include <helper.h>
#include <components/component.hpp>

namespace gl
{
	object::object()
		: _uid(utils::generate_uid())
	{}

	object::~object()
	{
		for (auto c : _children)
		{
			c->make_child_of(parent());
		}
	}

	void object::make_parent_of(object_ptr child)
	{
		child->make_child_of(weak_from_this());
		_children.push_back(child);
	}

	void object::make_child_of(object_wptr parent)
	{
		if (_is_parenting)
		{
			return;
		}

		_is_parenting = true;
		if (object_ptr p = _parent.lock())
		{
			p->remove_child(shared_from_this());
		}

		_parent = parent;
		if (object_ptr p = _parent.lock())
		{
			p->make_parent_of(shared_from_this());
		}
		_is_parenting = false;
	}

	void object::remove_child(object_ptr child)
	{
		_children.remove(child);
	}

	void object::start()
	{
		for (auto c : _components)
		{
			c->start();
		}
	}

	void object::update()
	{
		for (auto c : _components)
		{
			c->update();
		}
	}

	object_wptr object::parent()
	{
		return _parent;
	}
}