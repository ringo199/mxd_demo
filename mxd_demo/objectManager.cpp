
#include "objectManager.h"
#include "global.h"
#include "tools.h"

using namespace global;

objectManager::objectManager()
{
	this->_col = GetCollision();
}

objectManager::~objectManager()
{
}

void objectManager::beforeEvent()
{
	this->_collision_event();
}

void objectManager::render()
{
	for (int i = 0; i < this->_render_objects.size(); ++i)
	{
		this->_render_objects[i]->render();
	}
}

void objectManager::afterEvent()
{
	this->_animator();
	this->_hit();
	this->_other_event();
}

void objectManager::delivery(world_area *playerArea)
{
	for (int i = 0; i < this->_transpoints.size(); ++i)
	{
		if (rectIntersect(playerArea, this->_transpoints[i]->get_transpoint_area()))
		{
			this->_transpoints[i]->trans();
			break;
		}
	}
}

void objectManager::clear_objects()
{
	vector<render_object *>().swap(this->_render_objects);
	vector<hit_object *>().swap(this->_hit_objects);
	vector<attack_object *>().swap(this->_attack_objects);

	vector<animator_ *>().swap(this->_animators);
	vector<other_event_ *>().swap(this->_other_events);
	vector<transpoint_object*>().swap(this->_transpoints);
	vector<click_event_object*>().swap(this->_click_event_objects);

	GetCollision()->clear_objects();
}

void objectManager::checkClickEvent(coord* coo)
{
	for (int i = 0; i < this->_click_event_objects.size(); ++i)
	{
		if (isCoordInRect(coo, this->_click_event_objects[i]->get_click_event_area()))
		{
			this->_click_event_objects[i]->callEventListener();
		}
	}
}

void objectManager::_hit()
{
	int i, j;
	for (i = 0; i < this->_hit_objects.size(); ++i)
	{
		if (!this->_hit_objects[i]->checkHit())
		{
			for (j = 0; j < this->_attack_objects.size(); ++j)
			{
				if (this->_hit_objects[i]->_hit_type == this->_attack_objects[j]->_atk_type)
				{
					continue;
				}
				if (this->_attack_objects[j]->getIsAttack())
				{
					if (rectIntersect(
							this->_hit_objects[i]->get_hit_area(),
							this->_attack_objects[j]->get_attack_area()))
					{
						this->_hit_objects[i]->startHit();
						this->_hit_objects[i]->hit();
					}
				}
			}
		}
	}
}

void objectManager::_collision_event()
{
	GetCollision()->graviry_check();
	GetCollision()->graviry_force();
	GetCollision()->rigidbody_check();
}

void objectManager::_animator()
{
	for (int i = 0; i < this->_animators.size(); ++i)
	{
		this->_animators[i]->animator();
	}
}

void objectManager::_other_event()
{
	for (int i = 0; i < this->_other_events.size(); ++i)
	{
		this->_other_events[i]->other_event();
	}
}
