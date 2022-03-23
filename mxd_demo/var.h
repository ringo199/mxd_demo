#pragma once

#ifndef __VAR_H__
#define __VAR_H__

#include <stdio.h>

#define GRAVITY 10;

static bool s_update = false;

enum e_scene_type
{
	LOADING = -2,
	UI_SCENE_NULL = -1,

	CHECK_MASTER_SERVER,
	LOGIN,
	CHECK_SLAVE_SERVER,
	CHECK_PLAYER,
	GAME,

	UI_COUNT
};

enum e_game_scene_type
{
	GAME_SCENE_NULL = -1,
	GAME_1,
	GAME_2,

	GAME_SCENE_COUNT
};

enum e_event_type
{
	UI_NEXT,
	UI_BACK,
	UI_BACKHOME,

	UI_BEGIN_LOADING,
	UI_END_LOADING,

	GAME_GOTO_SCENE,

	//-- game
	GAME_CMD_LEFT,
	GAME_CMD_RIGHT,
	GAME_CMD_UP,
	GAME_CMD_DOWN,
	GAME_CMD_JUMP,
	GAME_CMD_ATTACK,
};


class coord
{
public:
	coord()
	{
		this->x = 0;
		this->y = 0;
	};

	coord(int ix, int iy)
	{
		this->x = ix;
		this->y = iy;
	};

	coord operator + (const coord& coo) const {
		coord tmpcoo(this->x, this->y);
		tmpcoo.x += coo.x;
		tmpcoo.y += coo.y;
		return tmpcoo;
	};

	coord operator - (const coord& coo) const {
		coord tmpcoo(this->x, this->y);
		tmpcoo.x -= coo.x;
		tmpcoo.y -= coo.y;
		return tmpcoo;
	};

	int x_except_y()
	{
		if (y == 0)
		{
			return 0;
		}
		return x / y;
	}

	int x;
	int y;
};

class area
{
public:
	area();
	area(coord coo);
	area(int x, int y);
	area(int x, int y, int w, int h);
	area(coord coo, int w, int h);
	area(coord* ref_coo, coord off_coo, int w, int h);
	~area();

	void init(coord* ref_coo, coord off_coo, int w, int h);
	void init(coord coo, int w, int h);
	void init(int x, int y, int w, int h);

	void changeCoord(coord coo);
	void changeOffCoord(coord coo);
	void changeRefOffCoord(coord off_coo);
	void changeX(int x);
	void changeOffX(int x);
	void changeY(int y);
	void changeOffY(int y);

	coord* get_coord_base();
	coord* get_coord1_in_world();
	coord* get_coord2_in_world();
	coord* get_coord_center_in_world();
	virtual coord* get_coord1();
	virtual coord* get_coord2();
	virtual coord* get_coord_center();

	int get_width();
	int get_height();

protected:
	coord _real_coo1_in_world;
	coord _real_coo2_in_world;
	coord _real_coo_center_in_world;

	coord _real_coo1;
	coord _real_coo2;
	coord _real_coo_center;

	coord _coo;

	// 引用坐标
	coord* _ref_coo;
	// 引用坐标与实际坐标的差值（左上角）
	coord _off_coo;

	bool _is_ref;

	int _w;
	int _h;
};

#endif
