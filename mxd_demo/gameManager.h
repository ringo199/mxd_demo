#pragma once

#ifndef __GAME_MANAGER_H__
#define __GAME_MANAGER_H__

#include "objects.h"
#include "collision.h"
#include "player.h"
#include "enemy.h"
#include <stdio.h>
#include <vector>

using namespace std;

class gameManager
{
public:
	gameManager();
	~gameManager();

	void beforeEvent();
	void render();
	void afterEvent();

	template<typename T>
	void delete_one_in_vector(T* obj, vector<T*>* objs)
	{
		typename vector<T*>::iterator it;
		for (it = objs->begin(); it != objs->end(); it++)
		{
			if (*it == obj)
			{
				objs->erase(it);
			}
		}
	}

	template<typename T>
	void push_object(T* obj)
	{
		render_object* render_obj = dynamic_cast<render_object*>(obj);
		if (render_obj != NULL)
		{
			this->_render_objects.push_back(render_obj);
		}

		hit_object* hit_obj = dynamic_cast<hit_object*>(obj);
		if (hit_obj != NULL)
		{
			this->_hit_objects.push_back(hit_obj);
		}

		attack_object* attack_obj = dynamic_cast<attack_object*>(obj);
		if (attack_obj != NULL)
		{
			this->_attack_objects.push_back(attack_obj);
		}

		dynamic_collsion_object* dynamic_collsion_obj = dynamic_cast<dynamic_collsion_object*>(obj);
		if (dynamic_collsion_obj != NULL)
		{
			this->_col->push_dynamic_collsion_object(dynamic_collsion_obj);
		}

		static_collsion_object* static_collsion_obj = dynamic_cast<static_collsion_object*>(obj);
		if (static_collsion_obj != NULL)
		{
			this->_col->push_static_collsion_object(static_collsion_obj);
		}

		animator_* anim = dynamic_cast<animator_*>(obj);
		if (anim != NULL)
		{
			this->_animators.push_back(anim);
		}
		other_event_* other_e = dynamic_cast<other_event_*>(obj);
		if (other_e != NULL)
		{
			this->_other_events.push_back(other_e);
		}
	}

	template<typename T>
	void delete_object(T* obj)
	{
		render_object* render_obj = dynamic_cast<render_object*>(obj);
		if (render_obj != NULL)
		{
			delete_one_in_vector(render_obj, &this->_render_objects);
		}

		hit_object* hit_obj = dynamic_cast<hit_object*>(obj);
		if (hit_obj != NULL)
		{
			delete_one_in_vector(hit_obj, &this->_hit_objects);
		}

		attack_object* attack_obj = dynamic_cast<attack_object*>(obj);
		if (attack_obj != NULL)
		{
			delete_one_in_vector(attack_obj, &this->_attack_objects);
		}

		dynamic_collsion_object* dynamic_collsion_obj = dynamic_cast<dynamic_collsion_object*>(obj);
		if (dynamic_collsion_obj != NULL)
		{
			this->_col->delete_dynamic_collsion_object(dynamic_collsion_obj);
		}

		static_collsion_object* static_collsion_obj = dynamic_cast<static_collsion_object*>(obj);
		if (static_collsion_obj != NULL)
		{
			this->_col->delete_static_collsion_object(static_collsion_obj);
		}

		animator_* anim = dynamic_cast<animator_*>(obj);
		if (anim != NULL)
		{
			this->_animators.push_back(anim);
		}
		other_event_* other_e = dynamic_cast<other_event_*>(obj);
		if (other_e != NULL)
		{
			this->_other_events.push_back(other_e);
		}
	}

	void clear_objects();

private:
	vector<render_object*> _render_objects;
	vector<hit_object*> _hit_objects;
	vector<attack_object*> _attack_objects;

	vector<animator_*> _animators;
	vector<other_event_*> _other_events;

	void _hit();
	void _collision_event();
	void _animator();
	void _other_event();

	collision* _col;
};

#endif
