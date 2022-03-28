
#include "ui_scene_base.h"
#include "../../tools.h"
#include "../../global.h"
#include "../../netEvent.h"

using namespace global;

discussion* dis = new discussion;
input* inp = new input;
button* inp_enter = new button;
board* b = new board;
label* l_lv = new label;
label* l_name = new label;
progress* _hp = new progress;
progress* _mp = new progress;
progress* _exp = new progress;
button* back = new button;
button* backHome = new button;

ui_game::ui_game()
{
    dia = new dialog;
}

ui_game::~ui_game()
{
    delete dia;
}

#include <sstream>
void ui_game::init()
{
    this->eventRegister();
    sendMessage_type_4(GetSessionManager()->GetSession(SESSION_USER_ID));
    sendMessage_type_5(0, 0, 0);
    GetSessionManager()->DeleteSession(SESSION_TRANS_FROM);
    GetEventManager()->eventEmit(GAME_GOTO_SCENE, GetSessionManager()->GetSession(SESSION_MAP_ID));
    GetLoadManager()->LoadAsset(RES_HERO);
    GetLoadManager()->LoadAsset(RES_HERO_ATTACK);
    GetLoadManager()->LoadAsset(RES_ENEMY);

    dia->init(getwidth() >> 2, (getheight() >> 3) * 3, getwidth() >> 1, getheight() >> 2);
    dia->fontSize = 15;
    dia->eventRegister();

    dis->init(0, getheight() - 250, 480, 125);
    dis->fontSize = 25;
    inp->init(0, getheight() - 125, 200, 25);
    inp->fontSize = 25;
    inp_enter->init(200, getheight() - 125, 80, 25);
    inp_enter->btntxt = "say";
    inp_enter->addEventListener([=]() {
        if (GetFocusInput() != inp)
        {
            ChangeFocusInput(inp);
        }
        else
        {
            if (!GetFocusInput()->txt.empty())
            {
                // stringstream ss1;
                // ss1 << GetSessionManager()->GetSession_String(SESSION_USER_NAME) << ": " << GetFocusInput()->txt;
                // dis->pushTxt(ss1.str());
                sendMessage_type_255(GetFocusInput()->txt.c_str());
                GetFocusInput()->txt = "";
                ChangeFocusInput(NULL);
            }
        }
    });
    inp_enter->setResType(RES_UI_BTN);
    inp_enter->loadRenderImage();

    b->init(0, getheight() - 100, getwidth(), 100);
    b->setResType(RES_UI_PLAYER_INFO);
    b->loadRenderImage();

    l_lv->init(50, getheight() - 62.5, 150, 25);
    l_name->init(125, getheight() - 62.5, 150, 25);
    l_lv->color = BLACK;
    l_name->txt = GetSessionManager()->GetSession_String(SESSION_USER_NAME);
    l_name->color = BLACK;

    _hp->init(200, getheight() - 62.5, 200, 25);
    _hp->fillColor = RED;

    _mp->init(420, getheight() - 62.5, 200, 25);
    _mp->fillColor = BLUE;

    _exp->init(640, getheight() - 62.5, 200, 25);
    _exp->fillColor = YELLOW;

    back->init(860, getheight() - 75, 100, 50);
    back->addEventListener(UI_BACK);
    back->btntxt = "上一步";
    back->setResType(RES_UI_BTN);
    back->loadRenderImage();

    backHome->init(10, 10, 100, 50);
    backHome->addEventListener(UI_BACKHOME);
    backHome->btntxt = "首页";
    backHome->setResType(RES_UI_BTN);
    backHome->loadRenderImage();
}

void ui_game::show()
{
    GetUIObjectManager()->push_object(dis);
    GetUIObjectManager()->push_object(b);
    GetUIObjectManager()->push_object(l_lv);
    GetUIObjectManager()->push_object(l_name);
    GetUIObjectManager()->push_object(_hp);
    GetUIObjectManager()->push_object(_mp);
    GetUIObjectManager()->push_object(_exp);
    GetUIObjectManager()->push_object(inp);
    GetUIObjectManager()->push_object(inp_enter);
    GetUIObjectManager()->push_object(back);
    GetUIObjectManager()->push_object(backHome);
    GetUIObjectManager()->push_object(dia);
    GetUIObjectManager()->push_object(dia->_close_btn);
    GetUIObjectManager()->push_object(dia->_next_btn);
    GetUIObjectManager()->push_object(dia->_ok_btn);
    GetUIObjectManager()->push_object(dia->_name);
    GetUIObjectManager()->push_object(dia->_img);
    GetUIObjectManager()->push_object(dia->_content);
}

void ui_game::hide()
{
    GetUIObjectManager()->clear_objects();
}

void ui_game::clear()
{
    GetGameSceneManager()->clearScene();
}

void ui_game::beforeEvent()
{
    GetObjectManager()->beforeEvent();
    GetCarama()->changeCenterPoint();
    stringstream ss;
    ss << "lv_" << GetSessionManager()->GetSession(SESSION_LEVEL);
    ss >> l_lv->txt;
    int max_hp = GetSessionManager()->GetSession(SESSION_MAX_HP);
    int max_mp = GetSessionManager()->GetSession(SESSION_MAX_MP);
    int max_exp = GetSessionManager()->GetSession(SESSION_MAX_EXP);
    max_hp = max_hp == 0 ? 1 : max_hp;
    max_mp = max_mp == 0 ? 1 : max_mp;
    max_exp = max_exp == 0 ? 1 : max_exp;
    _hp->percent = (double)(
        GetSessionManager()->GetSession(SESSION_HP) * 100 / max_hp) / 100;
    _mp->percent = (double)(
        GetSessionManager()->GetSession(SESSION_MP) * 100 / max_mp) / 100;
    _exp->percent = (double)(
        GetSessionManager()->GetSession(SESSION_EXP) * 100 / max_exp) / 100;
}

void ui_game::render()
{
    GetObjectManager()->render();
    GetUIObjectManager()->render();
}

void ui_game::afterEvent()
{
    GetObjectManager()->afterEvent();
}

void ui_game::eventRegister()
{
    GetGameSceneManager()->eventRegister();
    GetEventManager()->eventRegister(NET_TYPE_255, (long)&this->setDiscussTxt, this);
}

void ui_game::setDiscussTxt(void*, string msg)
{
    dis->pushTxt(msg);
}
