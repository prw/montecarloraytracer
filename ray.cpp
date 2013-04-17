#include "ray.h"

Ray::Ray(){}
Ray::Ray(Vector oo, Vector dd){
    o.x=oo.x; o.y=oo.y; o.z=oo.z;
    d.x=dd.x; d.y=dd.y; d.z=dd.z;
    d.normalize();
}

