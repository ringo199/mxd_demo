
#include "event_manager.h"


event_manager::event_manager()
{
}

event_manager::~event_manager()
{
}

void event_manager::eventRegister(e_event_type type, long event_fn)
{
    if (this->_events_fn.find(type) != this->_events_fn.end())
    {
        printf("event is register\n");
        //return;
    }

    this->_events_fn.insert(make_pair(type, event_fn));
}

void event_manager::eventRegister(e_event_type type, long event_fn, void* event_obj)
{
    if (this->_events_fn.find(type) != this->_events_fn.end())
    {
        printf("event is register\n");
        //return;
    }

    this->_events_fn.insert(make_pair(type, event_fn));
    this->_events_obj.insert(make_pair(type, event_obj));
}

void event_manager::eventEmit(e_event_type type)
{
    if (this->_events_fn.find(type) == this->_events_fn.end())
    {
        printf("event is not register\n");
        return;
    }

    typedef void* (*FUNC)(void*);

    if (this->_events_obj.find(type) == this->_events_obj.end())
    {
        ((FUNC)this->_events_fn.find(type)->second)(NULL);
    }
    else
    {
        ((FUNC)this->_events_fn.find(type)->second)(this->_events_obj.find(type)->second);
    }
}

void event_manager::eventEmit(e_event_type type, int extra)
{
    if (this->_events_fn.find(type) == this->_events_fn.end())
    {
        printf("event is not register\n");
        return;
    }

    typedef void* (*FUNC)(int);
    typedef void* (*FUNC2)(void*, int);

    if (this->_events_obj.find(type) == this->_events_obj.end())
    {
        ((FUNC)this->_events_fn.find(type)->second)(extra);
    }
    else
    {
        ((FUNC2)this->_events_fn.find(type)->second)(this->_events_obj.find(type)->second, extra);
    }
}

void event_manager::eventEmit(e_event_type type, string extra)
{
    if (this->_events_fn.find(type) == this->_events_fn.end())
    {
        printf("event is not register\n");
        return;
    }

    typedef void* (*FUNC)(string);
    typedef void* (*FUNC2)(void*, string);

    if (this->_events_obj.find(type) == this->_events_obj.end())
    {
        ((FUNC)this->_events_fn.find(type)->second)(extra);
    }
    else
    {
        ((FUNC2)this->_events_fn.find(type)->second)(this->_events_obj.find(type)->second, extra);
    }
}

void event_manager::clearEvent(e_event_type type)
{
    if (this->_events_fn.find(type) == this->_events_fn.end())
    {
        printf("event is not register\n");
        return;
    }
    this->_events_fn.erase(type);

    if (this->_events_obj.find(type) != this->_events_obj.end())
    {
        this->_events_obj.erase(type);
    }
}
