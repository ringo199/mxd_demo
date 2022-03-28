
#include "player.h"

#include "global.h"
#include "netEvent.h"

using namespace global;

player_info::player_info() : player()
{
	this->status = player_status::IDLE;
	this->speed = 2;
	this->is_reverse = false;
	this->is_runing = false;
	this->area_pad = 30;
	this->area_atk_x = 50;
	this->sa_percent = 1.0;
	this->is_on_ground = false;
}

player_info::~player_info()
{
	this->clearEventRegister();
}

void player_info::init(int x, int y)
{
	this->initObject(coord(x, y),
		GetLoadManager()->LoadAsset(RES_HERO)->img->getwidth(),
		GetLoadManager()->LoadAsset(RES_HERO)->img->getheight());

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
	this->setAnimator(this);
	this->setOtherEvent(this);
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
	if (count < 150)
	{
		return;
	}
	count = 0;
	if (!this->is_runing)
	{
		ChangeUpdate(true);
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
		ChangeUpdate(true);
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
		ChangeUpdate(true);
		//playSound("res/jump.mp3");
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
		this->ChangeImageIndex(RES_HERO_ATTACK, 0);
		this->is_runing = false;
		ChangeUpdate(true);
	}
	if (this->status != player_status::ATTACK)
	{
		this->status = player_status::ATTACK;
	}
}

void player_info::hit()
{
	sendMessage_type_5(-10, 0, 0);
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

	this->AddStepImageIndex(RES_HERO_ATTACK);

	if (this->GetImageIndex(RES_HERO_ATTACK) == 0)
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
		this->ChangeImageIndex(RES_HERO, 9);
		break;
	case player_status::RUN:
		this->AddStepImageIndex(RES_HERO);
		break;
	case player_status::JUMP:
		if (this->is_on_ground)
		{
			this->status = player_status::IDLE;
		}
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
		putimagePNG2(this->get_render_area()->get_coord1(),
			this->GetImage(RES_HERO), this->is_reverse, this->sa_percent);
		break;
	case player_status::ATTACK:
		putimagePNG2(this->get_render_area()->get_coord1(),
			this->GetImage(RES_HERO_ATTACK), this->is_reverse, this->sa_percent);
		break;
	default:
		break;
	}
}

void player_info::other_event()
{
	this->checkIsRuning();
	//GetSessionManager()->SetSession(SESSION_HP, this->health);
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

void player_info::eventRegister()
{
	GetEventManager()->eventRegister(GAME_CMD_LEFT, (long)&this->cmdLeftRun, this);
	GetEventManager()->eventRegister(GAME_CMD_RIGHT, (long)&this->cmdRightRun, this);
	GetEventManager()->eventRegister(GAME_CMD_UP, (long)&this->cmdUp, this);
	GetEventManager()->eventRegister(GAME_CMD_DOWN, (long)&this->cmdDown, this);
	GetEventManager()->eventRegister(GAME_CMD_JUMP, (long)&this->cmdJump, this);
	GetEventManager()->eventRegister(GAME_CMD_ATTACK, (long)&this->cmdAttack, this);
	GetEventManager()->eventRegister(GAME_CMD_STAY, (long)&this->cmdStay, this);
}

void player_info::clearEventRegister()
{
	GetEventManager()->clearEvent(GAME_CMD_LEFT);
	GetEventManager()->clearEvent(GAME_CMD_RIGHT);
	GetEventManager()->clearEvent(GAME_CMD_UP);
	GetEventManager()->clearEvent(GAME_CMD_DOWN);
	GetEventManager()->clearEvent(GAME_CMD_JUMP);
	GetEventManager()->clearEvent(GAME_CMD_ATTACK);
	GetEventManager()->clearEvent(GAME_CMD_STAY);
}

void player_info::cmdUp(void *ctx)
{
	player_info *context = (player_info *)ctx;
	//context->updown(-1);

	GetObjectManager()->delivery(context->get_collsion_area());
}

void player_info::cmdDown(void *ctx)
{
	player_info *context = (player_info *)ctx;
	//context->updown(1);
}

void player_info::cmdLeftRun(void *ctx)
{
	player_info *context = (player_info *)ctx;
	context->run(-1);
}

void player_info::cmdRightRun(void *ctx)
{
	player_info *context = (player_info *)ctx;
	context->run(1);
}

void player_info::cmdJump(void *ctx)
{
	player_info *context = (player_info *)ctx;
	context->jump();
}

void player_info::cmdAttack(void *ctx)
{
	player_info *context = (player_info *)ctx;
	context->attack();
}

void player_info::cmdStay(void *ctx)
{
	player_info *context = (player_info *)ctx;
	if (context->status == player_status::RUN)
	{
		context->status = player_status::IDLE;
	}
}
