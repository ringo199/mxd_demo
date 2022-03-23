#pragma once
#ifndef __GLOBAL_H__
#define __GLOBAL_H__

#include "carama.h"
#include "player.h"
#include "enemy.h"
#include "gameManager.h"
#include "var.h"
#include "event_manager.h"
#include "ui_manager.h"

class global
{
public:
	global();
	~global();

	void init(UIManager* uiManager, event_manager* eventManager);

	UIManager*		uiManager;
	event_manager*	eventManager;

	bool*			update;

private:

};


#endif
