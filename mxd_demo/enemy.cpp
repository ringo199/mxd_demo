
#include "enemy.h"


enemy::enemy()
{
	this->imgIndex = 4;
	this->status = enemy_status::IDLE;
	this->is_reverse = false;
	this->speed = 3;
	this->area_pad = 3;

	this->health = 30;
	this->healthMax = 30;
}

enemy::~enemy()
{
	delete this->imgEnemy;
	this->imgEnemy = NULL;
}

void enemy::init(carama_info* carama, rigidbody* rb, int x, int y)
{
	this->imgEnemy = new IMAGE[6];

	this->_load();

	this->enemy_area.init(x, y, this->imgEnemy[0].getwidth(), this->imgEnemy[0].getheight());
	this->enemy_area.set_carama(carama);

	this->hit_area.init(
		this->enemy_area.get_coord_base(), coord(this->area_pad, this->area_pad),
		this->enemy_area.get_width() - this->area_pad * 2,
		this->enemy_area.get_height() - this->area_pad);
	this->hit_area.set_carama(carama);

	this->health_area.init(
		this->enemy_area.get_coord_base(), coord(0, -15),
		this->enemy_area.get_width(), 10);

	this->health_area.set_carama(carama);

	rb->push_dynamic_objs(&this->enemy_area);
}

void enemy::render()
{
	putimagePNG2(this->enemy_area.get_coord1(), getwidth(), &this->imgEnemy[this->imgIndex], this->is_reverse, this->sa_percent);
}

void enemy::renderHP()
{
	double percent = (double)(this->health * 100 / this->healthMax) / 100;
	drawBloodBar(&this->health_area, 2, BLACK, LIGHTGRAY, RED, percent);
}

void enemy::animator()
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

void enemy::ai()
{
	change_status();
	move();
}

void enemy::change_status()
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

void enemy::move()
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

void enemy::hit(bool h = true)
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

void enemy::hitting()
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

void enemy::_load()
{
	for (int i = 0; i < 6; i++)
	{
		sprintf_s(this->path, "res/p%d.png", i + 1);
		loadimage(&this->imgEnemy[i], this->path);
	}
}

void enemy::_move()
{
	if (this->is_reverse)
	{
		this->enemy_area.changeOffX(speed);
	}
	else
	{
		this->enemy_area.changeOffX(-speed);
	}

	if (this->enemy_area.get_coord1()->x < 0)
	{
		this->enemy_area.changeX(0);
	}
}
