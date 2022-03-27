
#include "ui_scene_base.h"
#include "../../tools.h"
#include "../../global.h"

using namespace global;

board* b = new board;
label* l_lv = new label;
progress* _hp = new progress;
progress* _mp = new progress;
progress* _exp = new progress;
button* back = new button;

ui_game::ui_game()
{
}

ui_game::~ui_game()
{
}

void ui_game::init()
{
    GetGameSceneManager()->eventRegister();
    GetSessionManager()->DeleteSession(SESSION_TRANS_FROM);
    GetEventManager()->eventEmit(GAME_GOTO_SCENE, GAME_1);
    GetLoadManager()->LoadAsset(RES_HERO);
    GetLoadManager()->LoadAsset(RES_HERO_ATTACK);
    GetLoadManager()->LoadAsset(RES_ENEMY);

    b->init(0, getheight() - 100, getwidth(), 100);
    b->setResType(RES_UI_PLAYER_INFO);
    b->loadRenderImage();

    l_lv->init(50, getheight() - 62.5, 150, 25);
    l_lv->txt = "lv_100";
    l_lv->color = BLACK;

    _hp->init(200, getheight() - 62.5, 200, 25);
    _hp->fillColor = RED;

    _mp->init(420, getheight() - 62.5, 200, 25);
    _mp->fillColor = BLUE;

    _exp->init(640, getheight() - 62.5, 200, 25);
    _exp->fillColor = YELLOW;

    back->init(860, getheight() - 75, 100, 50);
    back->addEventListener(UI_BACK);
    back->btntxt = "ÉÏÒ»²½";
    back->setResType(RES_UI_BTN);
    back->loadRenderImage();

    Sleep(300);
}

void ui_game::show()
{
    GetUIObjectManager()->push_object(b);
    GetUIObjectManager()->push_object(l_lv);
    GetUIObjectManager()->push_object(_hp);
    GetUIObjectManager()->push_object(_mp);
    GetUIObjectManager()->push_object(_exp);
    GetUIObjectManager()->push_object(back);
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
    GetGameSceneManager()->getGameScene()->beforeEvent();
    _hp->percent = (double)(GetSessionManager()->GetSession(SESSION_HP) * 100 / 50) / 100;
}

void ui_game::render()
{
    GetGameSceneManager()->getGameScene()->render();
    GetUIObjectManager()->render();
}

void ui_game::afterEvent()
{
    GetGameSceneManager()->getGameScene()->afterEvent();
}
