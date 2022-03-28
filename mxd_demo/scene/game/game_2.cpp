
#include "game_scene_base.h"

#include "../../global.h"

using namespace global;

game_2::game_2()
{
}

game_2::~game_2()
{
	this->clear();
}

void game_2::init()
{
}

void game_2::show()
{
	//mciSendString("play res/bg.mp3 repeat", 0, 0, 0);
	//preLoadSound("res/atk.mp3");
	//preLoadSound("res/jump.mp3");

	GetCarama()->init(1500, 1000, getwidth(), getheight());

	background* _bg = new background;
	_bg->init(0, 0, 1500, 1000);
	_bg->setResType(RES_GAME_BG_2);
	_bg->loadRenderImage();
	GetObjectManager()->push_object(_bg);

	block* _blockList = new block[6];

	_blockList[0].init(0, 0, 200, 1000);
	_blockList[0].setResType(RES_BLOCK_WALL);
	_blockList[1].init(1300, 0, 200, 1000);
	_blockList[1].setResType(RES_BLOCK_WALL);
	_blockList[2].init(0, 800, 1500, 200);
	_blockList[2].setResType(RES_BLOCK_GROUND);
	_blockList[3].init(250, 500, 100, 50);
	_blockList[3].setResType(RES_BLOCK_PLATFORM1);
	_blockList[4].init(500, 700, 100, 50);
	_blockList[4].setResType(RES_BLOCK_PLATFORM2);
	_blockList[5].init(800, 600, 200, 50);
	_blockList[5].setResType(RES_BLOCK_PLATFORM3);

	for (int i = 0; i < 6; i++)
	{
		_blockList[i].loadRenderImage();
		GetObjectManager()->push_object(&_blockList[i]);
	}

	transpoint *transp = new transpoint();
	transp->init(300, 650, 150, 150);
	transp->setTranspoint(GAME_1);
	transp->setResType(RES_DOOR);
	transp->loadRenderImage();
	GetObjectManager()->push_object(transp);

	if (GetSessionManager()->GetSession(SESSION_TRANS_FROM) == GAME_2)
	{
		GetObjectManager()->GetPlayer()->init(300, 650);
	}
	else
	{
		GetObjectManager()->GetPlayer()->init(1000, 600);
	}

	GetCarama()->setCenterPoint(GetObjectManager()->GetPlayer()->get_base_area()->get_coord_base());

	GetObjectManager()->GetPlayer()->eventRegister();

	GetObjectManager()->push_object(GetObjectManager()->GetPlayer());

	old_enemy::CreateEnemy(550, 600);
	old_enemy::CreateEnemy(700, 600);
	old_enemy::CreateEnemy(800, 600);

	GetSessionManager()->DeleteSession(SESSION_TRANS_FROM);
}

void game_2::hide()
{
	GetObjectManager()->clear_objects();

	GetObjectManager()->GetPlayer()->clearEventRegister();
}

void game_2::clear()
{
	this->hide();
}

void game_2::beforeEvent()
{
	GetObjectManager()->beforeEvent();
	GetCarama()->changeCenterPoint();
}

void game_2::render()
{
	GetObjectManager()->render();
}

void game_2::afterEvent()
{
	GetObjectManager()->afterEvent();
}
