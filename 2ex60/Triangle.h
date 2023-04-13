// https://etudiants-stgi.pu-pm.univ-fcomte.fr/tp_bpiranda/adv_algo/circumscribe.zip
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
    bool isDelaunay=false;

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
        Vector2D AB=*ptr[1]-*ptr[0];
        Vector2D AC=*ptr[2]-*ptr[0];
        Vector2D V=AC.ortho();
        // calculate circle parameters
        float k = 0.5f*(AB*AB - AC*AB)/(V*AB);

        Vector2D u = (0.5f*AC)+k*V;

        circumCenter=*ptr[0]+u;
        circumRadius = (float)(u.norm());
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

    Vector2D *VertexOutside(const Triangle &T) const {
        if (ptr[0]!=T.ptr[0] && ptr[0]!=T.ptr[1] && ptr[0]!=T.ptr[2]) return ptr[0];
        if (ptr[1]!=T.ptr[0] && ptr[1]!=T.ptr[1] && ptr[1]!=T.ptr[2]) return ptr[1];
        if (ptr[2]!=T.ptr[0] && ptr[2]!=T.ptr[1] && ptr[2]!=T.ptr[2]) return ptr[2];
    }

    Vector2D *NextVertex(const Vector2D *pt) const {
        if (pt==ptr[0]) return ptr[1];
        if (pt==ptr[1]) return ptr[2];
        if (pt==ptr[2]) return ptr[0];
    }

    void draw() {
        // glColor3fv(isHighlighted?ORANGE:(isDelaunay?GREY:YELLOW));
        glColor4fv(isDelaunay?(isHighlighted?GREEN:GREY):(isHighlighted?RED:YELLOW));
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

    bool isInsideCircle(const Vector2D &p) const {
        if (p==*ptr[0] || p==*ptr[1] || p==*ptr[2]) return false;
        return ((p-circumCenter).norm()<circumRadius);
    }

    bool checkDelauney(const vector<Vector2D> &vertices) {
        auto v=vertices.begin();
        while (v!=vertices.end() && !isInsideCircle(*v)) {
            v++;
        }
        isDelaunay = (v==vertices.end());
        return isDelaunay;
    }
};

#endif //TRIANGLE_H
