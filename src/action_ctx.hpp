#pragma once

#include <glm/ext.hpp>
#include <iostream>
#include <variant>

namespace gl
{
	class action_ctx
	{
	public:
		using variant_t = std::variant<char, int, long, float, double, glm::vec2, glm::vec3, glm::vec4>;

	public:
		action_ctx(bool performed, variant_t value) : _performed { performed }, _value { value } { }

		template <typename T>
		T value() const
		{
			try
				{
					return std::get<T>(_value);
				}
			catch (const std::bad_variant_access& ex)
				{
					std::cout << ex.what() << '\n';
				}
			return {};
		}

		operator bool() { return _performed; }

	private:
		bool	  _performed;
		variant_t _value;
	};
} // namespace gl