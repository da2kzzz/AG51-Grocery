#include <iostream>
#include <cstdlib>
#include <vector>
#include <array>
#include <glutWindow.h>
#include "Mesh.h"

using namespace std;

class PolygonDraw: public GlutWindow {
private:
    array<Vector2D,5> vertices;
    array<Triangle*,15> tris;
    Mesh *mesh;
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
    float tabVect[][2]={{280,740},{700,750},{500,700},{900,720},{50,410},{340,400},
                        {650,390},{950,300},{400,200},{550,190},{200,50},{800,100}};
    int tabTri[][3]={{9,10,11},{0,4,2},{1,6,3},{2,6,1},{2,8,6},{3,11,7},
                     {4,8,5},{4,5,2},{3,6,11},{0,2,1},{4,10,8},{6,8,9},{6,9,11},{2,5,8},{8,10,9}};
    mesh = new Mesh(tabVect,12,tabTri,15);
    for(int i=0;i<15;i++){
        tris[i]=& mesh->triangles.at(i);
    }
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
    Vector2D v((float)cx,(float)cy);
    Triangle *thistri = mesh->returnTriangle(v);
    Triangle *neigbr = mesh->getNeighbor(thistri);
    if(neigbr!= nullptr){
        mesh->flip(*thistri,*neigbr);
    }
    mesh->checkDelaunay();
}

void PolygonDraw::onKeyPressed(unsigned char c, double x, double y) {
    switch (c) {
        case 'w': {
            mesh->checkDelaunay();
            mesh->changeDelaunay();
            mesh->checkDelaunay();
        }
    }
}

int main(int argc,char **argv) {
    cout<<"press mouse to change one by one, press w to auto change"<<endl;
    PolygonDraw win("Triangulation", argc,argv);
    win.start();

    return 0;
}