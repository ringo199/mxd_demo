
#include "ui_objectManager.h"
#include "tools.h"

UIObjectManager::UIObjectManager()
{
}

UIObjectManager::~UIObjectManager()
{
}

void UIObjectManager::beforeEvent()
{
}

void UIObjectManager::render()
{
	for (int i = 0; i < this->_ui_render_objects.size(); ++i)
	{
		this->_ui_render_objects[i]->render();
	}
}

void UIObjectManager::afterEvent()
{
}

void UIObjectManager::clear_objects()
{
	vector<ui_render_object*>().swap(this->_ui_render_objects);
	vector<ui_click_event_object*>().swap(this->_ui_click_event_objects);
}

void UIObjectManager::checkClickEvent(coord* coo)
{
	for (int i = 0; i < this->_ui_click_event_objects.size(); ++i)
	{
		if (isCoordInRect(coo, this->_ui_click_event_objects[i]->get_click_event_area()))
		{
			this->_ui_click_event_objects[i]->callEventListener();
		}
	}
}
