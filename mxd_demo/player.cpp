
#include "player.h"


player_info::player_info()
{
	this->status = player_status::IDLE;
	this->imgIndex = 0;
	this->speed = 1;
	this->is_reverse = false;
	this->is_runing = false;
	this->area_pad = 30;
	this->area_atk_x = 50;
	this->is_hit = false;
	this->sa_percent = 1.0;

	this->health = 50;
	this->healthMax = 50;
}

player_info::~player_info()
{
}

void player_info::init(carama_info* carama, rigidbody* rb, coord coo)
{
	this->_carama = carama;
	this->_load();

	this->player_area.init(coo,
		this->imgPlayer[0].getwidth(), this->imgPlayer[0].getheight());
	this->player_area.set_carama(carama);

	this->hit_area.init(this->player_area.get_coord_base(), coord(this->area_pad, this->area_pad),
		this->player_area.get_width() - 2 * this->area_pad, this->player_area.get_height() - this->area_pad);
	this->hit_area.set_carama(carama);

	this->atk_area.init(this->player_area.get_coord_base(), coord(this->area_pad + this->player_area.get_width(), this->area_pad),
		this->area_atk_x, this->player_area.get_height() - 2 * this->area_pad);
	this->atk_area.set_carama(carama);

	rb->push_dynamic_objs(&this->player_area);
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
	this->player_area.changeOffCoord(coo);

	if (!this->is_reverse)
	{
		this->atk_area.changeRefOffCoord(
			coord(this->area_pad + this->player_area.get_width(), this->area_pad));
	}
	else
	{
		this->atk_area.changeRefOffCoord(
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
	if (!this->is_jumping)
	{
		this->is_jumping = true;
		this->jump_v = -30.0f;
		this->_move(coord(0, this->jump_v));
		this->is_runing = false;
		s_update = true;
		playSound("res/jump.mp3");
	}
	if (this->status != player_status::JUMP)
	{
		this->status = player_status::JUMP;
	}
}

void player_info::attack()
{
	if (!this->is_attacking)
	{
		this->is_attacking = true;
		this->imgIndex = 0;
		this->is_runing = false;
		s_update = true;
	}
	if (this->status != player_status::ATTACK)
	{
		this->status = player_status::ATTACK;
	}
}

void player_info::hit(bool h = true)
{
	if (h)
	{
		this->health -= 10;
		if (this->health <= 0)
		{
			this->health = this->healthMax;
		}
	}
	this->is_hit = h;
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

void player_info::droping()
{
	//if (this->player_area.get_coord1()->y <= 300)
	//{
	//	return;
	//}
	//this->jump_v += 0.3 * GRAVITY;
	//this->_move(coord(0, this->jump_v));
	//if (this->player_area.get_coord1()->y >= 300 && this->is_jumping)
	//{
	//	this->is_jumping = false;
	//	this->player_area.changeY(300);
	//	if (this->status == player_status::JUMP)
	//	{
	//		this->status = player_status::IDLE;
	//	}
	//}
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
		this->is_attacking = false;
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
	//this->droping();
	this->hitting();
}

void player_info::render()
{
	switch (this->status)
	{
	case player_status::IDLE:
	case player_status::RUN:
	case player_status::JUMP:
		putimagePNG2(player_area.get_coord1(), &this->imgPlayer[this->imgIndex], this->is_reverse, this->sa_percent);
		break;
	case player_status::ATTACK:
		putimagePNG2(player_area.get_coord1(), &this->imgAtkPlayer[this->imgIndex], this->is_reverse, this->sa_percent);
		break;
	default:
		break;
	}
	this->renderHP();
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

void player_info::renderHP()
{
	double percent = (double)(this->health * 100 / this->healthMax) / 100;
	drawBloodBar(10, 10, 300, 20, 3, BLACK, LIGHTGRAY, RED, percent);
}