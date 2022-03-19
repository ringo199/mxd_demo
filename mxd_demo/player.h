#pragma once

#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <stdio.h>
#include <math.h>
#include <graphics.h>
#include "tools.h"
#include "carama.h"
#include "rigidbody.h"
#include "var.h"

class player_info
{
public:
	player_info();
	~player_info();

	enum class player_status
	{
		IDLE,
		RUN,
		JUMP,
		ATTACK,
	};

	world_area player_area;
	world_area hit_area;
	world_area atk_area;

	void init(carama_info* carama, rigidbody* rb, coord coo);

	void animator();
	void render();
	void renderHP();

	void run(int is_right);
	void updown(int is_daown);
	void jump();
	void attack();
	void hit(bool h);
	void hitting();

	void droping();
	void attacking();

	void checkIsRuning();
	void cancelRuning();

	bool is_attacking;

private:
	player_status status;
	IMAGE imgPlayer[12];
	IMAGE imgAtkPlayer[12];
	char path[64];
	int imgIndex;
	carama_info* _carama;

	float jump_v; // 跳跃的速度

	bool is_reverse;
	bool is_runing;
	bool is_jumping;
	bool is_hit;

	float speed;
	int area_pad; // 面积的内边距
	int area_atk_x;
	float sa_percent;

	int health;
	int healthMax;

	void _load();
	void _move(coord coo);
};

#endif
