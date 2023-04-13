//
// Created by bpiranda on 22/11/2019.
//

#ifndef TRIANGLE_H
#define TRIANGLE_H
#include <GL/glut.h>
#include "Vector2D.h"

const float BLACK[4]={0.0,0.0,0.0,1.0f};
const float GREY[4]={0.75f,0.75f,0.75f,1.0f};
const float RED[4]={1.0f,0.0,0.0,1.0f};
const float ORANGE[4]={1.0f,0.27f,0.0,1.0f};
const float YELLOW[4]={1.0f,1.0f,0.0,1.0f};
const float GREEN[4]={0.0,1.0f,0.0,1.0f};
const float BLUE[4]={0.0,0.0,1.0f,1.0f};

class Triangle {
public:
    Vector2D *ptr[3];
    bool isHighlighted;
    Vector2D circumCenter;
    float circumRadius;

    Triangle(Vector2D *ptr1,Vector2D *ptr2,Vector2D *ptr3) {
        ptr[0] = ptr1;
        ptr[1] = ptr2;
        ptr[2] = ptr3;
        isHighlighted = false;
        calculateCircle();
    }

    void updateVertices(Vector2D *ptr1,Vector2D *ptr2,Vector2D *ptr3) {
        ptr[0] = ptr1;
        ptr[1] = ptr2;
        ptr[2] = ptr3;
        isHighlighted = false;
        calculateCircle();
    }

    void calculateCircle() {
        // calculate circle parameters
        circumCenter=*ptr[0];
        circumRadius = 50.0;
    }

    void onMouseMove(const Vector2D& pos) {
        isHighlighted=isInside(pos);
    }

    bool isOnTheLeft(const Vector2D *P,const Vector2D *P1,const Vector2D *P2) {
        Vector2D AB = *P2-*P1,
                AP = *P-*P1;

        return (AB.x*AP.y - AB.y*AP.x)>=0;
    }

    bool isEmpty(const vector<Vector2D*> &tmp,int n) {
        auto p=tmp.begin()+n;
        while (p!=tmp.end() && (!isOnTheLeft(*p,ptr[0],ptr[1]) || !isOnTheLeft(*p,ptr[1],ptr[2]) || !isOnTheLeft(*p,ptr[2],ptr[0]))) {
            p++;
        }
        return p==tmp.end();
    }

    bool isInside(const Vector2D &P) {
        return isOnTheLeft(&P,ptr[0],ptr[1]) && isOnTheLeft(&P,ptr[1],ptr[2]) && isOnTheLeft(&P,ptr[2],ptr[0]);
    }

    void draw() {
        glColor3fv(isHighlighted?ORANGE:YELLOW);
        glBegin(GL_TRIANGLES);
        glVertex2f(ptr[0]->x,ptr[0]->y);
        glVertex2f(ptr[1]->x,ptr[1]->y);
        glVertex2f(ptr[2]->x,ptr[2]->y);
        glEnd();
        glColor3fv(BLACK);
        glBegin(GL_LINE_LOOP);
        glVertex2f(ptr[0]->x,ptr[0]->y);
        glVertex2f(ptr[1]->x,ptr[1]->y);
        glVertex2f(ptr[2]->x,ptr[2]->y);
        glEnd();

    }

    void drawCircle() {
        // draw circle
        if (isHighlighted) {
            glColor3fv(RED);
            glPushMatrix();
            glTranslatef(circumCenter.x,circumCenter.y,0);
            glLineWidth(3);
            glBegin(GL_LINE_LOOP);
            float a=0.0;
            for (int i=0; i<40; i++) {
                glVertex2f(circumRadius*cos(a),circumRadius*sin(a));
                a+=(float)(M_PI/20.0);
            }
            glEnd();
            glLineWidth(1);
            glPopMatrix();
        }
    }

};

#endif //TRIANGLE_H
