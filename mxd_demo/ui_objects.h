#pragma once

#ifndef __UI_OBJECTS_H__
#define __UI_OBJECTS_H__

#include "var.h"
#include <functional>
#include <string>
#include <vector>

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
		this->_res_str_path = "";
		this->_is_fixed = true;
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

	void setResType(e_res_type res_type) { this->_res_type = res_type; this->_is_fixed = true; }
	void setResStringPath(std::string res_str_path) { this->_res_str_path = res_str_path; this->_is_fixed = false; }

	ui_object* _render_base_point;

protected:
	area _render_area;
	bool _is_fixed;
	e_res_type _res_type;
	std::string _res_str_path;
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

	void addEventListener(std::function<void(void)> func)
	{
		this->_eventListenerFunc = func;
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
	std::function<void(void)> _eventListenerFunc;
	e_event_type _event_type;

	bool _is_event_mgr = false; // 是否为eventManager绑定的事件
};


// ---------------------------

class image : public ui_object, public ui_render_object
{
public:
	image() : ui_object(), ui_render_object() {}
	~image() {}

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

	bool isShow = true;
};

class button : public ui_object, public ui_render_object, public ui_click_event_object
{
public:
	button() : ui_object(), ui_render_object(), ui_click_event_object()
	{
		this->btntxt = "";
		this->font_size = 25;
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

	bool isShow = true;
	int font_size;
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
		this->isShow = true;
		this->_draw_text_type = DRAW_TEXT_SINGLE_LEFT;
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
	std::string txt;
	int fontSize;
	int color;
	bool isShow;
	e_draw_text_type _draw_text_type;
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

class input : public ui_object, public ui_render_object, public ui_click_event_object
{
public:
	input();
	~input() {}

	enum class INPUT_TYPE
	{
		TEXT,
		PASSWORD
	};

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

	virtual void render() override;

	int lineWidth;
	int boardColor;
	int focusColor;
	int emptyColor;
	int color;
	int fontSize;
	INPUT_TYPE type;
	std::string txt;
};

class discussion : public ui_object, public ui_render_object
{
public:
	discussion() : ui_object(), ui_render_object()
	{
		this->lineWidth = 3;
		this->boardColor = 0xAAAAAA;
		this->emptyColor = 0xAAAAAA;
		this->color = 0;
		this->fontSize = 0;
		this->txtsize = 5;
	}
	~discussion() {}

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
	void pushTxt(std::string txt);

	int lineWidth;
	int boardColor;
	int emptyColor;
	int color;
	int fontSize;

	int txtsize;

private:
	void adjust();

	std::string showtxt;
	std::vector<std::string> txtList;
};

class dialog : public ui_object, public ui_render_object
{
public:
	dialog() : ui_object(), ui_render_object()
	{
		this->lineWidth = 3;
		this->boardColor = 0xAAAAAA;
		this->emptyColor = 0xAAAAAA;
		this->color = 0;
		this->fontSize = 0;
		this->txtsize = 5;
		this->_is_show = false;
		this->contentTimerId = -1;
	}
	~dialog() {}

	void init(coord coo, int w, int h);
	void init(int x, int y, int w, int h);

	virtual void render() override;

	void openDialog(std::string name, e_res_type resType, std::string content);
	void openDialog(std::string name, std::string resPath, std::string content);
	void openDialog(std::string name, std::string resPath, int _dialogID);

	void eventRegister();
	static void getDialogContent(void*, std::string data);

	void closeDialog();
	void nextDialog();

	int lineWidth;
	int boardColor;
	int emptyColor;
	int color;
	int fontSize;

	int txtsize;

	button* _close_btn;
	button* _next_btn;
	button* _ok_btn;
	button* _yes_btn;
	button* _no_btn;
	label* _name;
	label* _content;
	image* _img;

	std::string str;
private:
	bool _is_show;
	int strindex;
	int contentTimerId;
	int dialogID;
	int nextID;
};

#endif // !__UI_OBJECTS_H__
