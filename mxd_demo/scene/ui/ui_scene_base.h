
#ifndef __UI_SCENE_BASE_H__
#define __UI_SCENE_BASE_H__

#include "../scene_base.h"
#include "../../game_scene_manager.h"
#include "../../ui_objects.h"

class ui_scene_base : public scene_base
{
public:
    ui_scene_base();
    ~ui_scene_base();
};

typedef ui_scene_base ui_scene;

class ui_check_master_server : public ui_scene_base
{
public:
    ui_check_master_server();
    ~ui_check_master_server();

    virtual void init() override final;
    virtual void show() override final;
    virtual void hide() override final;
    virtual void clear() override final;

    virtual void beforeEvent() override final;
    virtual void render() override final;
    virtual void afterEvent() override final;

    void eventRegister();
    static void setServerList(void *, string);

protected:
private:
    vector<pair<int, string>> _server_list;
};

class ui_login : public ui_scene_base
{
public:
    ui_login();
    ~ui_login();

    virtual void init() override final;
    virtual void show() override final;
    virtual void hide() override final;
    virtual void clear() override final;

    virtual void beforeEvent() override final;
    virtual void render() override final;
    virtual void afterEvent() override final;

    void eventRegister();
    static void setLoginSuccess(void *, string);
    static void setLoginFailMessage(void *, string);

protected:
private:
};

class ui_check_player : public ui_scene_base
{
public:
    ui_check_player();
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
    ui_check_slave_server();
    ~ui_check_slave_server();

    virtual void init() override final;
    virtual void show() override final;
    virtual void hide() override final;
    virtual void clear() override final;

    virtual void beforeEvent() override final;
    virtual void render() override final;
    virtual void afterEvent() override final;

    void eventRegister();
    static void setSubServerList(void *, string);

protected:
private:
};

class ui_game : public ui_scene_base
{
public:
    ui_game();
    ~ui_game();

    virtual void init() override final;
    virtual void show() override final;
    virtual void hide() override final;
    virtual void clear() override final;

    virtual void beforeEvent() override final;
    virtual void render() override final;
    virtual void afterEvent() override final;

    void eventRegister();
    static void setDiscussTxt(void *, string msg);

    dialog *dia;

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
    board *_ui_loading_board;
};

#endif
