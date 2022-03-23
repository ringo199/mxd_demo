
#include "player.h"


player_info::player_info(carama_info* carama): player(carama)
{
	this->status = player_status::IDLE;
	this->imgIndex = 0;
	this->speed = 2;
	this->is_reverse = false;
	this->is_runing = false;
	this->area_pad = 30;
	this->area_atk_x = 50;
	this->sa_percent = 1.0;
	this->is_on_ground = false;

	this->health = 50;
	this->healthMax = 50;

	this->_event_manager = NULL;
}

player_info::~player_info()
{
	this->clearEventRegister();
}

void player_info::init(int x, int y)
{
	this->_load();

	this->initObject(coord(x, y),
		this->imgPlayer[0].getwidth(), this->imgPlayer[0].getheight());

	this->setRenderArea(this);

	this->setCollsionArea(this);
		//coord(this->area_pad, this->area_pad),
		//this->get_render_area()->get_width() - 2 * this->area_pad,
		//this->get_render_area()->get_height() - this->area_pad);

	this->setHitArea(this,
		coord(this->area_pad, this->area_pad),
		this->get_render_area()->get_width() - 2 * this->area_pad,
		this->get_render_area()->get_height() - this->area_pad);

	this->setAttackArea(this,
		coord(this->area_pad + this->get_render_area()->get_width(), this->area_pad),
		this->area_atk_x,
		this->get_render_area()->get_height() - 2 * this->area_pad);

	this->setGroundCheckArea(this);
}

void player_info::_load()
{
	for (int i = 0; i < 12; i++)
	{
		sprintf_s(this->path, "res/hero%d.png", i + 1);
		loadimage(&this->imgPlayer[i], this->path);
		sprintf_s(this->path, "res/bark/g%02d.png", i + 1);
		loadimage(&this->imgAtkPlayer[i], this->path);
	}
}

void player_info::_move(coord coo)
{
	this->changeOffCoord(coo);

	if (!this->is_reverse)
	{
		this->get_attack_area()->changeRefOffCoord(
			coord(this->area_pad + this->get_render_area()->get_width(), this->area_pad));
	}
	else
	{
		this->get_attack_area()->changeRefOffCoord(
			coord(this->area_pad * -2, this->area_pad));
	}
}

void player_info::run(int is_right)
{
	static int count = 0;
	++count;
	if (count < 400)
	{
		return;
	}
	count = 0;
	if (!this->is_runing)
	{
		s_update = true;
	}
	this->is_runing = true;
	if (this->status == player_status::IDLE)
	{
		this->status = player_status::RUN;
	}
	this->is_reverse = is_right < 0;
	this->_move(coord(this->speed * is_right, 0));
}

void player_info::updown(int is_down)
{
	static int count = 0;
	++count;
	if (count < 400)
	{
		return;
	}
	count = 0;
	if (!this->is_runing)
	{
		s_update = true;
	}
	this->is_runing = true;
	if (this->status == player_status::IDLE)
	{
		this->status = player_status::RUN;
	}
	this->_move(coord(0, this->speed * is_down));
}

void player_info::jump()
{
	if (this->is_on_ground)
	{
		this->v_y = -20;
		this->is_runing = false;
		s_update = true;
		playSound("res/jump.mp3");
		if (this->status != player_status::JUMP)
		{
			this->status = player_status::JUMP;
		}
	}
}

void player_info::attack()
{
	if (!this->getIsAttack())
	{
		this->startAttack();
		this->imgIndex = 0;
		this->is_runing = false;
		s_update = true;
	}
	if (this->status != player_status::ATTACK)
	{
		this->status = player_status::ATTACK;
	}
}

void player_info::hit()
{
	this->health -= 10;
	if (this->health <= 0)
	{
		this->health = this->healthMax;
	}
}

