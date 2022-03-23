
#include "ui_scene_base.h"
#include "../../tools.h"

ui_loading::ui_loading()
{
}

ui_loading::~ui_loading()
{
}

void ui_loading::init()
{
}

void ui_loading::show()
{
}

void ui_loading::hide()
{
}

void ui_loading::clear()
{
}


void ui_loading::beforeEvent()
{
}

void ui_loading::render()
{
    static area a(0, 0, getwidth(), getheight());
    testDrawBar(&a);
}

void ui_loading::afterEvent()
{
}