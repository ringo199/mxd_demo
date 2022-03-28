
#include "ui_scene_base.h"
#include "../../tools.h"

#include "../../global.h"
#include "../../netEvent.h"

using namespace global;

label* l3 = new label;

ui_login::ui_login()
{
}

ui_login::~ui_login()
{
}

void ui_login::init()
{
    this->eventRegister();
}

void ui_login::show()
{
    board* b = new board;
    b->init(0, 0, getwidth(), getheight());
    b->setResType(RES_UI_BG2);
    b->loadRenderImage();
    GetUIObjectManager()->push_object(b);

    label* l = new label;
    l->color = WHITE;
    l->fontSize = 50;
    l->txt = "请登录";
    l->init(getwidth() / 2 - 250, 100, 500, 100);

    label* l1 = new label;
    l1->color = WHITE;
    l1->fontSize = 30;
    l1->txt = "账号：";
    l1->init(getwidth() / 2 - 180, 190, 200, 100);

    label* l2 = new label;
    l2->color = WHITE;
    l2->fontSize = 30;
    l2->txt = "密码：";
    l2->init(getwidth() / 2 - 180, 240, 200, 100);

    input* i1 = new input;
    input* i2 = new input;

    i2->type = input::INPUT_TYPE::PASSWORD;

    i1->init(getwidth() / 2 - 30, 225, 200, 30);
    i2->init(getwidth() / 2 - 30, 275, 200, 30);

    i1->fontSize = 30;
    i2->fontSize = 30;
    i1->txt = "diana";
    i2->txt = "diana";

    l3->color = WHITE;
    l3->fontSize = 25;
    l3->init(getwidth() / 2, getheight() / 2 + 30, getwidth() >> 1, 100);

    button* btn1 = new button;
    btn1->init(getwidth() / 2 - 150, getheight() / 2 + 100, 100, 100);
    btn1->addEventListener([=]() {
        ChangeFocusInput(NULL);
        GetEventManager()->eventEmit(UI_BACK);
    });
    btn1->btntxt = "上一步";
    btn1->setResType(RES_UI_BTN_);
    btn1->loadRenderImage();
    button* btn2 = new button;
    btn2->init(getwidth() / 2 + 50, getheight() / 2 + 100, 100, 100);
    btn2->addEventListener([=]() {
        ChangeFocusInput(NULL);
        // cout << i1->txt << " " << i2->txt << endl;
        sendMessage_type_3(
            GetSessionManager()->GetSession(SESSION_MASTER_SERVER_TYPE),
            i1->txt.c_str(), i2->txt.c_str());
    });
    btn2->btntxt = "下一步";
    btn2->setResType(RES_UI_BTN_);
    btn2->loadRenderImage();
    GetUIObjectManager()->push_object(l);
    GetUIObjectManager()->push_object(l1);
    GetUIObjectManager()->push_object(l2);
    GetUIObjectManager()->push_object(l3);
    GetUIObjectManager()->push_object(i1);
    GetUIObjectManager()->push_object(i2);
    GetUIObjectManager()->push_object(btn1);
    GetUIObjectManager()->push_object(btn2);
}

void ui_login::hide()
{
    GetUIObjectManager()->clear_objects();
}

void ui_login::clear()
{
}

void ui_login::beforeEvent()
{
}

void ui_login::render()
{
    GetUIObjectManager()->render();
}

void ui_login::afterEvent()
{
}

void ui_login::eventRegister()
{
    GetEventManager()->eventRegister(NET_TYPE_3_SUCCESS, (long)&this->setLoginSuccess, this);
    GetEventManager()->eventRegister(NET_TYPE_3_FAIL, (long)&this->setLoginFailMessage, this);
}

void ui_login::setLoginSuccess(void*, string userInfo)
{
    GetSessionManager()->SetSession(SESSION_USER_INFO, userInfo);
    GetEventManager()->eventEmit(UI_NEXT);
}

void ui_login::setLoginFailMessage(void*, string msg)
{
    cout << msg << endl;
    l3->txt = msg.c_str();
}
