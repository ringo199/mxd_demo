
#include "game_scene_base.h"

#include "../../global.h"

using namespace global;

game_1::game_1()
{
	this->_player = NULL;
	this->_blockList = NULL;
}

game_1::~game_1()
{
	this->clear();
}

void game_1::init()
{
	area map(0, 0, 2000, 1000);

	this->_player = new player_info;
	this->_blockList = new block[5];

	_player->init(300, 600);

	_blockList[0].init(0, 0, 200, 1000);
	_blockList[1].init(1800, 0, 200, 1000);
	_blockList[2].init(0, 800, 2000, 200);
	_blockList[3].init(200, 300, 300, 20);
	_blockList[4].init(500, 700, 20, 100);

	loadimage(&this->imgBG, "res/bark/bg.png", map.get_width(), map.get_height(), true);
}

void game_1::show()
{
	area map(0, 0, 2000, 1000);
	GetCarama()->init(map.get_width(), map.get_height(), getwidth(), getheight());
	//mciSendString("play res/bg.mp3 repeat", 0, 0, 0);
	//preLoadSound("res/atk.mp3");
	//preLoadSound("res/jump.mp3");

	GetCarama()->setCenterPoint(_player->get_base_area()->get_coord_base());

	_player->eventRegister();

	GetObjectManager()->push_object(_player);

	old_enemy::CreateEnemy(550, 600);
	old_enemy::CreateEnemy(550, 400);
	old_enemy::CreateEnemy(800, 600);

	transpoint *transp = new transpoint();
	transp->init(1600, 700, 100, 100);
	transp->setTranspoint(GAME_2);
	GetObjectManager()->push_object(transp);

	NPC *npc = new NPC();
	npc->init(1000, 700, 100, 100);
	npc->addEventListener((long)&this->npcEventTest);
	GetObjectManager()->push_object(npc);

	for (int i = 0; i < 5; i++)
	{
		GetObjectManager()->push_object(&this->_blockList[i]);
	}
}

void game_1::hide()
{
	GetObjectManager()->clear_objects();

	_player->clearEventRegister();
}

void game_1::clear()
{
	this->hide();

	delete this->_player;
	this->_player = NULL;
	delete[] this->_blockList;
	this->_blockList = NULL;
}

void game_1::beforeEvent()
{
	GetObjectManager()->beforeEvent();
	GetCarama()->changeCenterPoint();
}

void game_1::render()
{
	int ox, oy;
	GetCarama()->mapCoord2CaramaCoora(0, 0, &ox, &oy);
	putimage(ox, oy, &this->imgBG);
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
