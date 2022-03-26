#pragma once

#ifndef __OBJECT_MANAGER_H__
#define __OBJECT_MANAGER_H__

#include "objects.h"
#include "collision.h"
#include "player.h"
#include "enemy.h"
#include <stdio.h>
#include <vector>

using namespace std;

class objectManager
{
public:
	objectManager();
	~objectManager();

	void beforeEvent();
	void render();
	void afterEvent();

	// ´«ËÍ
	void delivery(world_area *playerArea);

	template <typename T>
	void push_object(T *obj)
	{
		render_object *render_obj = dynamic_cast<render_object *>(obj);
		if (render_obj != NULL)
		{
			this->_render_objects.push_back(render_obj);
		}

		hit_object *hit_obj = dynamic_cast<hit_object *>(obj);
		if (hit_obj != NULL)
		{
			this->_hit_objects.push_back(hit_obj);
		}

		attack_object *attack_obj = dynamic_cast<attack_object *>(obj);
		if (attack_obj != NULL)
		{
			this->_attack_objects.push_back(attack_obj);
		}

		dynamic_collsion_object *dynamic_collsion_obj = dynamic_cast<dynamic_collsion_object *>(obj);
		if (dynamic_collsion_obj != NULL)
		{
			this->_col->push_dynamic_collsion_object(dynamic_collsion_obj);
		}

		static_collsion_object *static_collsion_obj = dynamic_cast<static_collsion_object *>(obj);
		if (static_collsion_obj != NULL)
		{
			this->_col->push_static_collsion_object(static_collsion_obj);
		}

		animator_ *anim = dynamic_cast<animator_ *>(obj);
		if (anim != NULL)
		{
			this->_animators.push_back(anim);
		}
		other_event_ *other_e = dynamic_cast<other_event_ *>(obj);
		if (other_e != NULL)
		{
			this->_other_events.push_back(other_e);
		}
		transpoint_object *trans_obj = dynamic_cast<transpoint_object *>(obj);
		if (trans_obj != NULL)
		{
			this->_transpoints.push_back(trans_obj);
		}
		click_event_object* click_event_obj = dynamic_cast<click_event_object*>(obj);
		if (click_event_obj != NULL)
		{
			this->_click_event_objects.push_back(click_event_obj);
		}
	}

	template <typename T>
	void delete_object(T *obj)
	{
		render_object *render_obj = dynamic_cast<render_object *>(obj);
		if (render_obj != NULL)
		{
			for (int i = 0; i < this->_render_objects.size(); ++i)
			{
				if (render_obj->_render_base_point == this->_render_objects[i]->_render_base_point)
				{
					this->_render_objects.erase(this->_render_objects.begin() + i);
					break;
				}
			}
		}

		hit_object *hit_obj = dynamic_cast<hit_object *>(obj);
		if (hit_obj != NULL)
		{
			for (int i = 0; i < this->_hit_objects.size(); ++i)
			{
				if (hit_obj->_hit_base_point == this->_hit_objects[i]->_hit_base_point)
				{
					this->_hit_objects.erase(this->_hit_objects.begin() + i);
					break;
				}
			}
		}

		attack_object *attack_obj = dynamic_cast<attack_object *>(obj);
		if (attack_obj != NULL)
		{
			for (int i = 0; i < this->_attack_objects.size(); ++i)
			{
				if (attack_obj->_attack_base_point == this->_attack_objects[i]->_attack_base_point)
				{
					this->_attack_objects.erase(this->_attack_objects.begin() + i);
					break;
				}
			}
		}

		dynamic_collsion_object *dynamic_collsion_obj = dynamic_cast<dynamic_collsion_object *>(obj);
		if (dynamic_collsion_obj != NULL)
		{
			this->_col->delete_dynamic_collsion_object(dynamic_collsion_obj, obj);
		}

		static_collsion_object *static_collsion_obj = dynamic_cast<static_collsion_object *>(obj);
		if (static_collsion_obj != NULL)
		{
			this->_col->delete_static_collsion_object(static_collsion_obj, obj);
		}

		animator_ *anim = dynamic_cast<animator_ *>(obj);
		if (anim != NULL)
		{
			for (int i = 0; i < this->_animators.size(); ++i)
			{
				if (anim->_animator_base_point == this->_animators[i]->_animator_base_point)
				{
					this->_animators.erase(this->_animators.begin() + i);
					break;
				}
			}
		}
		other_event_ *other_e = dynamic_cast<other_event_ *>(obj);
		if (other_e != NULL)
		{
			for (int i = 0; i < this->_other_events.size(); ++i)
			{
				if (other_e->_other_event_base_point == this->_other_events[i]->_other_event_base_point)
				{
					this->_other_events.erase(this->_other_events.begin() + i);
					break;
				}
			}
		}
		transpoint_object *trans_obj = dynamic_cast<transpoint_object *>(obj);
		if (trans_obj != NULL)
		{
			for (int i = 0; i < this->_transpoints.size(); ++i)
			{
				if (trans_obj->_transpoint_base_point == this->_transpoints[i]->_transpoint_base_point)
				{
					this->_transpoints.erase(this->_transpoints.begin() + i);
					break;
				}
			}
		}
		click_event_object* click_event_obj = dynamic_cast<click_event_object*>(obj);
		if (click_event_obj != NULL)
		{
			for (int i = 0; i < this->_click_event_objects.size(); ++i)
			{
				if (click_event_obj->_click_event_base_point == this->_click_event_objects[i]->_click_event_base_point)
				{
					this->_click_event_objects.erase(this->_click_event_objects.begin() + i);
					break;
				}
			}
		}
	}

	void clear_objects();

	void checkClickEvent(coord* coo);

private:
	vector<render_object *> _render_objects;
	vector<hit_object *> _hit_objects;
	vector<attack_object *> _attack_objects;

	vector<animator_ *> _animators;
	vector<other_event_ *> _other_events;
	vector<transpoint_object *> _transpoints;
	vector<click_event_object*> _click_event_objects;

	void _hit();
	void _collision_event();
	void _animator();
	void _other_event();

	collision *_col;
};

#endif
