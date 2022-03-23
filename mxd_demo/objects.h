#pragma once

#ifndef __OBJECTS_H__
#define __OBJECTS_H__

#include "carama.h"
#include "tools.h"

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

	virtual void render() {};

	void setRenderArea(object* o)
	{
		this->_render_area.init(
			o->get_base_area()->get_coord_base(),
			coord(0, 0), o->get_base_area()->get_width(), o->get_base_area()->get_height());
		this->_render_base_point = o;
	}
	void setRenderArea(object* o, coord off_coo, int w, int h)
	{
		this->_render_area.init(
			o->get_base_area()->get_coord_base(), off_coo, w, h);
		this->_render_base_point = o;
	}

	object* _render_base_point;

protected:
	world_area _render_area;
};

class collsion_object
{
public:
	collsion_object(carama_info* carama)
	{
		this->_collsion_area.set_carama(carama);
		this->_collsion_base_point = NULL;
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
		this->_collsion_base_point = o;
	}
	void setCollsionArea(object* o, coord off_coo, int w, int h)
	{
		this->_collsion_area.init(
			o->get_base_area()->get_coord_base(), off_coo, w, h);
		this->_collsion_base_point = o;
	}

	object* _collsion_base_point;

protected:
	world_area _collsion_area;
};

class hit_object
{
public:
	hit_object(carama_info* carama)
	{
		this->_hit_area.set_carama(carama);
		this->_is_hit = false;
		this->hit_time = 1500;
		this->_hit_cur_tick_count = getTickCount();
		this->_hit_base_point = NULL;
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

		this->_hit_base_point = o;
	}
	void setHitArea(object* o, coord off_coo, int w, int h)
	{
		this->_hit_area.init(
			o->get_base_area()->get_coord_base(), off_coo, w, h);

		this->_hit_base_point = o;
	}

	virtual void hit() {};

	bool getIsHit() { return this->_is_hit; }

	// 检查是否受击
	bool checkHit()
	{
		if (this->_is_hit)
		{
			if (getTickCount() - this->_hit_cur_tick_count >= this->hit_time)
			{
				this->_is_hit = false;
			}
		}

		return this->_is_hit;
	}

	void startHit()
	{
		if (!this->_is_hit)
		{
			this->_is_hit = true;
			this->_hit_cur_tick_count = getTickCount();
		}
	}

	int hit_time; // 无敌时间

	object* _hit_base_point;

protected:
	world_area _hit_area;
	bool _is_hit;
	unsigned long long _hit_cur_tick_count;
};

class attack_object
{
public:
	attack_object(carama_info* carama)
	{
		this->_attack_area.set_carama(carama);
		this->_is_attack = false;
		this->_attack_base_point = NULL;
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
		this->_attack_base_point = o;
	}
	void setAttackArea(object* o, coord off_coo, int w, int h)
	{
		this->_attack_area.init(
			o->get_base_area()->get_coord_base(), off_coo, w, h);
		this->_attack_base_point = o;
	}

	bool getIsAttack() { return this->_is_attack; }
	void startAttack() { this->_is_attack = true; }
	void stopAttack() { this->_is_attack = false; }

	object* _attack_base_point;

protected:
	world_area _attack_area;
	bool _is_attack;
};

class health_object
{
public:
	health_object(carama_info* carama)
	{
		this->_health_area.set_carama(carama);
		this->_health_base_point = NULL;
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
		this->_health_base_point = o;
	}
	void setHealthArea(object* o, coord off_coo, int w, int h)
	{
		this->_health_area.init(
			o->get_base_area()->get_coord_base(), off_coo, w, h);
		this->_health_base_point = o;
	}

	object* _health_base_point;

protected:
	world_area _health_area;
};

class ground_check_object
{
public:
	ground_check_object(carama_info* carama)
	{
		this->_ground_check_area.set_carama(carama);
		this->_ground_check_base_point = NULL;
	}
	~ground_check_object()
	{
	}
	world_area* get_ground_check_area() {
		return &this->_ground_check_area;
	};

	void setGroundCheckArea(object* o)
	{
		this->_ground_check_area.init(
			o->get_base_area()->get_coord_base(),
			coord(o->get_base_area()->get_width() / 4, o->get_base_area()->get_height()), o->get_base_area()->get_width() / 2, 10);
		this->_ground_check_base_point = o;
	}
	void setGroundCheckArea(object* o, coord off_coo, int w, int h)
	{
		this->_ground_check_area.init(
			o->get_base_area()->get_coord_base(), off_coo, w, h);
		this->_ground_check_base_point = o;
	}

	object* _ground_check_base_point;
protected:
	world_area _ground_check_area;
};

// ----------------------------------------

class animator_
{
public:
	virtual void animator() {};
};

class other_event_
{
public:
	virtual void other_event() {};
};

// ----------------------------------------

class static_collsion_object : public static_object,
	public collsion_object
{
public:
	static_collsion_object(carama_info* carama) :
		static_object(carama),
		collsion_object(carama)
	{}
};

class dynamic_collsion_object : public dynamic_object,
	public collsion_object,
	public ground_check_object
{
public:
	dynamic_collsion_object(carama_info* carama) :
		dynamic_object(carama),
		collsion_object(carama),
		ground_check_object(carama)
	{}
};

// ----------------------------------------

class block : public static_collsion_object, public render_object
{
public:
	block(carama_info* carama) :
		static_collsion_object(carama),
		render_object(carama)
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

	virtual void render() override;
};

class sprite_object : public dynamic_collsion_object,
	public render_object,
	public hit_object,
	public animator_,
	public other_event_
{
public:
	sprite_object(carama_info* carama) :
		dynamic_collsion_object(carama),
		render_object(carama),
		hit_object(carama)
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
	public attack_object,
	public health_object
{
public:
	enemy(carama_info* carama) :
		sprite_object(carama),
		attack_object(carama),
		health_object(carama)
	{}
};


#endif
