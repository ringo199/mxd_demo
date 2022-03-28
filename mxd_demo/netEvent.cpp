#include "netEvent.h"

#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib")

#include "global.h"

#include <queue>
#include <unordered_map>
#include <sstream>

using namespace global;

#define _WINSOCK_DEPRECATED_NO_WARNINGS

#define BUF_SIZE 1024

DWORD WINAPI create_net_send_th(LPVOID);
DWORD WINAPI create_net_recv_th(LPVOID);

void netEvent()
{
	HANDLE hSendThread = CreateThread(NULL, 0, create_net_send_th, NULL, 0, NULL);
    HANDLE hRecvThread = CreateThread(NULL, 0, create_net_recv_th, NULL, 0, NULL);

	CloseHandle(hSendThread);
    CloseHandle(hRecvThread);
}

char bufSend[BUF_SIZE];
char bufRecv[BUF_SIZE];
int sock;

#define port 6572
#define addr "127.0.0.1"

void initnet()
{
    WSADATA ws;
    WSAStartup(MAKEWORD(2, 2), &ws);
    //创建一个用来通讯的socket
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0)
    {
        perror("socket");
    }

    //需要connect的是对端的地址，因此这里定义服务器端的地址结构体
    struct sockaddr_in server;
    server.sin_family = AF_INET;
    //server.sin_port =htons(6000);
    // server.sin_addr.s_addr = inet_addr("127.0.0.1");
    server.sin_port = htons(port);
    server.sin_addr.s_addr = inet_addr(addr);
    int len = sizeof(struct sockaddr_in);
    if (connect(sock, (struct sockaddr*)&server, len) < 0)
    {
        perror("connect");
    }

    printf("已连接到%s:%d\n", addr, port);
}

struct messageStu
{
    int type;
    cJSON* data;
};

queue<messageStu> _messageQueue;

void sendMessage_type_1()
{
    messageStu ms = { 1, nullptr };
    _messageQueue.push(ms);
}

void sendMessage_type_2(int id)
{
    cJSON* data = cJSON_CreateObject();
    cJSON_AddNumberToObject(data, "id", id);
    messageStu ms = { 2, data };
    _messageQueue.push(ms);
}

void sendMessage_type_3(int areaId, const char* username, const char* password)
{
    cJSON* data = cJSON_CreateObject();
    cJSON_AddNumberToObject(data, "id", areaId);
    cJSON_AddStringToObject(data, "username", username);
    cJSON_AddStringToObject(data, "password", password);
    messageStu ms = { 3, data };
    _messageQueue.push(ms);
}

void sendMessage_type_4(int userId)
{
    cJSON* data = cJSON_CreateObject();
    cJSON_AddNumberToObject(data, "id", userId);
    messageStu ms = { 4, data };
    _messageQueue.push(ms);
}

void sendMessage_type_5(int hp, int mp, int exp)
{
    int userId = GetSessionManager()->GetSession(SESSION_USER_ID);

    cJSON* data = cJSON_CreateObject();
    cJSON_AddNumberToObject(data, "id", userId);
    cJSON_AddNumberToObject(data, "hp", hp);
    cJSON_AddNumberToObject(data, "mp", mp);
    cJSON_AddNumberToObject(data, "exp", exp);
    messageStu ms = { 5, data };
    _messageQueue.push(ms);
}

void sendMessage_type_6(int gameMapID)
{
    int userId = GetSessionManager()->GetSession(SESSION_USER_ID);

    cJSON* data = cJSON_CreateObject();
    cJSON_AddNumberToObject(data, "characterID", userId);
    cJSON_AddNumberToObject(data, "gameMapID", gameMapID);
    messageStu ms = { 6, data };
    _messageQueue.push(ms);
}
void sendMessage_type_6(int gameMapID, int from)
{
    int userId = GetSessionManager()->GetSession(SESSION_USER_ID);

    cJSON* data = cJSON_CreateObject();
    cJSON_AddNumberToObject(data, "characterID", userId);
    cJSON_AddNumberToObject(data, "gameMapID", gameMapID);
    cJSON_AddNumberToObject(data, "from", from);
    messageStu ms = { 6, data };
    _messageQueue.push(ms);
}

void sendMessage_type_7(int dialogID)
{
    cJSON* data = cJSON_CreateObject();
    cJSON_AddNumberToObject(data, "id", dialogID);
    messageStu ms = { 7, data };
    _messageQueue.push(ms);
}

void sendMessage_type_255(const char* content)
{
    int userId = GetSessionManager()->GetSession(SESSION_USER_ID);

    cJSON* data = cJSON_CreateObject();
    cJSON_AddNumberToObject(data, "id", userId);
    cJSON_AddStringToObject(data, "content", content);
    messageStu ms = { 255, data };
    _messageQueue.push(ms);
}

