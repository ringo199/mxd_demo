
#include "global.h"

namespace global
{
	static bool s_update = false;

	static event_manager* s_event_manager = NULL;
	static UIManager *s_ui_manager = NULL;
	static objectManager *s_object_manager = NULL;
	static GameSceneManager *s_game_scene_manager = NULL;
	static carama_info *s_carama = NULL;
	static collision *s_collision = NULL;
	static UIObjectManager* s_ui_object_manager = NULL;
	static SessionManager* s_session_manager = NULL;
	static LoadManager* s_load_manager = NULL;

	bool GetUpdate()
	{
		return s_update;
	}

	void ChangeUpdate(bool update)
	{
		s_update = update;
	}

	event_manager *GetEventManager()
	{
		if (s_event_manager == NULL)
		{
			s_event_manager = new event_manager;
		}

		return s_event_manager;
	}

	UIManager *GetUIManager()
	{
		if (s_ui_manager == NULL)
		{
			s_ui_manager = new UIManager;
		}

		return s_ui_manager;
	}

	objectManager *GetObjectManager()
	{
		if (s_object_manager == NULL)
		{
			s_object_manager = new objectManager;
		}

		return s_object_manager;
	}

	GameSceneManager *GetGameSceneManager()
	{
		if (s_game_scene_manager == NULL)
		{
			s_game_scene_manager = new GameSceneManager;
		}

		return s_game_scene_manager;
	}

	carama_info *GetCarama()
	{
		if (s_carama == NULL)
		{
			s_carama = new carama_info;
		}

		return s_carama;
	}

	collision *GetCollision()
	{
		if (s_collision == NULL)
		{
			s_collision = new collision;
		}

		return s_collision;
	}
	UIObjectManager* GetUIObjectManager()
	{
		if (s_ui_object_manager == NULL)
		{
			s_ui_object_manager = new UIObjectManager;
		}

		return s_ui_object_manager;
	}
	SessionManager* GetSessionManager()
	{
		if (s_session_manager == NULL)
		{
			s_session_manager = new SessionManager;
		}

		return s_session_manager;
	}

	LoadManager* GetLoadManager()
	{
		if (s_load_manager == NULL)
		{
			s_load_manager = new LoadManager;
		}

		return s_load_manager;
	}

} // namespace global