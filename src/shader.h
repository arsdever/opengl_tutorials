#pragma once

#include <filesystem>
#include <string>

class shader
{
public:
	static shader from_file(const std::filesystem::path& path);
	unsigned int  id() const;

private:
	unsigned int _type;
	unsigned int _id;
};