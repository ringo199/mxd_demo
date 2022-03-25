
#ifndef __GAME_SCENE_BASE_H__
#define __GAME_SCENE_BASE_H__

#include "../scene_base.h"
#include "../../gameManager.h"
#include "../../event_manager.h"

class game_scene_base : public scene_base
{
public:
    game_scene_base();
    ~game_scene_base();
};

typedef game_scene_base game_scene;

class game_1 : public game_scene_base
{
public:
    game_1();
    ~game_1();

    virtual void init() override final;
    virtual void show() override final;
    virtual void hide() override final;
    virtual void clear() override final;

    virtual void beforeEvent() override final;
    virtual void render() override final;
    virtual void afterEvent() override final;

private:
    player_info* _player;

    IMAGE imgBG;
    old_enemy* _enemy;
    block* _blockList;
};

class game_2 : public game_scene_base
{
public:
    game_2();
    ~game_2();

    virtual void init() override final;
    virtual void show() override final;
    virtual void hide() override final;
    virtual void clear() override final;

    virtual void beforeEvent() override final;
    virtual void render() override final;
    virtual void afterEvent() override final;

private:
    player_info* _player;

    IMAGE imgBG;
    old_enemy* _enemy;
    block* _blockList;
};

#endif
