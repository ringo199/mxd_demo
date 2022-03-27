#pragma once

#ifndef __OBJECTS_H__
#define __OBJECTS_H__

#include "var.h"
#include "tools.h"
#include <map>

class object
{
public:
	object();
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

	object* _base_point;

protected:
	world_area _base_area;
};

class static_object : public object
{
public:
	static_object() : object() {}
};

class dynamic_object : public object
{
public:
	dynamic_object() : object() {}

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
	render_object();
	~render_object();
	world_area* get_render_area();

	virtual void render()
	{
		this->renderImage();
		this->renderChild();
	};
	virtual void renderChild() {}

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

	void loadRenderImage();
	void renderImage();

	void setResType(e_res_type res_type) { this->_res_type = res_type; }

	object* _render_base_point;

protected:
	world_area _render_area;
	e_res_type _res_type;
};

class collsion_object
{
public:
	collsion_object()
	{
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
	hit_object()
	{
		this->_is_hit = false;
		this->hit_time = 1500;
		this->_hit_cur_tick_count = getTickCount();
		this->_hit_base_point = NULL;
		this->_hit_type = ATK_OR_HIT_NULL;
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
	e_atk_or_hit_type _hit_type;

protected:
	world_area _hit_area;
	bool _is_hit;
	unsigned long long _hit_cur_tick_count;
};

class attack_object
{
public:
	attack_object()
	{
		this->_is_attack = false;
		this->_attack_base_point = NULL;
		this->_atk_type = ATK_OR_HIT_NULL;
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
	e_atk_or_hit_type _atk_type;

protected:
	world_area _attack_area;
	bool _is_attack;
};

class health_object
{
public:
	health_object()
	{
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
	ground_check_object()
	{
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

class transpoint_object
{
public:
	transpoint_object()
	{
		this->_transpoint_base_point = NULL;
		this->_game_scene = GAME_SCENE_NULL;
	}
	~transpoint_object()
	{
	}

	world_area* get_transpoint_area() {
		return &this->_transpoint_area;
	};

	void setTranspointArea(object* o)
	{
		this->_transpoint_area.init(
			o->get_base_area()->get_coord_base(),
			coord(0, 0), o->get_base_area()->get_width(), o->get_base_area()->get_height());
		this->_transpoint_base_point = o;
	}

	void setTranspoint(e_game_scene_type type)
	{
		this->_game_scene = type;
	}

	void trans();

	object* _transpoint_base_point;

	e_game_scene_type _game_scene;

protected:
	world_area _transpoint_area;
};

class click_event_object
{
public:
	click_event_object()
	{
		this->_click_event_base_point = NULL;
		this->_eventListener = 0;
	}
	~click_event_object()
	{
	}
	world_area* get_click_event_area() { return &this->_click_event_area; };

	void setClickEventArea(object* o)
	{
		this->_click_event_area.init(
			o->get_base_area()->get_coord_base(),
			coord(0, 0), o->get_base_area()->get_width(), o->get_base_area()->get_height());
		this->_click_event_base_point = o;
	}

	void addEventListener(long func)
	{
		this->_eventListener = func;
	}

	void callEventListener()
	{
		typedef void* (*FUNC)(void*);
		((FUNC)this->_eventListener)(NULL);
	}

	object* _click_event_base_point;

protected:
	world_area _click_event_area;

	long _eventListener;
};

// ----------------------------------------

class animator_
{
public:
	virtual void animator() {};

	void setAnimator(object* o)
	{
		this->_animator_base_point = o;
	}

	object* _animator_base_point;
};

class other_event_
{
public:
	virtual void other_event() {};

	void setOtherEvent(object* o)
	{
		this->_other_event_base_point = o;
	}

	object* _other_event_base_point;
};

class image_indexs_
{
public:
	int GetImageIndex(e_res_type);
	int ChangeImageIndex(e_res_type, int);
	int AddStepImageIndex(e_res_type);
	IMAGE* GetImage(e_res_type);

protected:
	std::map<e_res_type, int> _img_indexs;
};

// ----------------------------------------

class static_collsion_object : public static_object,
	public collsion_object
{
public:
	static_collsion_object() :
		static_object(),
		collsion_object()
	{}
};

class dynamic_collsion_object : public dynamic_object,
	public collsion_object,
	public ground_check_object
{
public:
	dynamic_collsion_object() :
		dynamic_object(),
		collsion_object(),
		ground_check_object()
	{}
};

// ----------------------------------------

class background : public static_object, public render_object
{
public:
	background():
		static_object(),
		render_object()
	{}

	void init(int x, int y, int w, int h)
	{
		this->initObject(x, y, w, h);
		this->setRenderArea(this);
	}

	void init(coord coo, int w, int h)
	{
		this->initObject(coo, w, h);
		this->setRenderArea(this);
	}
};

class block : public static_collsion_object, public render_object
{
public:
	block() :
		static_collsion_object(),
		render_object()
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

class transpoint : public static_object,
					public render_object,
					public transpoint_object
{
public:
	transpoint() :
		static_object(),
		render_object(),
		transpoint_object()
	{
	}

	void init(int x, int y, int w, int h)
	{
		this->initObject(x, y, w, h);
		this->setRenderArea(this);
		this->setTranspointArea(this);
	}

	void init(coord coo, int w, int h)
	{
		this->initObject(coo, w, h);
		this->setRenderArea(this);
		this->setTranspointArea(this);
	}
};

class sprite_object : public dynamic_collsion_object,
	public render_object,
	public hit_object,
	public animator_,
	public other_event_,
	public image_indexs_
{
public:
	sprite_object() :
		dynamic_collsion_object(),
		render_object(),
		hit_object()
	{}
};

class player : public sprite_object,
	public attack_object
{
public:
	player() :
		sprite_object(),
		attack_object()
	{
		this->_atk_type = PLAYER;
		this->_hit_type = PLAYER;
	}
};

class enemy : public sprite_object,
	public attack_object,
	public health_object
{
public:
	enemy() :
		sprite_object(),
		attack_object(),
		health_object()
	{
		this->_atk_type = ENEMY;
		this->_hit_type = ENEMY;
	}
};

class NPC : public render_object,
	public dynamic_object,
	public click_event_object
{
public:
	NPC() : render_object(), dynamic_object(), click_event_object()
	{}

	void init(coord coo, int w, int h)
	{
		this->initObject(coo, w, h);
		this->setRenderArea(this);
		this->setClickEventArea(this);
	}

	void init(int x, int y, int w, int h)
	{
		this->initObject(x, y, w, h);
		this->setRenderArea(this);
		this->setClickEventArea(this);
	}
};


#endif
