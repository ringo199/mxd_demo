
#ifndef __EVENT_MANAGER_H__
#define __EVENT_MANAGER_H__

#include <stdio.h>
#include <map>
#include "var.h"

using namespace std;

struct event_params
{
    long func_point;
    void* context;

    static event_params builder(long fp, void* ctx = NULL)
    {
        event_params tmp;
        tmp.func_point = fp;
        tmp.context = ctx;
        return tmp;
    }
};

class event_manager
{
public:
    event_manager();
    ~event_manager();

    void eventRegister(e_event_type type, long event_fn);
    void eventRegister(e_event_type type, long event_fn, void* event_obj);

    void eventEmit(e_event_type type);
    void eventEmit(e_event_type type, int extra);

    void clearEvent(e_event_type type);

private:
    map<e_event_type, long> _events_fn;
    map<e_event_type, void*> _events_obj;
    // map<e_event_type, event_params> _events;

};

#endif
