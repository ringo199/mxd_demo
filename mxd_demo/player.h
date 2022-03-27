#pragma once

#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <stdio.h>
#include <math.h>
#include <graphics.h>
#include "tools.h"
#include "carama.h"
#include "var.h"
#include "objects.h"
#include "event_manager.h"

class player_info : public player
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

	void init(int x, int y);

	virtual void render() override;
	virtual void animator() override;
	virtual void other_event() override;

	void run(int is_right);
	void updown(int is_daown);
	void jump();
	void attack();
	void hit();
	void hitting();

	void attacking();

	void checkIsRuning();
	void cancelRuning();

	void eventRegister();
	void clearEventRegister();

	static void cmdUp(void*);
	static void cmdDown(void*);
    static void cmdLeftRun(void*);
	static void cmdRightRun(void*);
	static void cmdJump(void*);
	static void cmdAttack(void*);
	static void cmdStay(void*);

private:
	player_status status;

	bool is_reverse;
	bool is_runing;

	float speed;
	int area_pad; // 面积的内边距
	int area_atk_x;
	float sa_percent;

	int health;
	int healthMax;

	void _move(coord coo);
};

#endif
