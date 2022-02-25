#pragma once

#include <shader_prog.h>
#include <components/component.hpp>
#include <components/texture2d.hpp>

namespace gl
{
	class camera;

	class renderer
		: public component
	{
	public:
		virtual void start() override;
		
		void render(std::shared_ptr<camera> cam);

		texture2d main_texture() const;
		void set_main_texture(const texture2d& texture);

	private:
		unsigned int _vbo;
		unsigned int _vao;
		unsigned int _ebo;
		unsigned int _texture;
		shader_prog _shader_prog;
		texture2d _main_texture;
	};
}