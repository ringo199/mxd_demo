
#include "game_scene_manager.h"

#include "global.h"
#include "netEvent.h"
#include "cJSON.h"

using namespace global;

GameSceneManager::GameSceneManager()
{
    this->_cur_game_scene_type = GAME_SCENE_NULL;
    this->_sceneMap = new unordered_map<e_game_scene_type, game_scene*>;
}

GameSceneManager::~GameSceneManager()
{
    this->clearScene();
}

void GameSceneManager::gotoScene(void* ctx, int gameMapID)
{
    GameSceneManager *context = (GameSceneManager*)ctx;

    GetObjectManager()->clear_objects();
    GetObjectManager()->GetPlayer()->clearEventRegister();

    GetEventManager()->eventEmit(UI_BEGIN_LOADING);
    sendMessage_type_6(gameMapID);
    /**
    if (context->_cur_game_scene_type != GAME_SCENE_NULL)
    {
        context->hideScene();
    }

    context->loadScene(type);
    context->showScene(type);
    */
}

void GameSceneManager::loadingScene(void* ctx, string data)
{
    GameSceneManager* context = (GameSceneManager*)ctx;

    cJSON* gameMapData = cJSON_Parse(data.c_str());

    cJSON* gameMapID,
        *area_json,
        *area_json_w, *area_json_h,
        *background_json,
        *background_json_path,
        *background_json_num,

        *block_json,
        *block_json_row,
        *block_json_row_area,
        *block_json_row_area_x,
        *block_json_row_area_y,
        *block_json_row_area_w,
        *block_json_row_area_h,
        *block_json_row_img,
        *block_json_row_img_path,
        *block_json_row_img_num,

        * transpoint_json,
        * transpoint_json_row,
        * transpoint_json_row_to,
        * transpoint_json_row_area,
        * transpoint_json_row_area_x,
        * transpoint_json_row_area_y,
        * transpoint_json_row_area_w,
        * transpoint_json_row_area_h,
        * transpoint_json_row_img,
        * transpoint_json_row_img_path,
        * transpoint_json_row_img_num,

        * npc_json,
        * npc_json_row,
        * npc_json_row_area,
        * npc_json_row_area_x,
        * npc_json_row_area_y,
        * npc_json_row_area_w,
        * npc_json_row_area_h,
        * npc_json_row_img,
        * npc_json_row_img_path,
        * npc_json_row_img_num,
        * npc_json_row_name,
        * npc_json_row_dialogID,

        *point_json,
        *point_json_x,
        *point_json_y;

    gameMapID = cJSON_GetObjectItem(gameMapData, "gameMapID");

    GetSessionManager()->SetSession(SESSION_MAP_ID, gameMapID->valueint);

    area_json = cJSON_GetObjectItem(gameMapData, "area");
    area_json_w = cJSON_GetObjectItem(area_json, "w");
    area_json_h = cJSON_GetObjectItem(area_json, "h");

    area map(0, 0, area_json_w->valueint, area_json_h->valueint);
    GetCarama()->init(map.get_width(), map.get_height(), getwidth(), getheight());

    background_json = cJSON_GetObjectItem(gameMapData, "background");
    background_json_path = cJSON_GetObjectItem(background_json, "path");
    background_json_num = cJSON_GetObjectItem(background_json, "num");

    GetLoadManager()->AddAsset(
        background_json_path->valuestring, background_json_num->valueint);

    background* _bg = new background;
    _bg->init(0, 0, map.get_width(), map.get_height());
    _bg->setResStringPath(background_json_path->valuestring);
    _bg->loadRenderImage();
    GetObjectManager()->push_object(_bg);

    block_json = cJSON_GetObjectItem(gameMapData, "block");
    int block_size = cJSON_GetArraySize(block_json);
    if (block_size > 0)
    {
        block* _blockList = new block[block_size];

        for (int i = 0; i < block_size; ++i)
        {
            block_json_row = cJSON_GetArrayItem(block_json, i);
            block_json_row_area = cJSON_GetObjectItem(block_json_row, "area");
            block_json_row_area_x = cJSON_GetObjectItem(block_json_row_area, "x");
            block_json_row_area_y = cJSON_GetObjectItem(block_json_row_area, "y");
            block_json_row_area_w = cJSON_GetObjectItem(block_json_row_area, "w");
            block_json_row_area_h = cJSON_GetObjectItem(block_json_row_area, "h");

            block_json_row_img = cJSON_GetObjectItem(block_json_row, "img");
            block_json_row_img_path = cJSON_GetObjectItem(block_json_row_img, "path");
            block_json_row_img_num = cJSON_GetObjectItem(block_json_row_img, "num");

            GetLoadManager()->AddAsset(
                block_json_row_img_path->valuestring, block_json_row_img_num->valueint);

            _blockList[i].init(
                block_json_row_area_x->valueint,
                block_json_row_area_y->valueint,
                block_json_row_area_w->valueint,
                block_json_row_area_h->valueint);
            _blockList[i].setResStringPath(block_json_row_img_path->valuestring);
            _blockList[i].loadRenderImage();
            GetObjectManager()->push_object(&_blockList[i]);
        }
    }

    transpoint_json = cJSON_GetObjectItem(gameMapData, "transpoint");
    int transpoint_size = cJSON_GetArraySize(transpoint_json);
    if (transpoint_size > 0)
    {
        transpoint* _transpointList = new transpoint[transpoint_size];

        for (int i = 0; i < transpoint_size; ++i)
        {
            transpoint_json_row = cJSON_GetArrayItem(transpoint_json, i);
            transpoint_json_row_to = cJSON_GetObjectItem(transpoint_json_row, "to");
            transpoint_json_row_area = cJSON_GetObjectItem(transpoint_json_row, "area");
            transpoint_json_row_area_x = cJSON_GetObjectItem(transpoint_json_row_area, "x");
            transpoint_json_row_area_y = cJSON_GetObjectItem(transpoint_json_row_area, "y");
            transpoint_json_row_area_w = cJSON_GetObjectItem(transpoint_json_row_area, "w");
            transpoint_json_row_area_h = cJSON_GetObjectItem(transpoint_json_row_area, "h");

            transpoint_json_row_img = cJSON_GetObjectItem(transpoint_json_row, "img");
            transpoint_json_row_img_path = cJSON_GetObjectItem(transpoint_json_row_img, "path");
            transpoint_json_row_img_num = cJSON_GetObjectItem(transpoint_json_row_img, "num");

            GetLoadManager()->AddAsset(
                transpoint_json_row_img_path->valuestring, transpoint_json_row_img_num->valueint);

            _transpointList[i].init(
                transpoint_json_row_area_x->valueint,
                transpoint_json_row_area_y->valueint,
                transpoint_json_row_area_w->valueint,
                transpoint_json_row_area_h->valueint);
            _transpointList[i].setTranspointTo(transpoint_json_row_to->valueint);
            _transpointList[i].setResStringPath(transpoint_json_row_img_path->valuestring);
            _transpointList[i].loadRenderImage();
            GetObjectManager()->push_object(&_transpointList[i]);
        }
    }

    npc_json = cJSON_GetObjectItem(gameMapData, "npc");
    int npc_size = cJSON_GetArraySize(npc_json);
    if (npc_size > 0)
    {
        NPC* _npcList = new NPC[npc_size];

        for (int i = 0; i < npc_size; ++i)
        {
            npc_json_row = cJSON_GetArrayItem(npc_json, i);
            npc_json_row_area = cJSON_GetObjectItem(npc_json_row, "area");
            npc_json_row_area_x = cJSON_GetObjectItem(npc_json_row_area, "x");
            npc_json_row_area_y = cJSON_GetObjectItem(npc_json_row_area, "y");
            npc_json_row_area_w = cJSON_GetObjectItem(npc_json_row_area, "w");
            npc_json_row_area_h = cJSON_GetObjectItem(npc_json_row_area, "h");

            npc_json_row_img = cJSON_GetObjectItem(npc_json_row, "img");
            npc_json_row_img_path = cJSON_GetObjectItem(npc_json_row_img, "path");
            npc_json_row_img_num = cJSON_GetObjectItem(npc_json_row_img, "num");

            npc_json_row_name = cJSON_GetObjectItem(npc_json_row, "name");
            npc_json_row_dialogID = cJSON_GetObjectItem(npc_json_row, "dialogID");

            GetLoadManager()->AddAsset(
                npc_json_row_img_path->valuestring, npc_json_row_img_num->valueint);

            _npcList[i].init(
                npc_json_row_area_x->valueint,
                npc_json_row_area_y->valueint,
                npc_json_row_area_w->valueint,
                npc_json_row_area_h->valueint);

            _npcList[i].name = npc_json_row_name->valuestring;
            _npcList[i].setResStringPath(npc_json_row_img_path->valuestring);
            _npcList[i].loadRenderImage();

            _npcList[i].addEventListener([=]() {
                GetUIManager()->getUIGame()
                    ->dia->openDialog(_npcList[i].name,
                        npc_json_row_img_path->valuestring, npc_json_row_dialogID->valueint);
            });
            GetObjectManager()->push_object(&_npcList[i]);
        }
    }

    point_json = cJSON_GetObjectItem(gameMapData, "point");
    point_json_x = cJSON_GetObjectItem(point_json, "x");
    point_json_y = cJSON_GetObjectItem(point_json, "y");
    GetObjectManager()->GetPlayer()->init(
        point_json_x->valueint, point_json_y->valueint);

    GetCarama()->setCenterPoint(GetObjectManager()->GetPlayer()->get_base_area()->get_coord_base());
    GetObjectManager()->GetPlayer()->eventRegister();
    GetObjectManager()->push_object(GetObjectManager()->GetPlayer());

    cout << data << endl;

    GetEventManager()->eventEmit(UI_END_LOADING);
}

void GameSceneManager::eventRegister()
{
    GetEventManager()->eventRegister(GAME_GOTO_SCENE, (long)&this->gotoScene, this);
    GetEventManager()->eventRegister(NET_TYPE_6, (long)&this->loadingScene, this);
}

void GameSceneManager::clearEventRegister()
{
    GetEventManager()->clearEvent(GAME_GOTO_SCENE);
    GetEventManager()->clearEvent(GAME_LOADING_SCENE);
}

void GameSceneManager::clearScene()
{
    this->clearEventRegister();

    if (this->_sceneMap != NULL)
    {
        unordered_map<e_game_scene_type, game_scene*>::iterator iter;
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
