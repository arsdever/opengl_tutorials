#pragma once

#include <components/component.hpp>
#include <shader_prog.h>

namespace gl
{
	class camera;

	class renderer
		: public component
	{
	public:
		virtual void start() override;
		
		void render(std::shared_ptr<camera> cam);

	private:
		unsigned int _vbo;
		unsigned int _vao;
		unsigned int _ebo;
		shader_prog _shader_prog;
	};
}