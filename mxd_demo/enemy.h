#pragma once


#ifndef __ENEMY_H__
#define __ENEMY_H__

#include <stdio.h>
#include <math.h>
#include <graphics.h>
#include "tools.h"
#include "carama.h"
#include "objects.h"

class old_enemy : public enemy
{
public:
	old_enemy(carama_info* carama);
	~old_enemy();

	enum class enemy_status
	{
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
