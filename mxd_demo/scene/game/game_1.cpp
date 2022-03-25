
#include "game_scene_base.h"

#include "../../global.h"

using namespace global;

game_1::game_1()
{
	this->_player = NULL;
	this->_enemy = NULL;
	this->_blockList = NULL;
}

game_1::~game_1()
{
	this->clear();
}

void game_1::init()
{
	area map(0, 0, 2000, 1000);
	GetCarama()->init(map.get_width(), map.get_height(), getwidth(), getheight());

	this->_player = new player_info;
	this->_enemy = new old_enemy;
	this->_blockList = new block[5];

	_player->init(300, 600);

	_enemy->init(500, 600);

	_blockList[0].init(0, 0, 200, 1000);
	_blockList[1].init(1800, 0, 200, 1000);
	_blockList[2].init(0, 800, 2000, 200);
	_blockList[3].init(200, 300, 300, 20);
	_blockList[4].init(500, 700, 20, 100);

	loadimage(&this->imgBG, "res/bark/bg.png", map.get_width(), map.get_height(), true);
}

void game_1::show()
{
	//mciSendString("play res/bg.mp3 repeat", 0, 0, 0);
	//preLoadSound("res/atk.mp3");
	//preLoadSound("res/jump.mp3");

	GetCarama()->setCenterPoint(_player->get_base_area()->get_coord_base());

	_player->eventRegister();

	GetGameManager()->push_object(_player);
	GetGameManager()->push_object(_enemy);

	for (int i = 0; i < 5; i++)
	{
		GetGameManager()->push_object(&this->_blockList[i]);
	}
}

void game_1::hide()
{
	GetGameManager()->clear_objects();

	_player->clearEventRegister();
}

void game_1::clear()
{
	this->hide();

	delete this->_player;
	this->_player = NULL;
	delete this->_enemy;
	this->_enemy = NULL;
	delete[] this->_blockList;
	this->_blockList = NULL;
}

void game_1::beforeEvent()
{
	GetGameManager()->beforeEvent();
	GetCarama()->changeCenterPoint();
}

void game_1::render()
{
	int ox, oy;
	GetCarama()->mapCoord2CaramaCoora(0, 0, &ox, &oy);
	putimage(ox, oy, &this->imgBG);
	GetGameManager()->render();
}

void game_1::afterEvent()
{
	GetGameManager()->afterEvent();
}
