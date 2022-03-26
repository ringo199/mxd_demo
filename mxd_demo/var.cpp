#include "var.h"

area::area()
{
	this->init(0, 0, 0, 0);
}

area::area(coord coo)
{
	this->init(coo, 0, 0);
}

area::area(int x, int y)
{
	this->init(x, y, 0, 0);
}

area::area(int x, int y, int w, int h)
{
	this->init(x, y, w, h);
}

area::area(coord coo, int w, int h)
{
	this->init(coo, w, h);
}

area::area(coord* ref_coo, coord off_coo, int w, int h)
{
	this->init(ref_coo, off_coo, w, h);
}

area::~area()
{
}

void area::init(coord* ref_coo, coord off_coo, int w, int h)
{
	this->_is_ref = true;
	this->_ref_coo = ref_coo;
	this->_off_coo = off_coo;
	this->_w = w;
	this->_h = h;
}

void area::init(coord coo, int w, int h)
{
	this->_coo = coo;
	this->_w = w;
	this->_h = h;
	this->_is_ref = false;
	this->_ref_coo = NULL;
}

void area::init(int x, int y, int w, int h)
{
	this->_coo = coord(x, y);
	this->_w = w;
	this->_h = h;
	this->_is_ref = false;
	this->_ref_coo = NULL;
}

void area::changeCoord(coord coo)
{
	this->_coo = coo;
}

void area::changeOffCoord(coord coo)
{
	this->_coo = this->_coo + coo;
}

void area::changeRefOffCoord(coord off_coo)
{
	this->_off_coo = off_coo;
}

void area::changeX(int x)
{
	this->_coo.x = x;
}

void area::changeOffX(int x)
{
	this->_coo.x += x;
}

void area::changeY(int y)
{
	this->_coo.y = y;
}

void area::changeOffY(int y)
{
	this->_coo.y += y;
}

coord* area::get_coord_base()
{
	if (this->_is_ref)
	{
		return this->_ref_coo;
	}
	else
	{
		return &this->_coo;
	}
}

coord* area::get_coord1_in_world()
{
	if (this->_is_ref)
	{
		this->_real_coo1_in_world = *this->_ref_coo + this->_off_coo;
	}
	else
	{
		this->_real_coo1_in_world = this->_coo;
	}

	return &this->_real_coo1_in_world;
}

coord* area::get_coord2_in_world()
{
	this->_real_coo2_in_world = *this->get_coord1_in_world();

	this->_real_coo2_in_world.x = this->_real_coo2_in_world.x + this->_w;
	this->_real_coo2_in_world.y = this->_real_coo2_in_world.y + this->_h;

	return &this->_real_coo2_in_world;
}

coord* area::get_coord_center_in_world()
{
	this->_real_coo_center_in_world = *this->get_coord1_in_world();

	this->_real_coo_center_in_world.x = this->_real_coo_center_in_world.x + this->_w * 0.5;
	this->_real_coo_center_in_world.y = this->_real_coo_center_in_world.y + this->_h * 0.5;

	return &this->_real_coo_center_in_world;
}

coord* area::get_coord1()
{
	if (this->_is_ref)
	{
		this->_real_coo1 = *this->_ref_coo + this->_off_coo;
	}
	else
	{
		this->_real_coo1 = this->_coo;
	}

	return &this->_real_coo1;
}

coord* area::get_coord2()
{
	this->_real_coo2 = *this->get_coord1();

	this->_real_coo2.x = this->_real_coo2.x + this->_w;
	this->_real_coo2.y = this->_real_coo2.y + this->_h;

	return &this->_real_coo2;
}

coord* area::get_coord_center()
{
	this->_real_coo_center = *this->get_coord1();

	this->_real_coo_center.x = this->_real_coo_center.x + this->_w * 0.5;
	this->_real_coo_center.y = this->_real_coo_center.y + this->_h * 0.5;

	return &this->_real_coo_center;
}

int area::get_width()
{
	return this->_w;
}

int area::get_height()
{
	return this->_h;
}

// world_area
#include "global.h"

using namespace global;

coord* world_area::get_coord1()
{
	if (this->_is_ref)
	{
		GetCarama()->mapCoord2CaramaCoora(*this->_ref_coo + this->_off_coo, &this->_real_coo1);
	}
	else
	{
		GetCarama()->mapCoord2CaramaCoora(this->_coo, &this->_real_coo1);
	}

	return &this->_real_coo1;
}

coord* world_area::get_coord2()
{
	this->_real_coo2 = *this->get_coord1();

	this->_real_coo2.x += this->_w;
	this->_real_coo2.y += this->_h;

	return &this->_real_coo2;
}

coord* world_area::get_coord_center()
{
	this->_real_coo_center = *this->get_coord1();

	this->_real_coo_center.x += this->_w * 0.5;
	this->_real_coo_center.y += this->_h * 0.5;

	return &this->_real_coo_center;
}
