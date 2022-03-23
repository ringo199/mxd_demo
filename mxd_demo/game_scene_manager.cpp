
#include "game_scene_manager.h"

GameSceneManager::GameSceneManager()
{
    this->_cur_game_scene_type = GAME_SCENE_NULL;
    this->_event_manager = NULL;
    this->_gameManager = new gameManager;
    this->_sceneMap = new map<e_game_scene_type, game_scene*>;
}

GameSceneManager::~GameSceneManager()
{
    this->clearEventRegister();
    this->_cur_game_scene_type = GAME_SCENE_NULL;
    this->_event_manager = NULL;
    delete this->_gameManager;
    this->_gameManager = NULL;

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
        map<e_game_scene_type, game_scene*>().swap(*this->_sceneMap);
        this->_sceneMap = NULL;
    }
}

void GameSceneManager::gotoScene(void* ctx, e_game_scene_type type)
{
    GameSceneManager *context = (GameSceneManager*)ctx;

    if (context->_cur_game_scene_type != GAME_SCENE_NULL)
    {
        context->hideScene();
    }

    context->loadScene(type);
    context->showScene(type);
}

void GameSceneManager::eventRegister(event_manager* event_manager)
{
    this->_event_manager = event_manager;
    event_manager->eventRegister(GAME_GOTO_SCENE, (long)&this->gotoScene, this);
}

void GameSceneManager::clearEventRegister()
{
    this->_event_manager->clearEvent(GAME_GOTO_SCENE);
}

game_scene* GameSceneManager::getGameScene()
{
    return (*this->_sceneMap)[this->_cur_game_scene_type];
}

void GameSceneManager::loadScene(e_game_scene_type type)
{
    if ((*this->_sceneMap)[type] != NULL) return;

    this->_event_manager->eventEmit(UI_BEGIN_LOADING);

    switch (type)
    {
    case GAME_1:
        (*this->_sceneMap)[type] = new game_1(this->_event_manager, this->_gameManager);
        break;
    case GAME_2:
        (*this->_sceneMap)[type] = new game_2(this->_event_manager, this->_gameManager);
        break;
    default:
        break;
    }

    (*this->_sceneMap)[type]->init();
    this->_event_manager->eventEmit(UI_END_LOADING);
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
