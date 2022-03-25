
#include "ui_scene_base.h"
#include "../../tools.h"
#include "../../var.h"

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
}

void ui_check_master_server::hide()
{
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
}

void ui_check_master_server::afterEvent()
{
}