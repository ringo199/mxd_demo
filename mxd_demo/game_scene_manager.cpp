
#include "game_scene_manager.h"

#include "global.h"

using namespace global;

GameSceneManager::GameSceneManager()
{
    this->_cur_game_scene_type = GAME_SCENE_NULL;
    this->_sceneMap = new map<e_game_scene_type, game_scene*>;
}

GameSceneManager::~GameSceneManager()
{
    this->clearScene();
}

void GameSceneManager::gotoScene(void* ctx, e_game_scene_type type)
{
    GameSceneManager *context = (GameSceneManager*)ctx;

    GetEventManager()->eventEmit(UI_BEGIN_LOADING);

    if (context->_cur_game_scene_type != GAME_SCENE_NULL)
    {
        context->hideScene();
    }

    context->loadScene(type);
    context->showScene(type);

    GetEventManager()->eventEmit(UI_END_LOADING);
}

void GameSceneManager::eventRegister()
{
    GetEventManager()->eventRegister(GAME_GOTO_SCENE, (long)&this->gotoScene, this);
}

void GameSceneManager::clearEventRegister()
{
    GetEventManager()->clearEvent(GAME_GOTO_SCENE);
}

void GameSceneManager::clearScene()
{
    this->clearEventRegister();

    if (this->_sceneMap != NULL)
    {
        map<e_game_scene_type, game_scene*>::iterator iter;
        for (iter = this->_sceneMap->begin(); iter != this->_sceneMap->end();)
        {
            iter->second->clear();
            delete iter->second;
            this->_sceneMap->erase(iter++);
        }
        this->_sceneMap->clear();
        //map<e_game_scene_type, game_scene*>().swap(*this->_sceneMap);
        //this->_sceneMap = NULL;
    }

    this->_cur_game_scene_type = GAME_SCENE_NULL;
}

game_scene* GameSceneManager::getGameScene()
{
    return (*this->_sceneMap)[this->_cur_game_scene_type];
}

void GameSceneManager::loadScene(e_game_scene_type type)
{
    if ((*this->_sceneMap)[type] != NULL) return;

    switch (type)
    {
    case GAME_1:
        (*this->_sceneMap)[type] = new game_1;
        break;
    case GAME_2:
        (*this->_sceneMap)[type] = new game_2;
        break;
    default:
        break;
    }

    (*this->_sceneMap)[type]->init();
}

void GameSceneManager::showScene(e_game_scene_type type)
{
    this->_cur_game_scene_type = type;
    (*this->_sceneMap)[type]->show();
}

void GameSceneManager::hideScene()
{
    (*this->_sceneMap)[_cur_game_scene_type]->hide();
}
