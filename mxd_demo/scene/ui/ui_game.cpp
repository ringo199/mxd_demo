
#include "ui_scene_base.h"
#include "../../tools.h"
#include "../../global.h"

using namespace global;

ui_game::ui_game()
{
}

ui_game::~ui_game()
{
}

void ui_game::init()
{
    GetGameSceneManager()->eventRegister();
    GetEventManager()->eventEmit(GAME_GOTO_SCENE, GAME_1);
}

void ui_game::show()
{
}

void ui_game::hide()
{
}

void ui_game::clear()
{
    GetGameSceneManager()->clearScene();
}

void ui_game::beforeEvent()
{
    GetGameSceneManager()->getGameScene()->beforeEvent();
}

void ui_game::render()
{
    GetGameSceneManager()->getGameScene()->render();
}

void ui_game::afterEvent()
{
    GetGameSceneManager()->getGameScene()->afterEvent();
}
