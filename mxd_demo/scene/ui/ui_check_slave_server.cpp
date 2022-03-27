
#include "ui_scene_base.h"
#include "../../tools.h"

#include "../../global.h"

using namespace global;

ui_check_slave_server::ui_check_slave_server()
{
}

ui_check_slave_server::~ui_check_slave_server()
{
}

void ui_check_slave_server::init()
{
    Sleep(300);
}

void ui_check_slave_server::show()
{
    board* b = new board;
    b->init(0, 0, getwidth(), getheight());
    b->setResType(RES_UI_BG3);
    b->loadRenderImage();
    GetUIObjectManager()->push_object(b);

    label* l = new label;
    l->color = WHITE;
    l->fontSize = 50;
    l->txt = "请选择子服务器";
    l->init(getwidth() / 2 - 250, 100, 500, 100);

    button* btn1 = new button;
    btn1->init(getwidth() / 2 - 150, getheight() / 2 - 50, 100, 100);
    btn1->addEventListener(UI_BACK);
    btn1->btntxt = "上一步";
    btn1->setResType(RES_UI_BTN_);
    btn1->loadRenderImage();
    button* btn2 = new button;
    btn2->init(getwidth() / 2 + 50, getheight() / 2 - 50, 100, 100);
    btn2->addEventListener(UI_NEXT);
    btn2->btntxt = "下一步";
    btn2->setResType(RES_UI_BTN_);
    btn2->loadRenderImage();
    GetUIObjectManager()->push_object(l);
    GetUIObjectManager()->push_object(btn1);
    GetUIObjectManager()->push_object(btn2);
}

void ui_check_slave_server::hide()
{
    GetUIObjectManager()->clear_objects();
}

void ui_check_slave_server::clear()
{
}

void ui_check_slave_server::beforeEvent()
{
}

void ui_check_slave_server::render()
{
    GetUIObjectManager()->render();
}

void ui_check_slave_server::afterEvent()
{
}