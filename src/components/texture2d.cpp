#include "texture2d.hpp"

#include <vector>
#include <fstream>
#include <components/vertex/color.hpp>

#include <turbojpeg.h>

namespace gl
{
	texture2d::texture2d()
	{}

	texture2d texture2d::from_file(const std::filesystem::path& filepath)
	{
		std::ifstream reader(filepath, std::ios::binary);
		if (!reader)
		{
			return {};
		}

		std::vector<uint8_t> buffer{ std::istreambuf_iterator<char>(reader), {} };
		reader.close();

		// convert to jpeg

		texture2d result;
		unsigned& width = result._width;
		unsigned& height = result._height;
		std::vector<uint8_t>& dst = result._data;

		int w;
		int h;

		tjhandle decompress = tjInitDecompress();
		tjDecompressHeader(decompress, buffer.data(), buffer.size(), &w, &h);

		width = static_cast<unsigned>(w);
		height = static_cast<unsigned>(h);
		dst.resize(width * height * TJPF_RGBA);

		tjDecompress2(decompress, buffer.data(), buffer.size(), dst.data(), width, width * tjPixelSize[TJPF_RGBA], height, TJPF_RGBA, 0);
		return result;
	}

	const std::vector<uint8_t>& texture2d::data() const
	{
		return _data;
	}

	unsigned texture2d::width() const
	{
		return _width;
	}

	unsigned texture2d::height() const
	{
		return _height;
	}
}