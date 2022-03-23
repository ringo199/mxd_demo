
#include "ui_scene_base.h"
#include "../../tools.h"

ui_login::ui_login(event_manager* event_manager)
    :ui_scene_base(event_manager)
{
}

ui_login::~ui_login()
{
}

void ui_login::init()
{
}

void ui_login::show()
{
}

void ui_login::hide()
{
}

void ui_login::clear()
{
}

void ui_login::beforeEvent()
{
}

void ui_login::render()
{
    static area a(0, 0, getwidth(), getheight());
    drawBloodBar(&a, 2, WHITE, BLUE, BLACK, 1.0);
}

void ui_login::afterEvent()
{
}