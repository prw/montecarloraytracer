#ifndef SCENE_H
#define SCENE_H
#include "object.h"
#include "light.h"

class Scene {
public:
    Object * objs[1000];
    Light * lights[1000];
    int objCount;
    int lCount;
    Scene();
    void addObject(Object *o);
    int objectCount();
    void addLight(Light *l);
    int lightCount();
    Object * getObject(int i);
    Light * getLight(int i);
};

#endif // SCENE_H
