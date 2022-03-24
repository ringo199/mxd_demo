#pragma once
#ifndef __GLOBAL_H__
#define __GLOBAL_H__

#include "ui_manager.h"
#include "gameManager.h"
#include "game_scene_manager.h"
#include "event_manager.h"

namespace global
{
	bool GetUpdate();
	void ChangeUpdate(bool update);
	event_manager* GetEventManager();
	UIManager* GetUIManager();
	gameManager* GetGameManager();
	GameSceneManager* GetGameSceneManager();
}

#endif
