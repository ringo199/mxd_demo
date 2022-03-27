#pragma once


#ifndef __ENEMY_H__
#define __ENEMY_H__

#include <stdio.h>
#include <math.h>
#include <graphics.h>
#include "tools.h"
#include "var.h"
#include "objects.h"

class old_enemy : public enemy
{
public:
	old_enemy();
	~old_enemy();

	enum class enemy_status
	{
		BIRTH,
		DIE,
		DIED,

		IDLE,
		RUN,

		COUNT
	};

	void init(int x, int y);

	virtual void render() override;
	virtual void animator() override;
	virtual void other_event() override;

	void renderHP();
	void ai();
	void change_status();
	void move();
	void hit();
	void hitting();

	static void CreateEnemy(int x, int y);

private:
	enemy_status status;
	bool is_reverse;
	int speed;
	int area_pad;
	bool is_hit;
	float sa_percent;

	int health;
	int healthMax;

	void _move();

	void _died();

	unsigned long long _change_status_timer_const = 500;
	unsigned long long _hitting_timer_const = 100;

	unsigned long long _change_status_timer = 0;
	unsigned long long _hitting_timer = 0;
	int _hitting_angle = 0;
};

#endif
