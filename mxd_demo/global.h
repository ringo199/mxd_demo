#pragma once
#ifndef __GLOBAL_H__
#define __GLOBAL_H__

#include "ui_manager.h"
#include "objectManager.h"
#include "game_scene_manager.h"
#include "event_manager.h"
#include "carama.h"
#include "collision.h"
#include "ui_objectManager.h"

namespace global
{
	bool GetUpdate();
	void ChangeUpdate(bool update);
	event_manager *GetEventManager();
	UIManager *GetUIManager();
	objectManager *GetObjectManager();
	GameSceneManager *GetGameSceneManager();
	carama_info *GetCarama();
	collision *GetCollision();
	UIObjectManager* GetUIObjectManager();
} // namespace global

#endif