void sendMessage(messageStu ms)
{
    cJSON* sendData = cJSON_CreateObject();
    cJSON_AddNumberToObject(sendData, "type", ms.type);
    cJSON_AddItemToObject(sendData, "data", ms.data);

    sprintf(bufSend, "%s", cJSON_PrintUnformatted(sendData));
    send(sock, bufSend, BUF_SIZE, 0);
    memset(bufSend, 0, BUF_SIZE);
}

void dispatchMessage()
{
    recv(sock, bufRecv, BUF_SIZE, 0);
    if (strcmp(bufRecv, "") == 0)
    {
        return;
    }
    printf("Data recv from Server Socket: %s\n", bufRecv);
    cJSON* recvData = cJSON_Parse(bufRecv);
    cJSON* code = cJSON_GetObjectItem(recvData, "code");
    cJSON* type = cJSON_GetObjectItem(recvData, "type");
    printf("msg_type: %d\n", type->valueint);
    if (code->valueint != 0)
    {
        cJSON* message = cJSON_GetObjectItem(recvData, "message");
        printf("code: %d, message: %s\n", code->valueint, message->valuestring);
        if (type->valueint == 3)
        {
            GetEventManager()->eventEmit(NET_TYPE_3_FAIL, message->valuestring);
        }
    }
    else
    {
        if (type->valueint == 1)
        {
            cJSON* data = cJSON_GetObjectItem(recvData, "data");
            cJSON* rows = cJSON_GetObjectItem(data, "rows");
            GetEventManager()->eventEmit(NET_TYPE_1, cJSON_PrintUnformatted(rows));
        }
        else if (type->valueint == 2)
        {
            cJSON* data = cJSON_GetObjectItem(recvData, "data");
            cJSON* rows = cJSON_GetObjectItem(data, "rows");
            GetEventManager()->eventEmit(NET_TYPE_2, cJSON_PrintUnformatted(rows));
        }
        else if (type->valueint == 3)
        {
            cJSON* data = cJSON_GetObjectItem(recvData, "data");
            cJSON* rows = cJSON_GetObjectItem(data, "rows");
            GetEventManager()->eventEmit(NET_TYPE_3_SUCCESS, cJSON_PrintUnformatted(rows));
        }
        else if (type->valueint == 5)
        {
            cJSON* data = cJSON_GetObjectItem(recvData, "data");
            cJSON* level = cJSON_GetObjectItem(data, "level");
            cJSON* hp = cJSON_GetObjectItem(data, "hp");
            cJSON* mp = cJSON_GetObjectItem(data, "mp");
            cJSON* exp = cJSON_GetObjectItem(data, "exp");
            cJSON* max_hp = cJSON_GetObjectItem(data, "max_hp");
            cJSON* max_mp = cJSON_GetObjectItem(data, "max_mp");
            cJSON* max_exp = cJSON_GetObjectItem(data, "max_exp");
            cJSON* atk = cJSON_GetObjectItem(data, "atk");
            cJSON* def = cJSON_GetObjectItem(data, "def");

            GetSessionManager()->SetSession(SESSION_LEVEL, level->valueint);
            GetSessionManager()->SetSession(SESSION_HP, hp->valueint);
            GetSessionManager()->SetSession(SESSION_MP, mp->valueint);
            GetSessionManager()->SetSession(SESSION_EXP, exp->valueint);
            GetSessionManager()->SetSession(SESSION_MAX_HP, max_hp->valueint);
            GetSessionManager()->SetSession(SESSION_MAX_MP, max_mp->valueint);
            GetSessionManager()->SetSession(SESSION_MAX_EXP, max_exp->valueint);
            GetSessionManager()->SetSession(SESSION_ATK, atk->valueint);
            GetSessionManager()->SetSession(SESSION_DEF, def->valueint);
        }
        else if (type->valueint == 6)
        {
            cJSON* data = cJSON_GetObjectItem(recvData, "data");
            GetEventManager()->eventEmit(NET_TYPE_6, cJSON_PrintUnformatted(data));
        }
        else if (type->valueint == 7)
        {
            cJSON* data = cJSON_GetObjectItem(recvData, "data");
            GetEventManager()->eventEmit(NET_TYPE_7, cJSON_PrintUnformatted(data));
        }
        else if (type->valueint == 255)
        {
            cJSON* data = cJSON_GetObjectItem(recvData, "data");
            cJSON* name = cJSON_GetObjectItem(data, "name");
            cJSON* content = cJSON_GetObjectItem(data, "content");

            stringstream ss;
            ss << name->valuestring << ": " << content->valuestring;

            GetEventManager()->eventEmit(NET_TYPE_255, ss.str());
        }
    }

    memset(bufRecv, 0, BUF_SIZE);
}


DWORD WINAPI create_net_send_th(LPVOID args)
{
    initnet();
	for (;;)
	{
        while (_messageQueue.size() != 0)
        {
            sendMessage(_messageQueue.front());
            _messageQueue.pop();
        }
	}
    closesocket(sock);
}

DWORD WINAPI create_net_recv_th(LPVOID args)
{
    for (;;)
    {
        dispatchMessage();
    }
}
