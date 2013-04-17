#include <iostream>
#include <algorithm>
#include <cmath>
#include <fstream>
#include "camera.h"

using namespace std;

Camera::Camera(Point pos, Vector camup, Vector dir, double w, double h){
    position = pos; up = camup; direction=dir;
    up.normalize(); direction.normalize();
    right.cross(direction,up);
    up.cross(right, direction);
    height = h; width=w;

    image=new Point * [(int)h];
    for(int i=0; i<h; i++){ //TODO gotta delete these at the end... MEMORYLEAK
        image[i] = new Point[(int)w];
    }
}

void Camera::getRay(int i, int j, Ray &r){
    double norm_i = ((i/width) - 0.5*(width/height))*(width/height);
    double norm_j = ((j/height) -0.5);

    Vector ri, u;

    ri=right; u=up;

    ri.scale(norm_i);
    u.scale(norm_j);

    //cout << "ri, u: "; ri.print(); u.print();

    r.d.add(ri,u);
    r.d.add(r.d, direction);
    r.d.add(r.d, position);
    r.d.normalize();
    r.o.x=position.x; r.o.y=position.y; r.o.z=position.z;
}

void Camera::setPixel(int i, int j, Point color){
    image[j][i]=color;
    if( color.x > largest)
        largest=color.x;
    if( color.y > largest)
        largest=color.y;
    if(color.z > largest)
        largest = color.z;
}

void Camera::writeImage(char *fname){
    // need to convert point data to 0-255 int
    // color = min(255, (int) color)
    ofstream imagefile(fname);
    int r, g, b;

    imagefile << "P3" << "\n" << width << " " << height << "\n255\n";
    for(int i=0; i<height; i++){
        for(int j=0; j<width; j++){
            r=(int)((sqrt(image[i][j].x)/sqrt(largest))*255.);
            g=(int)((sqrt(image[i][j].y)/sqrt(largest))*255.);
            b=(int)((sqrt(image[i][j].z)/sqrt(largest))*255.);
            if(r>255) r=255;
            if(g>255) g=255;
            if(b>255) b=255;
            imagefile << max(r,0) << " " << max(g,0) << " " << max(b,0) << " ";
        }
        imagefile << "\n";
    }
    imagefile.close();
}
