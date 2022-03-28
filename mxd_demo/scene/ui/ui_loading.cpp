
#include "ui_scene_base.h"
#include "../../tools.h"
#include "../../global.h"

using namespace global;

ui_loading::ui_loading()
{
    this->_ui_loading_board = new board;
    this->_ui_loading_board->init(0, 0, getwidth(), getheight());
    this->_ui_loading_board->setResType(RES_UI_BG_LOADING);
    this->_ui_loading_board->loadRenderImage();
}

ui_loading::~ui_loading()
{
}

void ui_loading::init()
{
}

void ui_loading::show()
{
    GetUIObjectManager()->push_object(this->_ui_loading_board);
    Sleep(100);
}

void ui_loading::hide()
{
    Sleep(100);
    GetUIObjectManager()->delete_object(this->_ui_loading_board);
}

void ui_loading::clear()
{
    //delete this->_ui_loading_board;
    //this->_ui_loading_board = nullptr;
}


void ui_loading::beforeEvent()
{
}

void ui_loading::render()
{
    GetUIObjectManager()->render();
}

void ui_loading::afterEvent()
{
}