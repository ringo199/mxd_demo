#pragma once
#ifndef __REQUEST_H__
#define __REQUEST_H__

#include <queue>
#include <string>
#include <stdio.h>
#include <winsock2.h>
#include <json/json.h>


#pragma comment(lib, "WS2_32.lib")

#define BUF_SIZE 0x1000

using namespace std;


class request
{
public:
    request();
    ~request();

    enum class request_path
    {
        ENTRY,
        CREATE_ENEMY,
    };

    void init(string addr, int port);
    void req(request_path path);

private:
    queue<string> _req;
    queue<string> _res;

    void push_request(string);
    string build_request(request_path);

    //void create_th();

    //static DWORD WINAPI create_request(LPVOID);
    //static DWORD WINAPI dispatch_response(LPVOID);

    WSADATA     wsd;
    SOCKET      sockClient;
    SOCKADDR_IN addrSrv;

    char _buf_send[BUF_SIZE];
    char _buf_recv[BUF_SIZE];
    char _buf_tmp[BUF_SIZE];
};

#endif
