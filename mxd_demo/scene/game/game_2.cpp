
#include "game_scene_base.h"


game_2::game_2(event_manager* eventManager, gameManager* game_manager)
	: game_scene_base(eventManager, game_manager)
{
	this->_player = NULL;
	this->_enemy = NULL;
	this->_blockList = NULL;
}

game_2::~game_2()
{
}

void game_2::init()
{
	area map(0, 0, 1500, 1000);
	this->_carama.init(map.get_width(), map.get_height(), getwidth(), getheight());

	this->_player = new player_info(&_carama);
	this->_enemy = new old_enemy(&_carama);
	this->_blockList = new block[5]{ &_carama, &_carama, &_carama, &_carama, &_carama };

	_player->init(1000, 600);

	_enemy->init(700, 600);

	_blockList[0].init(0, 0, 200, 1000);
	_blockList[1].init(1300, 0, 200, 1000);
	_blockList[2].init(0, 800, 2000, 200);
	_blockList[3].init(200, 300, 300, 20);
	_blockList[4].init(500, 500, 20, 100);

	this->_carama.setCenterPoint(_player->get_base_area()->get_coord_base());

	loadimage(&this->imgBG, "res/bark/bg.png", map.get_width(), map.get_height(), true);
}

void game_2::show()
{
	_player->eventRegister(this->_event_manager);

	this->_gameManager->push_object(_player);
	this->_gameManager->push_object(_enemy);

	for (int i = 0; i < 5; i++)
	{
		this->_gameManager->push_object(&this->_blockList[i]);
	}
}

void game_2::hide()
{
	this->_gameManager->clear_objects();
}

void game_2::clear()
{
	delete this->_player;
	this->_player = NULL;
	delete this->_enemy;
	this->_enemy = NULL;
	delete[] this->_blockList;
	this->_blockList = NULL;
}

void game_2::beforeEvent()
{
	this->_gameManager->beforeEvent();
	this->_carama.changeCenterPoint();
}

void game_2::render()
{
	int ox, oy;
	this->_carama.mapCoord2CaramaCoora(0, 0, &ox, &oy);
	putimage(ox, oy, &this->imgBG);
	this->_gameManager->render();
}

void game_2::afterEvent()
{
	this->_gameManager->afterEvent();
}
