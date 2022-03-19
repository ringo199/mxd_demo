
#include "global.h"

global::global()
{
	this->update = &s_update;
}

global::~global()
{
}

void global::init(carama_info* carama, player_info* pi, enemy* ene, rigidbody* rb)
{
	this->carama = carama;
	this->pi	 = pi;
	this->ene	 = ene;
	this->rb	 = rb;
}
