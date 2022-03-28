
#include "ui_scene_base.h"
#include "../../tools.h"

#include "../../global.h"
#include "../../netEvent.h"
#include "../../cJSON.h"

#include <functional>

using namespace global;

ui_check_master_server::ui_check_master_server()
{
}

ui_check_master_server::~ui_check_master_server()
{
}

void ui_check_master_server::init()
{
    this->eventRegister();
}

void ui_check_master_server::show()
{
    sendMessage_type_1();
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
    /**
    button* btn1 = new button;
    btn1->init(getwidth() / 2 - 150, getheight() / 2 - 50, 100, 100);
    btn1->addEventListener(UI_NEXT);
    btn1->btntxt = "一区";
    btn1->setResType(RES_UI_BTN_);
    btn1->loadRenderImage();
    button* btn2 = new button;
    btn2->init(getwidth() / 2 + 50, getheight() / 2 - 50, 100, 100);
    btn2->addEventListener(UI_NEXT);
    btn2->btntxt = "二区";
    btn2->setResType(RES_UI_BTN_);
    btn2->loadRenderImage();
    */
    GetUIObjectManager()->push_object(l);
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

void ui_check_master_server::eventRegister()
{
    GetEventManager()->eventRegister(NET_TYPE_1, (long)&this->setServerList, this);
}

void ui_check_master_server::setServerList(void* ctx, string server_list_rows)
{
    ui_check_master_server* context = (ui_check_master_server*)ctx;

    cJSON* rows = cJSON_Parse(server_list_rows.c_str());

    cJSON* row;
    cJSON* id;
    cJSON* name;

    context->_server_list.clear();
    int rows_size = cJSON_GetArraySize(rows);
    for (int i = 0; i < rows_size; ++i)
    {
        row = cJSON_GetArrayItem(rows, i);
        id = cJSON_GetObjectItem(row, "id");
        name = cJSON_GetObjectItem(row, "name");
        context->_server_list.push_back({ id->valueint, name->valuestring });
    }

    int btn_width = 150;
    int btn_height = 100;

    for (int i = 0; i < context->_server_list.size(); ++i)
    {
        button* btn = new button;
        btn->init(((getwidth() - btn_width) >> 1) + btn_width * i, (getheight() - btn_height) >> 1, btn_width, btn_height);
        btn->addEventListener([=]()
        {
            GetSessionManager()->SetSession(
                SESSION_MASTER_SERVER_TYPE, context->_server_list[i].first);
            // sendMessage_type_2(context->_server_list[i].first);
            GetEventManager()->eventEmit(UI_NEXT);
        });
        btn->btntxt = context->_server_list[i].second.c_str();
        btn->setResType(RES_UI_BTN_);
        btn->loadRenderImage();
        GetUIObjectManager()->push_object(btn);
    }
}