void player_info::hitting()
{
	static int count = 0;
	static double x = 0.0;
	++count;
	if (count < 3)
	{
		return;
	}
	count = 0;
	x += 2.0;
	if (x >= 360.0)
	{
		x = 0.0;
	}
	if (this->getIsHit())
	{
		this->sa_percent = cos(x);
		if (this->sa_percent < 0)
		{
			this->sa_percent *= -1;
		}
	}
	else
	{
		this->sa_percent = 1.0;
	}
}

void player_info::attacking()
{
	static int count = 0;
	++count;
	if (count < 2)
	{
		return;
	}
	count = 0;

	this->imgIndex = (this->imgIndex + 1) % 12;

	if (this->imgIndex == 0)
	{
		this->stopAttack();
		this->status = player_status::IDLE;
	}
}

void player_info::animator()
{
	switch (this->status)
	{
	case player_status::IDLE:
		this->imgIndex = 9;
		break;
	case player_status::RUN:
		this->imgIndex = (this->imgIndex + 1) % 12;
		break;
	case player_status::JUMP:
		break;
	case player_status::ATTACK:
		this->attacking();
		break;
	default:
		break;
	}
	this->hitting();
}

void player_info::render()
{
	switch (this->status)
	{
	case player_status::IDLE:
	case player_status::RUN:
	case player_status::JUMP:
		putimagePNG2(this->get_render_area()->get_coord1(), &this->imgPlayer[this->imgIndex], this->is_reverse, this->sa_percent);
		break;
	case player_status::ATTACK:
		putimagePNG2(this->get_render_area()->get_coord1(), &this->imgAtkPlayer[this->imgIndex], this->is_reverse, this->sa_percent);
		break;
	default:
		break;
	}
	this->renderHP();
}

void player_info::other_event()
{
	this->checkIsRuning();
}

void player_info::checkIsRuning()
{
	if (!this->is_runing && this->status == player_status::RUN)
	{
		this->status = player_status::IDLE;
	}
}

void player_info::cancelRuning()
{
	this->is_runing = false;
}

void player_info::eventRegister(event_manager* eventManager)
{
	this->_event_manager = eventManager;
	eventManager->eventRegister(GAME_CMD_LEFT, (long)&this->cmdLeftRun, this);
	eventManager->eventRegister(GAME_CMD_RIGHT, (long)&this->cmdRightRun, this);
	eventManager->eventRegister(GAME_CMD_UP, (long)&this->cmdUp, this);
	eventManager->eventRegister(GAME_CMD_DOWN, (long)&this->cmdDown, this);
	eventManager->eventRegister(GAME_CMD_JUMP, (long)&this->cmdJump, this);
	eventManager->eventRegister(GAME_CMD_ATTACK, (long)&this->cmdAttack, this);
}

void player_info::clearEventRegister()
{
	this->_event_manager->clearEvent(GAME_CMD_LEFT);
	this->_event_manager->clearEvent(GAME_CMD_RIGHT);
	this->_event_manager->clearEvent(GAME_CMD_UP);
	this->_event_manager->clearEvent(GAME_CMD_DOWN);
	this->_event_manager->clearEvent(GAME_CMD_JUMP);
	this->_event_manager->clearEvent(GAME_CMD_ATTACK);
}

void player_info::cmdUp(void* ctx)
{
	player_info* context = (player_info*)ctx;
	context->updown(-1);
}

void player_info::cmdDown(void* ctx)
{
	player_info* context = (player_info*)ctx;
	context->updown(1);
}

void player_info::cmdLeftRun(void* ctx)
{
	player_info* context = (player_info*)ctx;
	context->run(-1);
}

void player_info::cmdRightRun(void* ctx)
{
	player_info* context = (player_info*)ctx;
	context->run(1);
}

void player_info::cmdJump(void* ctx)
{
	player_info* context = (player_info*)ctx;
	context->jump();
}

void player_info::cmdAttack(void* ctx)
{
	player_info* context = (player_info*)ctx;
	context->attack();
}

void player_info::renderHP()
{
	double percent = (double)(this->health * 100 / this->healthMax) / 100;
	drawBloodBar(10, 10, 300, 20, 3, BLACK, LIGHTGRAY, RED, percent);
}