#pragma once

#include <list>

#include <singleton.h>
#include <entity.h>

class entity_manager : public singleton<entity_manager>
{
public:
	entity_manager() = default;

	void add_entity(entity* obj);
	void remove_entity(entity* obj);
	const std::list<entity*>& entities() const;

private:
	std::list<entity*> _entities;
};