#pragma once

#ifndef __MAIN_LOOP_H__
#define __MAIN_LOOP_H__

#include "tools.h"
#include "inputEvent.h"
#include "global.h"
#include "collision.h"
#include "gameManager.h"
#include "ui_manager.h"
#include "event_manager.h"

#define FRAMES 16

void init(global*);
void loop(global*);
void initialize();

#endif
