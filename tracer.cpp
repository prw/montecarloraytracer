#include <cmath>
#include <algorithm>
#include <stdlib.h>
#include <ctime>
#include "tracer.h"
#include "ray.h"
#include "point.h"
#include "vector.h"

#include <iostream>
using namespace std;

Tracer::Tracer(Camera *cc, Scene *ss){
    c=cc;
    s=ss;
}
void Tracer::trace(char *img, int recursions, int aa){
    Ray r;
    Point color;
    clock_t start, end;
    double elapsed;
    for(int i=0; i<c->width; i++){
	start = clock();
		
        for(int j=0; j<c->height; j++){
	    //cout << "." << flush;
            color.x=0; color.y=0; color.z=0;
            for(int a=0; a<aa; a++){
                c->getRay(i,j,r);
                r.d.x+=(0.5-((double) rand()/RAND_MAX))*(1.0/c->height);
                r.d.y+=(0.5-((double) rand()/RAND_MAX))*(1.0/c->width);
                r.d.normalize();
                _trace(r, color, recursions);
            }
            //color.scale(1.0/aa);
            c->setPixel(i,j,color);
        }
        end = clock();
        elapsed = (double)(end - start)/CLOCKS_PER_SEC;

        cout << "\r" <<i<<" of "<< c->width << " Row elapsed (s): " << elapsed << flush;
    }
    cout << endl << "Writing image.\n";
    c->writeImage(img);
}
void Tracer::_trace(Ray &r, Point &color, int recurse){
    Point reflectedColor (0,0,0), diffuse (0,0,0), colorTmp, mcColor (0,0,0);
    Vector normal;
    Light *tmplight;
    Ray reflectedRay, lRay, mcRay;
    Object *close;
    double t, dtmp;
    int tmp, closeI, ldist;

    if( recurse < 0)
        return;

    // need to find closest intersection
    t=getClosest(r, closeI, false);
    if( t < 0.0){
            return;
    }
    t-=0.001;
    close = s->getObject(closeI);
    // need to find reflected + normal

    close->getReflected(r, t, reflectedRay, normal);

    // need to compute light->intersection point
    // kd*sum( lightColor.scale(lRay.d.(normal))
    for(int i=0; i<s->lightCount(); i++){
        lRay.o=r.d; // compute point on suface, d*t+o
        lRay.o.scale(t);
        lRay.o.add(lRay.o, r.o);

        tmplight = s->getLight(i);

        lRay.d.sub(tmplight->p, lRay.o);

        ldist = lRay.d.length();
        lRay.d.normalize();

        dtmp = getClosest(lRay, tmp, false);
        if(dtmp < 0.0 || dtmp > ldist){
            // means its not in shadow, obj behind or ahead of obj/light
            colorTmp=tmplight->color;
            colorTmp.scale(1.0+1.0/ldist);
            colorTmp.scale(max(lRay.d.dot(normal)*close->diffuse, 0.0)); // compute diffuse
            color.add(color, colorTmp);
			
            Vector n2, lRefl; // need to vector to point to the viewer
            n2=normal;
            n2.scale(2.0*lRay.d.dot(n2));
            lRefl.sub(lRay.d, n2);
            lRefl.normalize();
            r.d.negate();
            colorTmp=tmplight->color; // compute specular
            colorTmp.scale( pow(r.d.dot(lRefl), close->shiny) * close->specular);
            color.add(color, colorTmp);
            r.d.negate();
        }

    }
	
	// Monte carlo raytrace - need to create random ray with normal.dot(ray) > 0
	mcRay.o=reflectedRay.o;
	for( int i=0; i<14; i++){
		do {
			mcRay.d.x=(0.5-((double) rand()/RAND_MAX));
			mcRay.d.y=(0.5-((double) rand()/RAND_MAX));
			mcRay.d.z=(0.5-((double) rand()/RAND_MAX));
			mcRay.d.normalize();
		} while( normal.dot(mcRay.d)<=0.0 );
		
		if( normal.dot(mcRay.d) > 0.1){
			_trace(mcRay, mcColor, recurse - 1);
			mcColor.scale(normal.dot(mcRay.d)*close->diffuse);
			mcColor.x*=close->color.x; mcColor.y*=close->color.y; mcColor.z*=close->color.z;
			color.add(color, mcColor);
			mcColor.x=0; mcColor.y=0; mcColor.z=0;
		}
	}
	
    // need to recurse on reflected ray
    _trace(reflectedRay, reflectedColor, recurse - 1);

    colorTmp=reflectedColor;
    colorTmp.scale(reflectedRay.d.dot(normal)*close->specular);
	colorTmp.x*=close->color.x; colorTmp.y*=close->color.y; colorTmp.z*=close->color.z;
    color.add(color, colorTmp);

    color.x*=close->color.x; color.y*=close->color.y; color.z*=close->color.z;

    //color.x+=0.05*close->diffuse; color.y+=0.05*close->diffuse; color.z+=0.05*close->diffuse; // this is ambient TODO FIXME

    // need to find transmitted ray TODO

    // need to recurse on that ray TODO
}
double Tracer::getClosest(Ray &r, int &closeObj, bool check){
    Object *curr;
    double closeT=INFINITY, t;
    for(int i=0; i < s->objCount; i++){
        //cout << "getClosest: i:" << i << endl;
        curr = s->getObject(i);
        t=curr->intersect(r);
        if( t>0.0 && t<closeT ){
            closeT=t;
            closeObj=i;
        }
        if( t>0.0 && check){
            return t;
        }
    }
    if (closeT != INFINITY)
        return closeT;
    else
        return -1.0;
}
