#pragma once

#ifndef __MAIN_LOOP_H__
#define __MAIN_LOOP_H__

#include "tools.h"
#include "render.h"
#include "inputEvent.h"
#include "global.h"
#include "beforeEvent.h"
#include "afterEvent.h"
#include "collision.h"

#define FRAMES 16

void init(global*);
void loop(global*);
void initialize();

#endif
