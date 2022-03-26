
#include "game_scene_base.h"

#include "../../global.h"

using namespace global;

game_2::game_2()
{
	this->_player = NULL;
	this->_blockList = NULL;
}

game_2::~game_2()
{
	this->clear();
}

void game_2::init()
{
	this->_player = new player_info;
	this->_blockList = new block[5];

	_player->init(1000, 600);

	_blockList[0].init(0, 0, 200, 1000);
	_blockList[1].init(1300, 0, 200, 1000);
	_blockList[2].init(0, 800, 2000, 200);
	_blockList[3].init(200, 300, 300, 20);
	_blockList[4].init(500, 500, 20, 100);

	area map(0, 0, 1500, 1000);
	loadimage(&this->imgBG, "res/bark/bg.png", map.get_width(), map.get_height(), true);
}

void game_2::show()
{
	area map(0, 0, 1500, 1000);
	GetCarama()->init(map.get_width(), map.get_height(), getwidth(), getheight());

	//mciSendString("play res/bg.mp3 repeat", 0, 0, 0);
	//preLoadSound("res/atk.mp3");
	//preLoadSound("res/jump.mp3");

	GetCarama()->setCenterPoint(_player->get_base_area()->get_coord_base());

	_player->eventRegister();

	old_enemy::CreateEnemy(550, 600);
	old_enemy::CreateEnemy(700, 600);
	old_enemy::CreateEnemy(800, 600);

	transpoint *transp = new transpoint();
	transp->init(300, 700, 100, 100);
	transp->setTranspoint(GAME_1);
	GetObjectManager()->push_object(transp);

	GetObjectManager()->push_object(_player);

	for (int i = 0; i < 5; i++)
	{
		GetObjectManager()->push_object(&this->_blockList[i]);
	}
}

void game_2::hide()
{
	GetObjectManager()->clear_objects();

	_player->clearEventRegister();
}

void game_2::clear()
{
	this->hide();

	delete this->_player;
	this->_player = NULL;
	delete[] this->_blockList;
	this->_blockList = NULL;
}

void game_2::beforeEvent()
{
	GetObjectManager()->beforeEvent();
	GetCarama()->changeCenterPoint();
}

void game_2::render()
{
	int ox, oy;
	GetCarama()->mapCoord2CaramaCoora(0, 0, &ox, &oy);
	putimage(ox, oy, &this->imgBG);
	GetObjectManager()->render();
}

void game_2::afterEvent()
{
	GetObjectManager()->afterEvent();
}
