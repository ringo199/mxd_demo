
#include "game_scene_base.h"

#include "../../global.h"

using namespace global;

game_1::game_1()
{
}

game_1::~game_1()
{
	this->clear();
}

void game_1::init()
{
}

void game_1::show()
{
	area map(0, 0, 2000, 1000);
	GetCarama()->init(map.get_width(), map.get_height(), getwidth(), getheight());
	//mciSendString("play res/bg.mp3 repeat", 0, 0, 0);
	//preLoadSound("res/atk.mp3");
	//preLoadSound("res/jump.mp3");

	background* _bg = new background;
	_bg->init(0, 0, 2000, 1000);
	_bg->setResType(RES_BG);
	_bg->loadRenderImage();
	GetObjectManager()->push_object(_bg);

	block* _blockList = new block[6];

	NPC* npc = new NPC();
	npc->init(1000, 700, 100, 100);
	npc->setResType(RES_NPC_ACAO);
	npc->loadRenderImage();
	npc->addEventListener((long)&this->npcEventTest);
	GetObjectManager()->push_object(npc);

	_blockList[0].init(0, 0, 200, 1000);
	_blockList[0].setResType(RES_BLOCK_WALL);
	_blockList[1].init(1800, 0, 200, 1000);
	_blockList[1].setResType(RES_BLOCK_WALL);
	_blockList[2].init(0, 800, 2000, 200);
	_blockList[2].setResType(RES_BLOCK_GROUND);
	_blockList[3].init(250, 500, 100, 50);
	_blockList[3].setResType(RES_BLOCK_PLATFORM1);
	_blockList[4].init(500, 700, 100, 50);
	_blockList[4].setResType(RES_BLOCK_PLATFORM2);
	_blockList[5].init(800, 600, 200, 50);
	_blockList[5].setResType(RES_BLOCK_PLATFORM3);

	old_enemy::CreateEnemy(550, 600);
	old_enemy::CreateEnemy(550, 400);
	old_enemy::CreateEnemy(800, 600);

	transpoint *transp = new transpoint();
	transp->init(1550, 650, 150, 150);
	transp->setTranspoint(GAME_2);
	transp->setResType(RES_DOOR);
	transp->loadRenderImage();
	GetObjectManager()->push_object(transp);

	if (GetSessionManager()->GetSession(SESSION_TRANS_FROM) == GAME_1)
	{
		GetObjectManager()->GetPlayer()->init(1550, 650);
	}
	else
	{
		GetObjectManager()->GetPlayer()->init(300, 600);
	}

	GetCarama()->setCenterPoint(GetObjectManager()->GetPlayer()->get_base_area()->get_coord_base());

	GetObjectManager()->GetPlayer()->eventRegister();

	GetObjectManager()->push_object(GetObjectManager()->GetPlayer());

	for (int i = 0; i < 6; i++)
	{
		_blockList[i].loadRenderImage();
		GetObjectManager()->push_object(&_blockList[i]);
	}
	GetSessionManager()->DeleteSession(SESSION_TRANS_FROM);
}

void game_1::hide()
{
	GetObjectManager()->clear_objects();

	GetObjectManager()->GetPlayer()->clearEventRegister();
}

void game_1::clear()
{
	this->hide();
}

void game_1::beforeEvent()
{
	GetObjectManager()->beforeEvent();
	GetCarama()->changeCenterPoint();
}

void game_1::render()
{
	GetObjectManager()->render();
}

void game_1::afterEvent()
{
	GetObjectManager()->afterEvent();
}

void game_1::npcEventTest(void* ctx)
{
	printf("isclicked\n");
}
