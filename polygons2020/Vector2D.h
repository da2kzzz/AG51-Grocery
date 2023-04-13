//
// Created by 11357 on 2020/11/20.
//

#ifndef POLYGONS2020_VECTOR2D_H
#define POLYGONS2020_VECTOR2D_H

#include "math.h"
#include "iostream"
#include <cmath>
using namespace std;

//Vector2D.h file


// I want a tool to write that in C++
//Number x vector + vector obtained by the difference of 2 points + scalar product times a vector + z component of the cross product
//Vector2D a = 3*b+(d-c) + (d*c)*b + (d^c);


class Vector2D {
public:
    float x,y;
    Vector2D(float p_x,float p_y):x(p_x),y(p_y) {}; // constructor
    Vector2D() { x=y=0.0; }

    double length() const;
// returns a orthogonal vector, but normalized norm==1
    Vector2D orthoNormed(const Vector2D &u) ;


// Vector2D a, a[0]->x a[1]->y;
    float operator[](const int i) const;


    friend double operator *(const Vector2D&,const Vector2D&);
    friend const Vector2D operator *(double,const Vector2D&);
    friend const Vector2D operator +(const Vector2D&,const Vector2D&);
    friend const Vector2D operator -(const Vector2D&,const Vector2D&);
    friend const Vector2D operator -(const Vector2D&);
// z component of the cross product
    friend double operator ^(const Vector2D&,const Vector2D&);
    friend istream& operator>>(istream& f,Vector2D &p);
    friend ostream& operator<<(ostream& f,const Vector2D &p);


    friend bool operator ==(const Vector2D&,const Vector2D&);
    friend bool operator !=(const Vector2D&,const Vector2D&);
};



const Vector2D operator *(double,const Vector2D&);
double operator *(const Vector2D&,const Vector2D&);
const Vector2D operator +(const Vector2D&,const Vector2D&);
const Vector2D operator -(const Vector2D&,const Vector2D&);
const Vector2D operator -(const Vector2D&);
double operator ^(const Vector2D&,const Vector2D&);
bool operator ==(const Vector2D&,const Vector2D&);
bool operator !=(const Vector2D&,const Vector2D&);





//Vector2D.cpp file
//Complete the codes, (only one line per function)


//@Marc
//3 x v(x,y) -> (3x,3y)
const Vector2D operator *(double a,const Vector2D &v) {
    return Vector2D(a*v.x,a*v.y);
}


//@Bliss
double operator *(const Vector2D &u,const Vector2D &v) {
    return u.x*v.x+u.y*v.y; // ok for the dot product
}


//@Michael
const Vector2D operator +(const Vector2D &u,const Vector2D &v) {
    return Vector2D(u.x+v.x,u.y+v.y);
}


//@Fatou
const Vector2D operator -(const Vector2D &u,const Vector2D &v) {
    return Vector2D(u.x-v.x,u.y-v.y);
}


//@Yu Qi
// unary minus ! Vector2D a = -b;
const Vector2D operator -(const Vector2D &v) {
    return Vector2D(-v.x,-v.y);
}


//@Dana
// cross product in 2D just returns the not null component
// (u x v).z = u.x * v.y - u.y * v.x;
double operator ^(const Vector2D &u,const Vector2D &v) {
    return u.x * v.y - u.y * v.x;
}


//@Hussein
double Vector2D::length() const {
    return sqrt(x*x+y*y);
}
// from hussein :
// return sqrt(pow(v.x-u.x,2.0)*pow(v.y-u.y,2.0));

//@Shivam
/*
\u(x,y) = (y,-x) + normalize
*/
Vector2D Vector2D::orthoNormed(const Vector2D &u)  {
    double l = u.length();
    return Vector2D(u.y/l,-u.x/l);
}


//@Carlita
bool operator ==(const Vector2D &u,const Vector2D &v) {
    return (u.x == v.x && u.y == v.y); // good
}


//@Gohar
bool operator !=(const Vector2D &u,const Vector2D &v) {
    return !(u==v);
}


//@Nikuevi
/*
Returns vector2D[0]->x and vector2D[1]->y
*/
float Vector2D::operator[](int i) const {
    if(i==0){return x; }
    else if(i==1){return y;}
// you can write shorter: return (i==0)?x:y;
}






//Example of drawing:


/*glBegin(GL_LINES);
            glVertex2f(x0,y0);
            glVertex2f(x1,y1);
glEnd();


Write a short code that draws a circle, centered at (cx,cv) of radius r
double cx = 0.5,cy = 0.5;
    double a, x, y;
    double r = 0.2;
    int n = 10;
glPushMatrix();
        glTranslatef(cx,cy);
       glBegin(GL_POLYGON); // GL_LINE_LOOP
       for (int i = 0; i<n; i++) {
           a = 2.0 * M_PI * i / n;
           x = r *cos(a);
           y = r *sin(a);
           glVertex2d(x,y);
       }
       glEnd();
glPopMatrix(),*/

#endif //POLYGONS2020_VECTOR2D_H
