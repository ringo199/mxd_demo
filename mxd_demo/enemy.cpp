
#include "enemy.h"

#include "global.h"
#include "netEvent.h"

using namespace global;

old_enemy::old_enemy() : enemy()
{
	this->status = enemy_status::BIRTH;
	this->sa_percent = 0.0f;
	this->is_reverse = false;
	this->speed = 3;
	this->area_pad = 3;

	this->health = 30;
	this->healthMax = 30;

	this->is_hit = false;

	this->startAttack();
}

old_enemy::~old_enemy()
{
}

void old_enemy::init(int x, int y)
{
	this->initObject(coord(x, y),
		GetLoadManager()->LoadAsset(RES_ENEMY)->img->getwidth(),
		GetLoadManager()->LoadAsset(RES_ENEMY)->img->getheight());
	this->setRenderArea(this);
	this->setCollsionArea(this);
	this->setAttackArea(this, coord(this->area_pad, this->area_pad),
						this->get_base_area()->get_width() - this->area_pad * 2,
						this->get_base_area()->get_height() - this->area_pad);
	this->setHitArea(this, coord(this->area_pad, this->area_pad),
					 this->get_base_area()->get_width() - this->area_pad * 2,
					 this->get_base_area()->get_height() - this->area_pad);
	this->setHealthArea(this, coord(0, -15), this->get_base_area()->get_width(), 10);

	this->setGroundCheckArea(this);
	this->setAnimator(this);
	this->setOtherEvent(this);
}

void old_enemy::render()
{
	putimagePNG2(this->get_render_area()->get_coord1(), getwidth(),
		this->GetImage(RES_ENEMY), this->is_reverse, this->sa_percent);

	this->renderHP();
}

void old_enemy::renderHP()
{
	double percent = (double)(this->health * 100 / this->healthMax) / 100;
	drawBloodBar(this->get_health_area(), 2, BLACK, LIGHTGRAY, RED, percent);
}

void old_enemy::animator()
{
	switch (this->status)
	{
	case enemy_status::BIRTH:
		this->sa_percent += 0.05f;
		if (this->sa_percent >= 1.0f)
		{
			this->sa_percent = 1.0f;
			this->status = enemy_status::IDLE;
		}
	case enemy_status::IDLE:
		this->ChangeImageIndex(RES_ENEMY, 4);
		break;
	case enemy_status::RUN:
		this->AddStepImageIndex(RES_ENEMY);
		break;
	case enemy_status::DIE:
		this->sa_percent -= 0.05f;
		if (this->sa_percent <= 0.0f)
		{
			this->_died();
		}
	default:
		break;
	}
	this->hitting();
}

void old_enemy::other_event()
{
	this->ai();
}

void old_enemy::ai()
{
	change_status();
	move();
}

void old_enemy::change_status()
{
	if (getTickCount() - this->_change_status_timer < this->_change_status_timer_const)
	{
		return;
	}

	this->_change_status_timer = getTickCount();

	enemy_status beforeStatus = this->status;

	switch (this->status)
	{
	case enemy_status::IDLE:
	case enemy_status::RUN:
		this->status = (enemy_status)(rand() % 2 + (int)enemy_status::IDLE);
		if (this->status == enemy_status::RUN && beforeStatus == enemy_status::IDLE)
		{
			this->is_reverse = (rand() % 2) >= 1;
		}
		break;
	default:
		break;
	}
}

void old_enemy::move()
{
	switch (this->status)
	{
	case enemy_status::IDLE:
		break;
	case enemy_status::RUN:
		this->_move();
		break;
	default:
		break;
	}
}

void old_enemy::hit()
{
	this->health -= 10;
	if (this->health <= 0)
	{
		this->health = 0;
		this->status = enemy_status::DIE;
	}
	this->_hitting_angle = 0;
	playSound("res/atk.mp3");
}

void old_enemy::hitting()
{
	if (this->status == enemy_status::BIRTH || this->status == enemy_status::DIE)
	{
		return;
	}

	if (getTickCount() - this->_hitting_timer < this->_hitting_timer_const)
	{
		return;
	}

	this->_hitting_timer = getTickCount();

	this->_hitting_angle += 2;
	if (this->_hitting_angle >= 360)
	{
		this->_hitting_angle = 0;
	}
	if (this->getIsHit())
	{
		this->sa_percent = cos(this->_hitting_angle);
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

void old_enemy::CreateEnemy(int x, int y)
{
	old_enemy *ep = new old_enemy;
	ep->init(x, y);
	GetObjectManager()->push_object(ep);
}


void old_enemy::_died()
{
	sendMessage_type_5(0, 0, 20);
	this->status = enemy_status::DIED;
	GetObjectManager()->delete_object(this);
}

void old_enemy::_move()
{
	this->changeOffX((this->is_reverse ? 1 : -1) * speed);
}
