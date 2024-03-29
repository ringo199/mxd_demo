
#ifndef __UI_MANAGER_H__
#define __UI_MANAGER_H__

#include <iostream>
#include <stack>
#include <unordered_map>
#include "scene/ui_scene.h"

using namespace std;

class UIManager
{
public:
    UIManager();
    ~UIManager();

    static void nextScene(void*);
    static void backScene(void*);
    static void backHomeScene(void*);
    static void beginLoading(void*);
    static void endLoading(void*);
    void eventRegister(event_manager*);

    ui_scene* getScene();
    ui_game* getUIGame();
    bool getIsLoading();

private:
    ui_scene*                               _loadingScene;
    stack<e_scene_type>                     _scene_types;
    unordered_map<e_scene_type, ui_scene*>  _sceneMap;

    void loadScene(e_scene_type type);

    void showScene(e_scene_type type);
    void hideScene(e_scene_type type);
    void showScene();
    void hideScene();

    void clearScene();

    bool _is_loading;
};

#endif
