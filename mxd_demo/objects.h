#pragma once

#ifndef __OBJECTS_H__
#define __OBJECTS_H__

#include "carama.h"

class object
{
public:
	object(carama_info* carama);
	~object();
	world_area* get_base_area() { return &this->_base_area; };

	void initObject(coord coo, int w, int h)
	{
		this->_base_area.init(coo, w, h);
	};

	void initObject(int x, int y, int w, int h)
	{
		this->_base_area.init(x, y, w, h);
	};

	int get_width()
	{
		return this->_base_area.get_width();
	};

	int get_height()
	{
		return this->_base_area.get_height();
	};

protected:
	world_area _base_area;
	carama_info* _carama;
};

class static_object : public object
{
public:
	static_object(carama_info* carama) : object(carama) {}
};

class dynamic_object : public object
{
public:
	dynamic_object(carama_info* carama) : object(carama) {}

	void changeCoord(coord coo)
	{
		this->get_base_area()->changeCoord(coo);
	}

	void changeOffCoord(coord coo)
	{
		this->get_base_area()->changeOffCoord(coo);
	}

	void changeX(int x)
	{
		this->get_base_area()->changeX(x);
	}

	void changeY(int y)
	{
		this->get_base_area()->changeY(y);
	}

	void changeOffX(int off_x)
	{
		this->get_base_area()->changeOffX(off_x);
	}

	void changeOffY(int off_y)
	{
		this->get_base_area()->changeOffY(off_y);
	}

	int v_y = 0;
	bool is_on_ground = false;
};

// ----------------------------------------------------------

class render_object
{
public:
	render_object(carama_info* carama);
	~render_object();
	world_area* get_render_area();

	void setRenderArea(object* o)
	{
		this->_render_area.init(
			o->get_base_area()->get_coord_base(),
			coord(0, 0), o->get_base_area()->get_width(), o->get_base_area()->get_height());
	}
	void setRenderArea(object* o, coord off_coo, int w, int h)
	{
		this->_render_area.init(
			o->get_base_area()->get_coord_base(), off_coo, w, h);
	}

protected:
	world_area _render_area;
};

class collsion_object
{
public:
	collsion_object(carama_info* carama)
	{
		this->_collsion_area.set_carama(carama);
	}
	~collsion_object()
	{
	}
	world_area* get_collsion_area() { return &this->_collsion_area; };

	void setCollsionArea(object* o)
	{
		this->_collsion_area.init(
			o->get_base_area()->get_coord_base(),
			coord(0, 0), o->get_base_area()->get_width(), o->get_base_area()->get_height());
	}
	void setCollsionArea(object* o, coord off_coo, int w, int h)
	{
		this->_collsion_area.init(
			o->get_base_area()->get_coord_base(), off_coo, w, h);
	}
protected:
	world_area _collsion_area;
};

class hit_object
{
public:
	hit_object(carama_info* carama)
	{
		this->_hit_area.set_carama(carama);
	}
	~hit_object()
	{
	}
	world_area* get_hit_area() { return &this->_hit_area; };

	void setHitArea(object* o)
	{
		this->_hit_area.init(
			o->get_base_area()->get_coord_base(),
			coord(0, 0), o->get_base_area()->get_width(), o->get_base_area()->get_height());
	}
	void setHitArea(object* o, coord off_coo, int w, int h)
	{
		this->_hit_area.init(
			o->get_base_area()->get_coord_base(), off_coo, w, h);
	}
protected:
	world_area _hit_area;
};

class attack_object
{
public:
	attack_object(carama_info* carama)
	{
		this->_attack_area.set_carama(carama);
	}
	~attack_object()
	{
	}
	world_area* get_attack_area() { return &this->_attack_area; };

	void setAttackArea(object* o)
	{
		this->_attack_area.init(
			o->get_base_area()->get_coord_base(),
			coord(0, 0), o->get_base_area()->get_width(), o->get_base_area()->get_height());
	}
	void setAttackArea(object* o, coord off_coo, int w, int h)
	{
		this->_attack_area.init(
			o->get_base_area()->get_coord_base(), off_coo, w, h);
	}
protected:
	world_area _attack_area;
};

class health_object
{
public:
	health_object(carama_info* carama)
	{
		this->_health_area.set_carama(carama);
	}
	~health_object()
	{
	}
	world_area* get_health_area() { return &this->_health_area; };

	void setHealthArea(object* o)
	{
		this->_health_area.init(
			o->get_base_area()->get_coord_base(),
			coord(0, 0), o->get_base_area()->get_width(), o->get_base_area()->get_height());
	}
	void setHealthArea(object* o, coord off_coo, int w, int h)
	{
		this->_health_area.init(
			o->get_base_area()->get_coord_base(), off_coo, w, h);
	}
protected:
	world_area _health_area;
};

class ground_check_object
{
public:
	ground_check_object(carama_info* carama)
	{
		this->_ground_check_area.set_carama(carama);
	}
	~ground_check_object()
	{
	}
	world_area* get_ground_check_area() { return &this->_ground_check_area; };

	void setGroundCheckArea(object* o)
	{
		this->_ground_check_area.init(
			o->get_base_area()->get_coord_base(),
			coord(o->get_base_area()->get_width() / 4, o->get_base_area()->get_height()), o->get_base_area()->get_width() / 2, 10);
	}
	void setGroundCheckArea(object* o, coord off_coo, int w, int h)
	{
		this->_ground_check_area.init(
			o->get_base_area()->get_coord_base(), off_coo, w, h);
	}
protected:
	world_area _ground_check_area;
};

// ----------------------------------------

class block : public static_object, public render_object, public collsion_object
{
public:
	block(carama_info* carama) :
		static_object(carama),
		render_object(carama),
		collsion_object(carama)
	{}

	void init(int x, int y, int w, int h)
	{
		this->initObject(x, y, w, h);
		this->setRenderArea(this);
		this->setCollsionArea(this);
	}

	void init(coord coo, int w, int h)
	{
		this->initObject(coo, w, h);
		this->setRenderArea(this);
		this->setCollsionArea(this);
	}
};

class sprite_object : public dynamic_object,
						public render_object,
						public collsion_object,
						public hit_object,
						public ground_check_object
{
public:
	sprite_object(carama_info* carama) :
		dynamic_object(carama),
		render_object(carama),
		collsion_object(carama),
		hit_object(carama),
		ground_check_object(carama)
	{}
};

class player : public sprite_object,
				public attack_object
{
public:
	player(carama_info* carama) :
		sprite_object(carama),
		attack_object(carama)
	{}
};

class enemy : public sprite_object,
				public health_object
{
public:
	enemy(carama_info* carama) :
		sprite_object(carama),
		health_object(carama)
	{}
};


#endif
