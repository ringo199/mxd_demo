
#ifndef __GAME_SCENE_MANAGER_H__
#define __GAME_SCENE_MANAGER_H__

#include <stdio.h>
#include <unordered_map>
#include "scene/game_scene.h"
#include "event_manager.h"
#include "objectManager.h"
#include <malloc.h>

using namespace std;

class GameSceneManager
{
public:
    GameSceneManager();
    ~GameSceneManager();

    static void gotoScene(void*, int gameMapID);
    static void loadingScene(void*, string data);

    void eventRegister();
    void clearEventRegister();

    void clearScene();

    game_scene* getGameScene();

private:
    e_game_scene_type                     _cur_game_scene_type;
    unordered_map<e_game_scene_type, game_scene*>*  _sceneMap;

    void loadScene(e_game_scene_type type);
    void showScene(e_game_scene_type type);
    void hideScene();
};

#endif
