
#include "request.h"

request::request()
{
    if (WSAStartup(MAKEWORD(2, 2), &this->wsd))
    {
        printf("start up failed!\n");
        return;
    }
}

request::~request()
{
    WSACleanup();
}

void request::init(string addr, int port)
{
    this->addrSrv.sin_family = AF_INET;
    this->addrSrv.sin_addr.S_un.S_addr = inet_addr(addr.c_str());
    this->addrSrv.sin_port = htons(port);

    //this->create_th();
}

void request::req(request_path path)
{
    this->push_request(
        this->build_request(path));
}

string request::build_request(request_path path)
{
    Json::Value root;

    root["path"] = (int)path;

    switch (path)
    {
    case request_path::ENTRY:
        break;
    case request_path::CREATE_ENEMY:
        break;
    default:
        break;
    }

    return root.toStyledString();
}

void request::push_request(string str)
{
    this->_req.push(str);
}
/*
void request::create_th()
{
    static HANDLE hThread1 = CreateThread(NULL, 0, this->create_request, (LPVOID)this, 0, NULL);
    static HANDLE hThread2 = CreateThread(NULL, 0, this->dispatch_response, (LPVOID)this, 0, NULL);

    CloseHandle(hThread1);
    CloseHandle(hThread2);
}

DWORD WINAPI request::create_request(LPVOID args)
{
    request* p = (request*)args;

    for (;;)
    {
        if (!p->_req.empty())
        {
            // 创建套接字
            this->sockClient = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
            // 连接服务器
            connect(this->sockClient, (SOCKADDR*)&p->sockAddr, sizeof(SOCKADDR));

            sprintf(p->_buf_send, "%s", p->_req.front().c_str());
            p->_req.pop();
            send(sock, p->_buf_send, BUF_SIZE, 0);

            // 接受服务器传回来的消息
            recv(sock, p->_buf_recv, BUF_SIZE, 0);
            sprintf(p->_buf_tmp, "%s", p->_buf_recv);
            p->_res.push(p->_buf_tmp);
            // 重置缓冲区
            memset(p->_buf_send, 0, BUF_SIZE);
            memset(p->_buf_recv, 0, BUF_SIZE);
            memset(p->_buf_tmp, 0, BUF_SIZE);

            // 关闭套接字
            closesocket(sock);
        }
    }
}

DWORD WINAPI request::dispatch_response(LPVOID args)
{
    request* p = (request*)args;
    for (;;)
    {
        if (!p->_res.empty())
        {
            cout << p->_res.front() << endl;
            Json::Reader reader;
            Json::Value root;

            if (reader.parse(p->_res.front(), root))
            {
                int path = root["path"].asInt();

                switch ((request_path)path)
                {
                case request_path::ENTRY:
                    cout << "ENTRY " << root["message"] << endl;
                    break;
                case request_path::CREATE_ENEMY:
                    cout << "CREATE_ENEMY " <<
                        root["data"]["type"] <<
                        root["data"]["x"] <<
                        root["data"]["y"] <<
                        endl;
                    break;
                default:
                    break;
                }
            }

            p->_res.pop();
        }
    }
}
*/