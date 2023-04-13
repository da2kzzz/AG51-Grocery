#include <iostream>
#include <cstdlib>
#include <vector>
#include <array>
#include <glutWindow.h>
#include "Triangle.h"

using namespace std;

class PolygonDraw: public GlutWindow {
private:
    array<Vector2D,5> vertices;
    array<Triangle*,3> tris;
public:

    PolygonDraw(const string &title,int argc,char **argv):GlutWindow(argc,argv,title,1000,800,FIXED) {

    };

    void onStart() override;
    void onDraw() override;
    void onQuit() override;
    void onMouseMove(double cx,double cy) override;
    void onMouseDown(int button,double cx,double cy) override;
    void onKeyPressed(unsigned char c,double x,double y) override;
};

void PolygonDraw::onStart() {
    vertices[0].set(40,80);
    vertices[1].set(460,80);
    vertices[2].set(240,360);
    vertices[3].set(890,400);
    vertices[4].set(220,600);

    tris[0] = new Triangle(&vertices[0],&vertices[1],&vertices[2]);
    tris[1] = new Triangle(&vertices[1],&vertices[3],&vertices[2]);
    tris[2] = new Triangle(&vertices[2],&vertices[3],&vertices[4]);
    glClearColor(1.0,1.0,1.0,1.0); // background color
}

void PolygonDraw::onDraw() {
    // draw the referential
    glPushMatrix();
    glTranslatef(10,10,0);
    glColor3fv(RED);
    glBegin(GL_QUADS);
    glVertex2f(0.0,-2.0);
    glVertex2f(100.0,-2.0);
    glVertex2f(100.0,2.0);
    glVertex2f(0.0,2.0);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex2f(110.0,0.0);
    glVertex2f(90.0,-10.0);
    glVertex2f(90.0,10.0);
    glEnd();
    glColor3fv(GREEN);
    glBegin(GL_QUADS);
    glVertex2f(-2.0,0.0);
    glVertex2f(2.0,0.0);
    glVertex2f(2.0,100.0);
    glVertex2f(-2.0,100.0);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex2f(0.0,110.0);
    glVertex2f(-10.0,90.0);
    glVertex2f(10.0,90.0);
    glEnd();
    glPopMatrix();

    for (auto t:tris) {
        t->draw();
    }
    for (auto t:tris) {
        t->drawCircle();
    }
}

void PolygonDraw::onQuit() {

}

void PolygonDraw::onMouseMove(double cx, double cy) {
    Vector2D v((float)cx,(float)cy);
    for (auto t:tris) {
        t->onMouseMove(v);
    }
}

void PolygonDraw::onMouseDown(int button, double cx, double cy) {

}

void PolygonDraw::onKeyPressed(unsigned char c, double x, double y) {
}

int main(int argc,char **argv) {
    PolygonDraw win("Triangulation", argc,argv);
    win.start();

    return 0;
}