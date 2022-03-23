
#include "ui_scene_base.h"
#include "../../tools.h"

ui_game::ui_game(event_manager* event_manager)
    :ui_scene_base(event_manager)
{
    this->gameSceneManager = NULL;
}

ui_game::~ui_game()
{
}

void ui_game::init()
{
    this->gameSceneManager = new GameSceneManager;
    this->gameSceneManager->eventRegister(this->_event_manager);
    this->_event_manager->eventEmit(GAME_GOTO_SCENE, GAME_1);
}

void ui_game::show()
{
}

void ui_game::hide()
{
    this->gameSceneManager->getGameScene()->hide();
}

void ui_game::clear()
{
    this->gameSceneManager->getGameScene()->clear();
    delete this->gameSceneManager;
    this->gameSceneManager = NULL;
}

void ui_game::beforeEvent()
{
    this->gameSceneManager->getGameScene()->beforeEvent();
}

void ui_game::render()
{
    this->gameSceneManager->getGameScene()->render();
}

void ui_game::afterEvent()
{
    this->gameSceneManager->getGameScene()->afterEvent();
}
