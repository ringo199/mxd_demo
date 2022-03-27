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
#include "session_manager.h"
#include "load_manager.h"

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
	SessionManager* GetSessionManager();
	LoadManager* GetLoadManager();
} // namespace global

#endif
