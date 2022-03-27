
#include "ui_manager.h"


UIManager::UIManager()
{
    static ui_loading loading;
    this->_loadingScene = &loading;
    this->_is_loading = false;
}

UIManager::~UIManager()
{
}

void UIManager::eventRegister(event_manager* event_manager)
{
    event_manager->eventRegister(UI_NEXT, (long)&this->nextScene, this);
    event_manager->eventRegister(UI_BACK, (long)&this->backScene, this);
    event_manager->eventRegister(UI_BACKHOME, (long)&this->backHomeScene, this);
    event_manager->eventRegister(UI_BEGIN_LOADING, (long)&this->beginLoading, this);
    event_manager->eventRegister(UI_END_LOADING, (long)&this->endLoading, this);
}

void UIManager::nextScene(void* ctx)
{
    UIManager* context = (UIManager*)ctx;
    int cur_size = context->_scene_types.size();
    if (cur_size == UI_COUNT)
    {
        printf("is top!!\n");
        return;
    }

    printf("%d\n", cur_size);
    e_scene_type next_type = (e_scene_type)cur_size;

    if (cur_size > 0)
    {
        context->hideScene();
    }
    context->_loadingScene->show();
    context->_is_loading = true;
    context->loadScene(next_type);
    context->_scene_types.push(next_type);
    context->_loadingScene->hide();
    context->_is_loading = false;
    context->showScene();
}

void UIManager::backScene(void* ctx)
{
    UIManager* context = (UIManager*)ctx;
    if (context->_scene_types.size() < 2)
    {
        printf("is home!!\n");
        return;
    }

    context->_loadingScene->show();
    context->_is_loading = true;
    context->hideScene();
    context->clearScene();
    context->showScene();
    context->_is_loading = false;
    context->_loadingScene->hide();
}

void UIManager::backHomeScene(void* ctx)
{
    UIManager* context = (UIManager*)ctx;
    if (context->_scene_types.size() < 2)
    {
        printf("is home!!\n");
        return;
    }

    context->_loadingScene->show();
    context->_is_loading = true;
    for (int i = context->_scene_types.size() - 1; i > 0; i--)
    {
        context->hideScene((e_scene_type)i);
    }

    context->_sceneMap[(e_scene_type)0]->show();
    context->_is_loading = false;
    context->_loadingScene->hide();
    for (;;)
    {
        if (context->_scene_types.size() == 1)
        {
            break;
        }

        context->clearScene();
    }
}

void UIManager::beginLoading(void* ctx)
{
    UIManager* context = (UIManager*)ctx;
    context->_loadingScene->show();
    context->_is_loading = true;
}

void UIManager::endLoading(void* ctx)
{
    UIManager* context = (UIManager*)ctx;
    context->_is_loading = false;
    context->_loadingScene->hide();
}

void UIManager::loadScene(e_scene_type type)
{
    switch (type)
    {
    case CHECK_MASTER_SERVER:
        _sceneMap[type] = new ui_check_master_server;
        break;
    case LOGIN:
        _sceneMap[type] = new ui_login;
        break;
    case CHECK_SLAVE_SERVER:
        _sceneMap[type] = new ui_check_slave_server;
        break;
    case CHECK_PLAYER:
        _sceneMap[type] = new ui_check_player;
        break;
    case GAME:
        _sceneMap[type] = new ui_game;
        break;
    default:
        break;
    }
    _sceneMap[type]->init();
}

void UIManager::showScene(e_scene_type type)
{
    this->_sceneMap[type]->show();
}

void UIManager::hideScene(e_scene_type type)
{
    this->_sceneMap[type]->hide();
}

void UIManager::showScene()
{
    this->_sceneMap[this->_scene_types.top()]->show();
}

void UIManager::hideScene()
{
    this->_sceneMap[this->_scene_types.top()]->hide();
}

void UIManager::clearScene()
{
    this->_sceneMap[this->_scene_types.top()]->clear();
    delete this->_sceneMap[this->_scene_types.top()];
    this->_sceneMap[this->_scene_types.top()] = NULL;

    this->_scene_types.pop();
}


ui_scene* UIManager::getScene()
{
    if (this->_is_loading)
    {
        return _loadingScene;
    }
    else
    {
        return this->_sceneMap[this->_scene_types.top()];
    }
}
