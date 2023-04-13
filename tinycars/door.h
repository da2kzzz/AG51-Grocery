//
// Created by kniku on 09/01/2021.
//

#ifndef TINYCARS_DOOR_H
#define TINYCARS_DOOR_H
#include "Vector2D.h"
#include "glutWindow.h"
#include "constants.h"
#include <iostream>

class door {
public:
    GLuint texture;
    int x,y;
    Vector2D position;
    Vector2D orientation;
    double rot;

    door(int a,int b){
        texture=0;
        x=a;
        y=b;
        position.x=a;
        position.y=b;
    }

    door(){
        texture=0;
        x=700;
        y=500;
        rot=30;
        position.x=x;
        position.y=y;

        orientation.x=x+50;
        orientation.y=y+30;
    }

    void draw(){
        int lx,ly;
        texture = GlutWindow::loadTGATexture("../Textures/carstop.tga",lx,ly);
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
    }

};


#endif //TINYCARS_DOOR_H
