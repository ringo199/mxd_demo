
#include "game_scene_base.h"


game_scene_base::game_scene_base(event_manager* eventManager, gameManager* game_manager)
{
	this->_event_manager = eventManager;
	this->_gameManager = game_manager;
}

game_scene_base::~game_scene_base()
{
}
