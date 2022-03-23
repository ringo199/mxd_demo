
#ifndef __SCENE_BASE_H__
#define __SCENE_BASE_H__

#include <iostream>

using namespace std;

class scene_base
{
public:
    scene_base();
    ~scene_base();

    virtual void init();
    virtual void show();
    virtual void hide();
    virtual void clear();

    // loop
    virtual void beforeEvent();
    virtual void render();
    virtual void afterEvent();

protected:

private:
};

typedef scene_base scene;

#endif
