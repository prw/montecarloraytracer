#include "light.h"

Light::Light(double px, double py, double pz, double cr, double cg, double cb){
    p.x=px; p.y=py; p.z=pz;
    color.x=cr; color.y=cg; color.z=cb;
}
