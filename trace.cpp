#include "tracer.h"
#include "scene.h"
#include "camera.h"
#include "object.h"
#include "vector.h"
#include "point.h"

#include <iostream>

using namespace std;


int main(){
    Point camPoint (0,0,0);
    Vector camUp(0,1,0);
    Vector camDir(-0.3,0,-1);

    Camera c (camPoint, camUp, camDir, 800, 800);

    Light l1 (0,15,0, .5, .5, .52);
    Light l2 (10, 0, -6, .5, .5, .5);
    Light l3 ( 0, -20, 10, 0.52, 0.5, .5);
    Light l4 (-6,-5,-18,.2,.2,.5);
    
    Point so1 (-2,3,-15);
    Point sc1 (.1,.7,.1);
    Sphere s1 (so1, 3.0, sc1, .1, 0.8, 2000.0);

    Point so2 (-10,-6, -30);
    Point sc2 (1.0,1.0,1.);
    Sphere s2 (so2, 10, sc2, 0.8, 0.01, 2000.);

    Point so3 (1,-1, -20);
    Point sc3 (1,1,1);
    Sphere s3 (so3, 3.0, sc3, 0.0, 1., 2000.);

    Point so4 (-9,1, -15);
    Point sc4 (0.9,.1,.1);
    Sphere s4 (so4, 3.0, sc4, 0.2, 0.8, 1000.);
    
    Point so5 (1,-4,-14);
    Point sc5 (0.9,.1,.1);
    Sphere s5 (so5, 1.5, sc5, 0.9, 0.0, 2.);

    Vector pn1 (0,-1,0.1);
    Point pc1(.1,.8,.4);
    Plane p1 (pn1, 4.0, pc1, 0.7, 0.2, 1000.0 );

    Vector pn2 (0,0,-1);
    Point pc2(.7,.7,.7);
    Plane p2 (pn2, 20.0, pc2, 1.0, 0.0, 1000.0 );

    Scene scene;

    scene.addLight(&l1);
    scene.addLight(&l2);
    scene.addLight(&l3);
    scene.addLight(&l4);
    scene.addObject(&s1);
    scene.addObject(&s2);
    scene.addObject(&s3);
    
    scene.addObject(&p1);
    scene.addObject(&p2);
    
    scene.addObject(&s4);
    scene.addObject(&s5);

    Tracer t ( &c, &scene);

    char fname[] = "output/traceaa.ppm";
    t.trace(fname, 4, 4);

    return 0;

}
