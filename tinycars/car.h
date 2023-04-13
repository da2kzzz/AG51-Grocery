//
// Created by kniku on 04/01/2021.
//

#ifndef TINYCARS_CAR_H
#define TINYCARS_CAR_H
#include "Vector2D.h"
#include "glutWindow.h"
#include <iostream>
const  float  parkwidth =80;
const  float  parkheight =40;
const  float  carwidth =80;
const  float  carheight =32;
#include "door.h"
#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include "vector"

using namespace std;

class car {
public:
    GLuint texture;
    int x=100;int y=100;
    Vector2D orientation;
    Vector2D p0;
    Vector2D v0;
    Vector2D p1;
    Vector2D v1;
    double velocity;
    double dt;
    double t;
    double epsilon=0.01;
    Vector2D destination;
    Vector2D position;
    vector<Vector2D> curvep;
    double vo;
    double voo;

    car(int a,int b){
        texture=0;
        x=a;
        y=b;
        p0.x=a;
        p0.y=b;
    }

    car(){
        texture=0;
        x=500;
        y=300;
        p0.x=x;
        p0.y=y;
        vo=0;


        v0.x=x+50;
        v0.y=y+50;

    }

    Vector2D traj(float  t){
        Vector2D a=2*(p0-p1)+v0+v1;
        Vector2D b=3*(p1-p0)-2*v0-v1;
        Vector2D c=v0;
        Vector2D d=p0;


       /* Vector2D a=vo+voo+2*(p0-p1);
        Vector2D b=(-1)*(2*vo+voo)+3*(p1-p0);
        double c=vo;
        Vector2D d=p0;*/

        //return (3*t*t*t*a)+(t*t*b)+(t*c)+d;
        //vo=(t*(3*t*a + 2*b)) + c;
        //return t*((t*(t*a + b)) + c) + d;
        return (t*c)+(t*t*t*a)+(t*t*b)+d;

    }


    void drwcurve(){
        cout << "click1" <<endl;

        move(10,10);
    }

    void  move( double  dt ,  float  velocity ){

        Vector2D Pi= traj(t),Pj ;
        double d=dt*velocity ;
        while  (d>0.0 && t<1.0){
            t+=epsilon ;
            Pj = traj(t) ;
            d-=( Pj-Pi ) . norm () ;
            Pi=Pj ;
            cout << "x: " << Pi.x <<" y: " <<Pi.y <<endl;
            cout << "v0: " << v0.x <<" v0: " <<v0.y <<endl;
            curvep.push_back( Vector2D(Pi.x,Pi.y));
        }

        //return  t ;
    }

    void curve(door d){
        p1=d.position;
        v1=d.orientation;
        move(10,100);
    }

    void curvedr(){
        glBegin(GL_LINE_STRIP);
        auto current = curvep.begin();
        while (current != curvep.end()){
            glVertex2f(current->x,current->y);
            current++;
        }
        current = curvep.begin();

        glEnd();
    }

    void go(){
        auto current = curvep.begin();
        while (current != curvep.end()){
            x=current->x;y=current->y;
            current++;
            draw();
            glEnd();
        }


    }

    /*void onUpdate ( double dt ) {
        static double elapsedTime =0;
        if ( currentCar ) {
            elapsedTime+=dt ;
             if ( currentCar−>move( dt ,100.0f ) >1) {
                currentCar= nullptr ;
                cout << "Elapsed time=" << elapsedTime << "s"  << endl;
            }
        }
    }*/

    void draw(){
        int lx,ly;
        texture = GlutWindow::loadTGATexture("../Textures/bluecar.tga",lx,ly);
        assert(texture!=0);
        glBindTexture(GL_TEXTURE_2D,texture);
        glPushMatrix();
        glTranslatef(x,y,1.0);
        glBegin(GL_QUADS);
        glTexCoord2f(0.0,0.0);
        glVertex2f(0.0,0.0);
        glTexCoord2f(1.0,0.0);
        glVertex2f(96.0,0.0);
        glTexCoord2f(1.0,1.0);
        glVertex2f(96.0,45.0);
        glTexCoord2f(0.0,1.0);
        glVertex2f(0.0,45.0);
        glEnd();
        glPopMatrix();

/*
        glTranslatef(x,y,1.0);
        //glRotatef(30, 0, 0, 1);
        glBegin(GL_QUADS);
        /*glTexCoord2f(0.0,0.0);
        glVertex2f(0.0,0.0);
        glTexCoord2f(1.0,0.0);
        glVertex2f(96.0,0.0);
        glTexCoord2f(1.0,1.0);
        glVertex2f(96.0,96.0);
        glTexCoord2f(0.0,1.0);
        glVertex2f(0.0,96.0);

        glTexCoord2f(0.0,0.0);
        glVertex2f(-carwidth, carheight);
        glTexCoord2f(1.0,0.0);
        glVertex2f(carwidth, -carheight);
        glTexCoord2f(1.0,1.0);
        glVertex2f(carwidth, carheight);
        glVertex2f(0.0,1.0);
        glVertex2f(-carwidth, carheight);
        glEnd();

        glPopMatrix();*/



    }

};


#endif //TINYCARS_CAR_H
