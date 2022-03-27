
#include "ui_scene_base.h"
#include "../../tools.h"
#include "../../var.h"
#include "../../global.h"

using namespace global;

ui_check_master_server::ui_check_master_server()
{
}

ui_check_master_server::~ui_check_master_server()
{
}

void ui_check_master_server::init()
{
}

void ui_check_master_server::show()
{
    board* b = new board;
    b->init(0, 0, getwidth(), getheight());
    b->setResType(RES_UI_BG1);
    b->loadRenderImage();
    GetUIObjectManager()->push_object(b);

    label* l = new label;
    l->color = WHITE;
    l->fontSize = 50;
    l->txt = "请选择大区";
    l->init(getwidth() / 2 - 250, 100, 500, 100);

    button* btn = new button;
    btn->init(getwidth() / 2 + 50, getheight() / 2 - 50, 100, 100);
    btn->addEventListener(UI_NEXT);
    btn->btntxt = "下一步";
    btn->setResType(RES_UI_BTN_);
    btn->loadRenderImage();
    GetUIObjectManager()->push_object(l);
    GetUIObjectManager()->push_object(btn);
}

void ui_check_master_server::hide()
{
    GetUIObjectManager()->clear_objects();
}

void ui_check_master_server::clear()
{
}

void ui_check_master_server::beforeEvent()
{
}

void ui_check_master_server::render()
{
    GetUIObjectManager()->render();
}

void ui_check_master_server::afterEvent()
{
}