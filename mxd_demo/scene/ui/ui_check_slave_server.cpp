
#include "ui_scene_base.h"
#include "../../tools.h"

ui_check_slave_server::ui_check_slave_server(event_manager* event_manager)
    :ui_scene_base(event_manager)
{
}

ui_check_slave_server::~ui_check_slave_server()
{
}

void ui_check_slave_server::init()
{
}

void ui_check_slave_server::show()
{
}

void ui_check_slave_server::hide()
{
}

void ui_check_slave_server::clear()
{
}

void ui_check_slave_server::beforeEvent()
{
}

void ui_check_slave_server::render()
{
    static area a(0, 0, getwidth(), getheight());
    drawBloodBar(&a, 2, RED, BLUE, BROWN, 1.0);
}

void ui_check_slave_server::afterEvent()
{
}