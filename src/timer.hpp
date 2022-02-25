#pragma once

namespace gl
{
	class timer
	{
	public:
		static float now();
		static void	 update();
		static float delta();

	private:
		static float _last;
	};
} // namespace gl