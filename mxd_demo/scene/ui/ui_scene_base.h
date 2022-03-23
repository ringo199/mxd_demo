
#ifndef __UI_SCENE_BASE_H__
#define __UI_SCENE_BASE_H__

#include "../scene_base.h"
#include "../../game_scene_manager.h"
#include "../../event_manager.h"

class ui_scene_base : public scene_base
{
public:
    ui_scene_base();
    ui_scene_base(event_manager*);
    ~ui_scene_base();

protected:
    event_manager* _event_manager;
};

typedef ui_scene_base ui_scene;


class ui_check_master_server : public ui_scene_base
{
public:
    ui_check_master_server(event_manager*);
    ~ui_check_master_server();

    virtual void init() override final;
    virtual void show() override final;
    virtual void hide() override final;
    virtual void clear() override final;

    virtual void beforeEvent() override final;
    virtual void render() override final;
    virtual void afterEvent() override final;

protected:

private:
};

class ui_check_player : public ui_scene_base
{
public:
    ui_check_player(event_manager*);
    ~ui_check_player();

    virtual void init() override final;
    virtual void show() override final;
    virtual void hide() override final;
    virtual void clear() override final;

    virtual void beforeEvent() override final;
    virtual void render() override final;
    virtual void afterEvent() override final;

protected:

private:
};

class ui_check_slave_server : public ui_scene_base
{
public:
    ui_check_slave_server(event_manager*);
    ~ui_check_slave_server();

    virtual void init() override final;
    virtual void show() override final;
    virtual void hide() override final;
    virtual void clear() override final;

    virtual void beforeEvent() override final;
    virtual void render() override final;
    virtual void afterEvent() override final;

protected:

private:
};

class ui_game : public ui_scene_base
{
public:
    ui_game(event_manager*);
    ~ui_game();

    GameSceneManager* gameSceneManager;

    virtual void init() override final;
    virtual void show() override final;
    virtual void hide() override final;
    virtual void clear() override final;

    virtual void beforeEvent() override final;
    virtual void render() override final;
    virtual void afterEvent() override final;

private:

};

class ui_loading : public ui_scene_base
{
public:
    ui_loading();
    ~ui_loading();

    virtual void init() override final;
    virtual void show() override final;
    virtual void hide() override final;
    virtual void clear() override final;

    virtual void beforeEvent() override final;
    virtual void render() override final;
    virtual void afterEvent() override final;

protected:

private:
};

class ui_login : public ui_scene_base
{
public:
    ui_login(event_manager*);
    ~ui_login();

    virtual void init() override final;
    virtual void show() override final;
    virtual void hide() override final;
    virtual void clear() override final;

    virtual void beforeEvent() override final;
    virtual void render() override final;
    virtual void afterEvent() override final;

protected:

private:
};


#endif
