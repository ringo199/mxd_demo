#pragma once
#ifndef __RIGIDBODY_H__
#define __RIGIDBODY_H__

#include "carama.h"
#include "var.h"
#include "tools.h"
#include <vector>
#include <cmath>

using namespace std;

#define TOP		0x1
#define BOTTOM	0x2
#define LEFT	0x4
#define RIGHT	0x8

class rigidbody
{
public:
	rigidbody(carama_info*);
	~rigidbody();

	void render_static_objs();
	void rigidbody_move();

	void push_static_objs(world_area*);
	void push_dynamic_objs(world_area*);

private:
	vector<world_area*> static_objs;
	vector<world_area*> dynamic_objs;

	char _check_move_direction(world_area* static_obj, world_area* dynamic_obj);
};

#endif
