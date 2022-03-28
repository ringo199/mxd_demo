#pragma once

#ifndef __UI_OBJECT_MANAGER_H__
#define __UI_OBJECT_MANAGER_H__

#include "ui_objects.h"
#include "tools.h"
#include <stdio.h>
#include <vector>

using namespace std;

class UIObjectManager
{
public:
	UIObjectManager();
	~UIObjectManager();

	void beforeEvent();
	void render();
	void afterEvent();

	template <typename T>
	void push_object(T* obj)
	{
		ui_render_object* ui_render_obj = dynamic_cast<ui_render_object*>(obj);
		if (ui_render_obj != NULL)
		{
			this->_ui_render_objects.push_back(ui_render_obj);
		}

		ui_click_event_object* ui_click_event_obj = dynamic_cast<ui_click_event_object*>(obj);
		if (ui_click_event_obj != NULL)
		{
			this->_ui_click_event_objects.push_back(ui_click_event_obj);
		}

		this->_ui_objects.push_back(obj);
	}

	template <typename T>
	void delete_object(T* obj)
	{
		ui_render_object* ui_render_obj = dynamic_cast<ui_render_object*>(obj);
		if (ui_render_obj != NULL)
		{
			for (int i = 0; i < this->_ui_render_objects.size(); ++i)
			{
				if (ui_render_obj->_render_base_point == this->_ui_render_objects[i]->_render_base_point)
				{
					this->_ui_render_objects.erase(this->_ui_render_objects.begin() + i);
					break;
				}
			}
		}

		ui_click_event_object* ui_click_event_obj = dynamic_cast<ui_click_event_object*>(obj);
		if (ui_click_event_obj != NULL)
		{
			for (int i = 0; i < this->_ui_click_event_objects.size(); ++i)
			{
				if (ui_click_event_obj->_click_event_base_point == this->_ui_click_event_objects[i]->_click_event_base_point)
				{
					this->_ui_click_event_objects.erase(this->_ui_click_event_objects.begin() + i);
					break;
				}
			}
		}

		for (int i = 0; i < this->_ui_objects.size(); ++i)
		{
			if (obj->_base_point == this->_ui_objects[i]->_base_point)
			{
				this->_ui_objects.erase(this->_ui_objects.begin() + i);
				break;
			}
		}
	}

	void clear_objects();

	void checkClickEvent(coord* coo);

private:
	vector<ui_render_object*> _ui_render_objects;
	vector<ui_click_event_object*> _ui_click_event_objects;
	vector<ui_object*> _ui_objects;

	//vector<ui_animator_*> _ui_animators;
	//void _animator();
};

#endif
