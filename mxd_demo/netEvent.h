#pragma once
#ifndef __NET_EVENT_H__
#define __NET_EVENT_H__

#include "cJSON.h"

void netEvent();
void sendMessage_type_1();
void sendMessage_type_2(int);
void sendMessage_type_3(int areaId, const char* username, const char* password);
void sendMessage_type_4(int);
void sendMessage_type_5(int hp, int mp, int exp);
void sendMessage_type_6(int gameMapID);
void sendMessage_type_6(int gameMapID, int from);
void sendMessage_type_7(int dialogID);
void sendMessage_type_255(const char* content);

#endif // !__NET_EVENT_H__
