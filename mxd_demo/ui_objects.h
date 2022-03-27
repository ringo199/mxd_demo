#pragma once

#ifndef __UI_OBJECTS_H__
#define __UI_OBJECTS_H__

#include "var.h"

class ui_object
{
public:
	ui_object();
	~ui_object();

	area* get_base_area() { return &this->_base_area; };

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

	ui_object* _base_point;

protected:
	area _base_area;
private:

};

// ---------------------------

class ui_render_object
{
public:
	ui_render_object()
	{
		this->_render_base_point = NULL;
		this->_res_type = RES_NULL;
	}
	~ui_render_object()
	{
	}
	area* get_render_area() { return &this->_render_area; };

	virtual void render()
	{
		this->renderImage();
		this->renderChild();
	};
	virtual void renderChild() {}

	void setRenderArea(ui_object* o)
	{
		this->_render_area.init(
			o->get_base_area()->get_coord_base(),
			coord(0, 0), o->get_base_area()->get_width(), o->get_base_area()->get_height());
		this->_render_base_point = o;
	}
	void setRenderArea(ui_object* o, coord off_coo, int w, int h)
	{
		this->_render_area.init(
			o->get_base_area()->get_coord_base(), off_coo, w, h);
		this->_render_base_point = o;
	}

	void loadRenderImage();
	void renderImage();

	void setResType(e_res_type res_type) { this->_res_type = res_type; }

	ui_object* _render_base_point;

protected:
	area _render_area;
	e_res_type _res_type;
};

class ui_click_event_object
{
public:
	ui_click_event_object()
	{
		this->_click_event_base_point = NULL;
		this->_eventListener = 0;
	}
	~ui_click_event_object()
	{
	}
	area* get_click_event_area() { return &this->_click_event_area; };

	void setClickEventArea(ui_object* o)
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

	void addEventListener(e_event_type type)
	{
		this->_is_event_mgr = true;
		this->_event_type = type;
	}

	void callEventListener();

	ui_object* _click_event_base_point;

protected:
	area _click_event_area;

	long _eventListener;
	e_event_type _event_type;

	bool _is_event_mgr = false; // 是否为eventManager绑定的事件
};


// ---------------------------

class button : public ui_object, public ui_render_object, public ui_click_event_object
{
public:
	button() : ui_object(), ui_render_object(), ui_click_event_object()
	{
		this->btntxt = "";
	}
	~button() {}

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

	virtual void renderChild() override;

	const char* btntxt;
};

class board : public ui_object, public ui_render_object
{
public:
	board() : ui_object(), ui_render_object()
	{
	}
	~board() {}

	void init(coord coo, int w, int h)
	{
		this->initObject(coo, w, h);
		this->setRenderArea(this);
	}

	void init(int x, int y, int w, int h)
	{
		this->initObject(x, y, w, h);
		this->setRenderArea(this);
	}
};

class label : public ui_object, public ui_render_object
{
public:
	label() : ui_object(), ui_render_object()
	{
		this->txt = "";
		this->fontSize = 25;
		this->color = 0;
	}
	~label() {}

	void init(coord coo, int w, int h)
	{
		this->initObject(coo, w, h);
		this->setRenderArea(this);
	}

	void init(int x, int y, int w, int h)
	{
		this->initObject(x, y, w, h);
		this->setRenderArea(this);
	}

	virtual void render() override;
	const char* txt;
	int fontSize;
	int color;
};

class progress : public ui_object, public ui_render_object
{
public:
	progress() : ui_object(), ui_render_object()
	{
		this->lineWidth = 3;
		this->boardColor = 0;
		this->emptyColor = 0xAAAAAA;
		this->fillColor = 0;
		this->percent = 0.0;
	}
	~progress() {}

	void init(coord coo, int w, int h)
	{
		this->initObject(coo, w, h);
		this->setRenderArea(this);
	}

	void init(int x, int y, int w, int h)
	{
		this->initObject(x, y, w, h);
		this->setRenderArea(this);
	}

	virtual void render() override;

	int lineWidth;
	int boardColor;
	int emptyColor;
	int fillColor;
	float percent;
};

#endif // !__UI_OBJECTS_H__
