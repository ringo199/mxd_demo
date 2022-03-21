#pragma once
#ifndef __RIGIDBODY_H__
#define __RIGIDBODY_H__

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

class rigidbody
{
public:
	rigidbody(carama_info*);
	~rigidbody();

	void render_static_objs();
	void rigidbody_check();
	void graviry_check();

	void graviry_force();

	void push_static_objs(block* s_obj);
	void push_dynamic_objs(sprite_object* d_obj);

	// todo:
	// objects ��Ϊ��̬�;�̬�ģ��̳���world_area
	// ��̬��Ϊplayer��enemy��base
	// ��̬��Ϊground��block��base
private:
	vector<block*> static_objs;
	vector<sprite_object*> dynamic_objs;
	// ���������ַ�ĺ���Ϊkey��������Ϊvalue
	map<long, char> two_obs_pos;

	char _check_move_direction(world_area* static_obj, world_area* dynamic_obj);
};

#endif
