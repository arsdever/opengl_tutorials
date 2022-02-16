#pragma once

template <typename clazz>
class singleton
{
public:
	static clazz& instance();
};

template <typename clazz>
clazz& singleton<clazz>::instance()
{
	static clazz obj{};
	return obj;
}