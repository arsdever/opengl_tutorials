#pragma once

#include <prototypes.hpp>

#include <list>
#include <string>

namespace gl
{
	/// <summary>
	/// Represents any object in the scene
	/// </summary>
	class object : public std::enable_shared_from_this<object>
	{
	public:
		using uid_t = std::string;

	public:
		object();
		virtual ~object();

		void make_parent_of(object_ptr child);
		void make_child_of(object_wptr parent);
		void remove_child(object_ptr child);

		template <typename component_t>
		std::enable_if<std::is_base_of<component, component_t>::value, std::shared_ptr<component_t>>::type
		add_component()
		{
			if (get_component<component_t>())
				{
					// Cannot have 2 components of the same type;
					return nullptr;
				}

			std::shared_ptr<component_t> c = std::make_shared<component_t>();
			c->set_object(shared_from_this());
			_components.push_back(c);
			return c;
		}

		template <typename component_t>
		std::enable_if<std::is_base_of<component, component_t>::value, std::shared_ptr<component_t>>::type
		get_component()
		{
			for (auto c : _components)
				{
					if (auto cmp = std::dynamic_pointer_cast<component_t>(c))
						return cmp;
				}

			return nullptr;
		}

		void		start();
		void		update();
		object_wptr parent();

#pragma region Lifecycle functions
		/*
		protected:
			virtual void on_awake();
			virtual void on_enable();

			virtual void on_start_first();
			virtual void on_start();
			virtual void on_start_last();

			virtual void on_update_first();
			virtual void on_update();
			virtual void on_update_last();

			virtual void on_disable();
			virtual void on_destroy();
		*/
#pragma endregion

	private:
		std::list<object_ptr>	 _children;
		std::list<component_ptr> _components;
		object_wptr				 _parent;
		uid_t					 _uid;
		bool					 _is_parenting { false };
	};
} // namespace gl