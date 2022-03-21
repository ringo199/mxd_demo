#pragma once

#ifndef __VAR_H__
#define __VAR_H__

#define GRAVITY 10;

static bool s_update = false;

struct coord
{
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
