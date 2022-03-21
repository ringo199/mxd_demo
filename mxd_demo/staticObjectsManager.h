#pragma once

#ifndef __STATIC_OBJETCS_MANAGER__
#define __STATIC_OBJETCS_MANAGER__

#include "objects.h"
#include "rigidbody.h"

class staticObjetcsManager
{
public:
	staticObjetcsManager();
	~staticObjetcsManager();

	void init(rigidbody* rb);
	static_object createStaticObject();

private:
	rigidbody* _rb;
};

staticObjetcsManager::staticObjetcsManager()
{
}

staticObjetcsManager::~staticObjetcsManager()
{
}

inline void staticObjetcsManager::init(rigidbody* rb)
{
	this->_rb = rb;
}

inline static_object staticObjetcsManager::createStaticObject()
{
}



#endif
