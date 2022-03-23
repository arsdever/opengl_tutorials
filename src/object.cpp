#include <helper.h>
#include <profiler.hpp>

#include "object.hpp"

#include <components/component.hpp>

namespace gl
{
    object::object()
        : _uid(utils::generate_uid())
    {
        auto scoped_profiler_instance = prof::profiler::profile(id() + "::" + __func__);
    }

    object::~object()
    {
        for (auto c : _children)
            {
                c->make_child_of(parent());
            }
    }

    void object::make_parent_of(object_ptr child)
    {
        auto scoped_profiler_instance = prof::profiler::profile(id() + "::" + __func__);
        child->make_child_of(weak_from_this());
        _children.push_back(child);
    }

    void object::make_child_of(object_wptr parent)
    {
        auto scoped_profiler_instance = prof::profiler::profile(id() + "::" + __func__);
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
        auto scoped_profiler_instance = prof::profiler::profile(id() + "::" + __func__);
        _children.remove(child);
    }

    void object::start()
    {
        auto scoped_profiler_instance = prof::profiler::profile(id() + "::" + __func__);
        for (auto c : _components)
            {
                c->start();
            }
    }

    void object::update()
    {
        auto scoped_profiler_instance = prof::profiler::profile(id() + "::" + __func__);
        for (auto c : _components)
            {
                c->update();
            }
    }

    object::uid_t object::id() const { return _uid; }

    object_wptr object::parent() { return _parent; }
} // namespace gl