
#include "ui_scene_base.h"
#include "../../tools.h"

#include "../../global.h"
#include "../../netEvent.h"
#include "../../cJSON.h"

using namespace global;

ui_check_slave_server::ui_check_slave_server()
{
}

ui_check_slave_server::~ui_check_slave_server()
{
}

void ui_check_slave_server::init()
{
    this->eventRegister();
}

void ui_check_slave_server::show()
{
    sendMessage_type_2(
        GetSessionManager()->GetSession(SESSION_MASTER_SERVER_TYPE));

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
    btn1->init(10, 10, 100, 50);
    btn1->addEventListener(UI_BACK);
    btn1->btntxt = "上一步";
    btn1->setResType(RES_UI_BTN);
    btn1->loadRenderImage();
    GetUIObjectManager()->push_object(l);
    GetUIObjectManager()->push_object(btn1);
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

void ui_check_slave_server::eventRegister()
{
    GetEventManager()->eventRegister(NET_TYPE_2, (long)&this->setSubServerList, this);
}

void ui_check_slave_server::setSubServerList(void* ctx, string sub_server_list_rows)
{

    ui_check_master_server* context = (ui_check_master_server*)ctx;

    cJSON* rows = cJSON_Parse(sub_server_list_rows.c_str());

    cJSON* row;
    cJSON* id;
    cJSON* name;

    int rows_size = cJSON_GetArraySize(rows);

    int btn_width = 150;
    int btn_height = 100;

    for (int i = 0; i < rows_size; ++i)
    {
        row = cJSON_GetArrayItem(rows, i);
        id = cJSON_GetObjectItem(row, "id");
        name = cJSON_GetObjectItem(row, "name");

        button* btn = new button;
        btn->init(btn_width * i, (getheight() - btn_height) >> 1, btn_width, btn_height);
        btn->addEventListener([=]()
        {
            GetSessionManager()->SetSession(
                SESSION_SLAVE_SERVER_TYPE, id->valueint);
            GetEventManager()->eventEmit(UI_NEXT);
        });
        btn->btntxt = name->valuestring;
        btn->setResType(RES_UI_BTN_);
        btn->loadRenderImage();
        GetUIObjectManager()->push_object(btn);
    }
}
