
#include "enemy.h"


old_enemy::old_enemy(carama_info* carama) : enemy(carama)
{
	this->imgIndex = 4;
	this->status = enemy_status::IDLE;
	this->is_reverse = false;
	this->speed = 3;
	this->area_pad = 3;

	this->health = 30;
	this->healthMax = 30;
}

old_enemy::~old_enemy()
{
	delete this->imgEnemy;
	this->imgEnemy = NULL;
}

void old_enemy::init(rigidbody* rb, int x, int y)
{
	this->imgEnemy = new IMAGE[6];

	this->_load();

	this->initObject(coord(x, y),
		this->imgEnemy[0].getwidth(), this->imgEnemy[0].getheight());
	this->setRenderArea(this);
	this->setCollsionArea(this);
	this->setHitArea(this, coord(this->area_pad, this->area_pad),
		this->get_base_area()->get_width() - this->area_pad * 2,
		this->get_base_area()->get_height() - this->area_pad);
	this->setHealthArea(this, coord(0, -15), this->get_base_area()->get_width(), 10);

	this->setGroundCheckArea(this);

	rb->push_dynamic_objs(this);
}

void old_enemy::render()
{
	putimagePNG2(this->get_render_area()->get_coord1(), getwidth(), &this->imgEnemy[this->imgIndex], this->is_reverse, this->sa_percent);
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
	case enemy_status::IDLE:
		this->imgIndex = 4;
		break;
	case enemy_status::RUN:
		this->imgIndex = (this->imgIndex + 1) % 6;
		break;
	default:
		break;
	}
	this->hitting();
}

void old_enemy::ai()
{
	change_status();
	move();
}

void old_enemy::change_status()
{
	static int count = 0;
	++count;
	if (count < 30)
	{
		return;
	}
	count = 0;

	bool isIdle = this->status == enemy_status::IDLE;
	this->status = (enemy_status)(rand() % (int)(enemy_status::COUNT));
	if (this->status == enemy_status::RUN && isIdle)
	{
		this->is_reverse = (rand() % 2) >= 1;
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

void old_enemy::hit(bool h = true)
{
	if (h)
	{
		this->health -= 10;
		if (this->health <= 0)
		{
			this->health = this->healthMax;
		}
		playSound("res/atk.mp3");
	}
	this->is_hit = h;
}

void old_enemy::hitting()
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
	if (this->is_hit)
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

void old_enemy::_load()
{
	for (int i = 0; i < 6; i++)
	{
		sprintf_s(this->path, "res/p%d.png", i + 1);
		loadimage(&this->imgEnemy[i], this->path);
	}
}

void old_enemy::_move()
{
	this->changeOffX((this->is_reverse ? 1 : -1) * speed);
}
