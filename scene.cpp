#include <iostream>
#include "scene.h"
using namespace std;
Scene::Scene(){
    objCount=0;
    lCount=0;
}
void Scene::addObject(Object *o){
    //cout << "adding object at "<< objCount << endl;
    objs[objCount++]=o;
}
void Scene::addLight(Light *l){
    lights[lCount++]=l;
}
int Scene::objectCount(){
    return objCount;
}
int Scene::lightCount(){
    return lCount;
}
Object * Scene::getObject(int i){
    //cout << "i is:" << i << endl;
    if( i<objCount )
        return objs[i];
    else
        std::cout << "ERROR: getObject i is "<< i << std::endl;
}
Light * Scene::getLight(int i){
    return lights[i];
}
