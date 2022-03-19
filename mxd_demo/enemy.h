#pragma once


#ifndef __ENEMY_H__
#define __ENEMY_H__

#include <stdio.h>
#include <math.h>
#include <graphics.h>
#include "tools.h"
#include "carama.h"
#include "rigidbody.h"

class enemy
{
public:
	enemy();
	~enemy();

	enum class enemy_status
	{
		IDLE,
		RUN,

		COUNT
	};

	world_area enemy_area;
	world_area hit_area;
	world_area health_area;

	void init(carama_info* carama, rigidbody* rb, int x, int y);
	void render();
	void renderHP();
	void animator();
	void ai();
	void change_status();
	void move();
	void hit(bool);
	void hitting();

private:
	int imgIndex;
	IMAGE* imgEnemy;
	char path[64];
	enemy_status status;
	bool is_reverse;
	int speed;
	int area_pad;
	bool is_hit;
	float sa_percent;

	int health;
	int healthMax;

	void _move();
	void _load();
};
#endif
