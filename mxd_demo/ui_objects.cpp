
#include "ui_objects.h"

#include "global.h"
#include "tools.h"

ui_object::ui_object()
{
	this->_base_point = this;
}

ui_object::~ui_object()
{
}


void ui_click_event_object::callEventListener()
{
	if (this->_is_event_mgr)
	{
		global::GetEventManager()->eventEmit(this->_event_type);
	}
	else
	{
		typedef void* (*FUNC)(void*);
		((FUNC)this->_eventListener)(NULL);
	}
}

void button::render()
{
	drawBloodBar(this->get_render_area(), 5, BLACK, WHITE, WHITE, 1.0);
}
