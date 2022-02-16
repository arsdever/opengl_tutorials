#include "entity_manager.h"

void entity_manager::add_entity(entity* obj)
{
	_entities.push_back(obj);
}

void entity_manager::remove_entity(entity* obj)
{
	auto it = std::find(_entities.begin(), _entities.end(), obj);
	if (it != _entities.end())
		_entities.erase(it);
}

const std::list<entity*>& entity_manager::entities() const
{
	return _entities;
}