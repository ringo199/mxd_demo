
#include "ui_scene_base.h"
#include "../../tools.h"

#include "../../global.h"
#include "../../cJSON.h"

using namespace global;

ui_check_player::ui_check_player()
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
    board* b = new board;
    b->init(0, 0, getwidth(), getheight());
    b->setResType(RES_UI_BG4);
    b->loadRenderImage();
    GetUIObjectManager()->push_object(b);

    label* l = new label;
    l->color = WHITE;
    l->fontSize = 50;
    l->txt = "请选择角色";
    l->init(getwidth() / 2 - 250, 100, 500, 100);

    button* btn1 = new button;
    btn1->init(10, 10, 100, 50);
    btn1->addEventListener(UI_BACK);
    btn1->btntxt = "上一步";
    btn1->setResType(RES_UI_BTN);
    btn1->loadRenderImage();

    cJSON* rows = cJSON_Parse(
        GetSessionManager()->GetSession_String(SESSION_USER_INFO).c_str());

    cJSON* row;
    cJSON* id;
    cJSON* name;
    cJSON* level;
    cJSON* smallAreaId;
    cJSON* gameMapID;

    int rows_size = cJSON_GetArraySize(rows);

    int btn_width = 150;
    int btn_height = 100;

    for (int i = 0; i < rows_size; ++i)
    {
        row = cJSON_GetArrayItem(rows, i);
        id = cJSON_GetObjectItem(row, "id");
        name = cJSON_GetObjectItem(row, "name");
        level = cJSON_GetObjectItem(row, "level");
        smallAreaId = cJSON_GetObjectItem(row, "smallAreaId");
        gameMapID = cJSON_GetObjectItem(row, "gameMapID");

        if (GetSessionManager()->GetSession(SESSION_SLAVE_SERVER_TYPE) == smallAreaId->valueint)
        {
            button* btn = new button;
            btn->init(btn_width * i, (getheight() - btn_height) >> 1, btn_width, btn_height);
            btn->addEventListener([=]()
            {
                GetSessionManager()->SetSession(
                    SESSION_MAP_ID, gameMapID->valueint);
                GetSessionManager()->SetSession(
                    SESSION_LEVEL, level->valueint);
                GetSessionManager()->SetSession(
                    SESSION_USER_ID, id->valueint);
                GetSessionManager()->SetSession(
                    SESSION_USER_NAME, name->valuestring);

                GetEventManager()->eventEmit(UI_NEXT);
            });
            btn->btntxt = name->valuestring;
            btn->setResType(RES_UI_BTN_);
            btn->loadRenderImage();
            GetUIObjectManager()->push_object(btn);
        }
    }

    GetUIObjectManager()->push_object(l);
    GetUIObjectManager()->push_object(btn1);
}

void ui_check_player::hide()
{
    GetUIObjectManager()->clear_objects();
}

void ui_check_player::clear()
{
}

void ui_check_player::beforeEvent()
{
}

void ui_check_player::render()
{
    GetUIObjectManager()->render();
}

void ui_check_player::afterEvent()
{
}