
#include "ui_scene_base.h"
#include "../../tools.h"

ui_check_player::ui_check_player(event_manager* event_manager)
    :ui_scene_base(event_manager)
{
}

ui_check_player::~ui_check_player()
{
}

void ui_check_player::init()
{
}

void ui_check_player::show()
{
}

void ui_check_player::hide()
{
}

void ui_check_player::clear()
{
}

void ui_check_player::beforeEvent()
{
}

void ui_check_player::render()
{
    static area a(0, 0, getwidth(), getheight());
    drawBloodBar(&a, 2, RED, BLUE, YELLOW, 1.0);
}

void ui_check_player::afterEvent()
{
}