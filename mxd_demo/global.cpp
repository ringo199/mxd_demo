
#include "global.h"

static bool s_update = false;

static event_manager	*s_event_manager 		= NULL;
static UIManager		*s_ui_manager 			= NULL;
static gameManager		*s_game_manager 		= NULL;
static GameSceneManager	*s_game_scene_manager 	= NULL;

bool GetUpdate()
{
	return s_update;
}

void ChangeUpdate(bool update)
{
	s_update = update;
}

event_manager* GetEventManager()
{
	if (s_event_manager == NULL)
	{
		s_event_manager = new event_manager;
	}
	
	return s_event_manager;
}

UIManager* GetUIManager()
{
	if (s_ui_manager == NULL)
	{
		s_ui_manager = new UIManager;
	}
	
	return s_ui_manager;
}

gameManager* GetGameManager()
{
	if (s_game_manager == NULL)
	{
		s_game_manager = new gameManager;
	}

	return s_game_manager;
}

GameSceneManager* GetGameSceneManager()
{
	if (s_game_scene_manager == NULL)
	{
		s_game_scene_manager = new GameSceneManager;
	}

	return s_game_scene_manager;
}

