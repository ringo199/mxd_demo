
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
    button* btn = new button;
    btn->init(getwidth() / 2 + 50, getheight() / 2 - 50, 100, 100);
    btn->addEventListener(UI_NEXT);
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
    static area a(0, 0, getwidth(), getheight());
    drawBloodBar(&a, 2, RED, BLUE, BLACK, 1.0);
    GetUIObjectManager()->render();
}

void ui_check_master_server::afterEvent()
{
}