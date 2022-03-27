
#include "ui_objects.h"

#include "global.h"
#include "tools.h"

using namespace global;

ui_object::ui_object()
{
	this->_base_point = this;
}

ui_object::~ui_object()
{
}

void ui_render_object::loadRenderImage()
{
	if (this->_res_type != RES_NULL)
	{
		GetLoadManager()->LoadAsset(this->_res_type, this->get_render_area());
	}
}

void ui_render_object::renderImage()
{
	if (this->_res_type != RES_NULL)
	{
		putimagePNG2(this->get_render_area()->get_coord1()->x, this->get_render_area()->get_coord1()->y,
			GetLoadManager()->LoadAsset(this->_res_type, this->get_render_area())->img);
	}
}

void ui_click_event_object::callEventListener()
{
	if (this->_is_event_mgr)
	{
		GetEventManager()->eventEmit(this->_event_type);
	}
	else
	{
		typedef void* (*FUNC)(void*);
		((FUNC)this->_eventListener)(NULL);
	}
}

void button::renderChild()
{
	drawText(this->get_render_area(), this->btntxt, 25, BLACK);
}

void label::render()
{
	//drawBloodBar(this->get_render_area(), 5, BLACK, BLACK, BLACK, 1.0);
	drawText(this->get_render_area(), this->txt, this->fontSize, this->color);
}

void progress::render()
{
	drawBloodBar(this->get_render_area(),
		this->lineWidth, this->boardColor, this->emptyColor, this->fillColor, this->percent);
}
