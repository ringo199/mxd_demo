#pragma once
#ifndef __GLOBAL_H__
#define __GLOBAL_H__

#include "carama.h"
#include "player.h"
#include "rigidbody.h"
#include "enemy.h"
#include "var.h"


class global
{
public:
	global();
	~global();

	void init(carama_info* carama, player_info* pi, enemy* ene, rigidbody* rb);

	player_info*	pi;
	enemy*			ene;
	rigidbody*		rb;
	carama_info*	carama;
	bool*			update;

private:

};


#endif
