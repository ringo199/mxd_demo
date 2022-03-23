#pragma once
#ifndef __COLLISION_H__
#define __COLLISION_H__

#include "carama.h"
#include "var.h"
#include "tools.h"
#include <vector>
#include <map>
#include <cmath>
#include "objects.h"

using namespace std;

#define TOP		0x1
#define BOTTOM	0x2
#define LEFT	0x4
#define RIGHT	0x8

class collision
{
public:
	collision();
	~collision();

	void rigidbody_check();
	void graviry_check();
	void graviry_force();

	void clear_objects();

	void push_dynamic_collsion_object(dynamic_collsion_object* obj)
	{
		this->_dynamic_collsion_objects.push_back(obj);
	}

	void push_static_collsion_object(static_collsion_object* obj)
	{
		this->_static_collsion_objects.push_back(obj);
	}

	// todo:
	// objects 分为动态和静态的，继承自world_area
	// 动态的为player和enemy的base
	// 静态的为ground和block的base
private:
	vector<static_collsion_object*> _static_collsion_objects;
	vector<dynamic_collsion_object*> _dynamic_collsion_objects;

	// 两个物体地址的和作为key，方向作为value
	map<long, char> two_obs_pos;

	char _check_move_direction(world_area* static_obj, world_area* dynamic_obj);
};

#endif
