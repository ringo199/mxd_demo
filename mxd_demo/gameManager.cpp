
#include "gameManager.h"

gameManager::gameManager()
{
}

gameManager::~gameManager()
{
}

void gameManager::beforeEvent()
{
	this->_collision_event();
}

void gameManager::render()
{
	for (int i = 0; i < this->_render_objects.size(); ++i)
	{
		this->_render_objects[i]->render();
	}
}

void gameManager::afterEvent()
{
	this->_animator();
	this->_hit();
	this->_other_event();
}

void gameManager::clear_objects()
{
	vector<render_object*>().swap(this->_render_objects);
	vector<hit_object*>().swap(this->_hit_objects);
	vector<attack_object*>().swap(this->_attack_objects);

	vector<animator_*>().swap(this->_animators);
	vector<other_event_*>().swap(this->_other_events);

	this->_col.clear_objects();
}

void gameManager::_hit()
{
	int i, j;
	for (i = 0; i < this->_hit_objects.size(); ++i)
	{
		if (!this->_hit_objects[i]->checkHit())
		{
			for (j = 0; j < this->_attack_objects.size(); ++j)
			{
				if (this->_hit_objects[i]->_hit_base_point == this->_attack_objects[j]->_attack_base_point)
				{
					continue;
				}
				if (this->_attack_objects[j]->getIsAttack())
				{
					if (rectIntersect(
						this->_hit_objects[i]->get_hit_area(),
						this->_attack_objects[j]->get_attack_area()
					))
					{
						this->_hit_objects[i]->startHit();
						this->_hit_objects[i]->hit();
					}
				}
			}
		}
	}
}

void gameManager::_collision_event()
{
	//this->_col.graviry_check();
	//this->_col.graviry_force();
	this->_col.rigidbody_check();
}

void gameManager::_animator()
{
	for (int i = 0; i < this->_animators.size(); ++i)
	{
		this->_animators[i]->animator();
	}
}

void gameManager::_other_event()
{
	for (int i = 0; i < this->_other_events.size(); ++i)
	{
		this->_other_events[i]->other_event();
	}
}

