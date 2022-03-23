
#include "ui_scene_base.h"

ui_scene_base::ui_scene_base()
{
	this->_event_manager = NULL;
}

ui_scene_base::ui_scene_base(event_manager* event_manager)
{
	this->_event_manager = event_manager;
}

ui_scene_base::~ui_scene_base()
{
}
