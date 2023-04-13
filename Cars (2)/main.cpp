#include <iostream>
#include <cstdlib>
#include <array>
#include <vector>
#include <GL/glut.h>
#include "glutWindows.h"
#include <fstream>
#include <cstring>
#include <algorithm>
#include "Mesh.h"
#include "Voronoi.h"
#include "Icon.h"
#include "Cars.h"
#include "CarMove.h"
#include "door.h"

using namespace std;
car c,c1,c2;
door d,d1,d2;
bool click= false;
bool texturesShow =false;

const string serversFileName("../Data/servers.txt");
const array<Vector2D,4> tabAppearingPos={ Vector2D(50.0f,50.0f),
                                          Vector2D(950.0f,50.0f),
                                          Vector2D(950.0f,750.0f),
                                          Vector2D(50.0f,750.0f)};

class PolygonDraw: public GlutWindow {
private:
    GLuint CarportId;
    GLuint BluecarID,OrangecarID;
    GLuint CarStopID;

    array<Triangle*,11> tris;

    Mesh *mesh;
    Voronoi *voronoi;
    bool showVoronoi;
    Icon *server;
    vector<CarData*> Cars;
    vector<ServerData*> servers;
    vector<ServerData*>::iterator mouseOverServer;
    ServerData* selectedServer;
    string configFile;
    double fieldSurface;
public:

    PolygonDraw(const string &title,int argc,char **argv):GlutWindow(argc,argv,title,1280,840,FIXED) {
        showVoronoi=false;
        mesh= nullptr;
        voronoi= nullptr;
        CarportId=0;
        configFile = serversFileName;
        selectedServer=nullptr;
        fieldSurface = width*height;
    };

    void onStart() override;
    void onDraw() override;
    void onQuit() override;
    void onMouseMove(double cx,double cy) override;
    void onMouseDrag(double cx,double cy) override;
    void onMouseDown(int button,double cx,double cy) override;
    void onKeyPressed(unsigned char c,double x,double y) override;
    void onUpdate(double dt) override;
    void loadServerPositions(const string &title);
    bool saveServerPositions(const string &title);
    void addCar(const Vector2D &pos);
};

void PolygonDraw::onStart() {
    int lx,ly;
    CarportId = loadTGATexture("../textures/carpark.tga",lx,ly);
    assert(CarportId!=0);
    BluecarID = loadTGATexture("../textures/cyancar.tga",lx,ly);
    assert(CarportId!=0);
    CarStopID = loadTGATexture("../textures/carstop.tga",lx,ly);
    assert(CarportId!=0);
    OrangecarID = loadTGATexture("../textures/orangecar.tga",lx,ly);
    assert(CarportId!=0);


    loadServerPositions(configFile);

    /*vector<Vector2D> tabVertices;
    for(auto s:servers) {
        tabVertices.push_back(s->position);
    }
    mesh = new Mesh(tabVertices);*/

    //----------------
    float tabVect[][2]={{110,450},{400,700},{1100,720},{510,470},{370,120},{680,40},
                        {670,230},{900,280},{1140,350},{970,80}};
    //int tabTri[][3]={{4,7,3},{4,5,7},{5,6,7},{7,9,3},{7,6,8},{7,8,9},{6,0,8},{0,9,8},{0,1,9},
    //    {1,2,9},{2,3,9}};
    int tabTri[][3]={{0,3,1},{0,4,3},{1,3,2},{3,4,6},{3,6,7},{3,7,2},{2,7,8},{4,5,6},{6,5,7},
                     {7,5,9},{7,9,8}};
    mesh = new Mesh(tabVect,10,tabTri,11);
    for(int i=0;i<11;i++){
        tris[i]=& mesh->triangles.at(i);
    }
    //----------------

    mouseOverServer = servers.end();
    glClearColor(1.0,1.0,1.0,1.0); // background color
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void PolygonDraw::onDraw() {
    // draw the referential
    glPushMatrix();
    glTranslatef(10,10,0);
    glColor3fv(&RED[0]);
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
    glColor3fv(&GREEN[0]);
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

    if (voronoi && showVoronoi) {
        voronoi->draw();
    } else if (mesh) {
        mesh->draw();
    }

    glColor3fv(&BLACK[0]);
    for (auto v:servers) {
        glPushMatrix();
        glTranslatef(v->position.x,v->position.y,0.0);
        server->glDraw();
        drawText(0,-0.5*server->getHeight()-18,v->name,ALIGN_CENTER);
        glPopMatrix();
    }
if(texturesShow){
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,CarportId);
    //Bravo
    for(int x=360;x<=480;x+=40){
        glPushMatrix();
        glTranslatef(x,720,0.0);
        glBegin(GL_QUADS);
        glTexCoord2f(1.0,0.0);
        glVertex2f(0.0,0.0);
        glTexCoord2f(1.0,1.0);
        glVertex2f(40.0,0.0);
        glTexCoord2f(0.0,1.0);
        glVertex2f(40.0,50.0);
        glTexCoord2f(0.0,0.0);
        glVertex2f(0.0,50.0);
        glEnd();
        glPopMatrix();}

    //Alpha
    for(int y=410;y<=530;y+=40){
        glPushMatrix();
        glTranslatef(0,y,0.0);
        glBegin(GL_QUADS);
        glTexCoord2f(0.0,0.0);
        glVertex2f(0.0,0.0);
        glTexCoord2f(1.0,0.0);
        glVertex2f(50.0,0.0);
        glTexCoord2f(1.0,1.0);
        glVertex2f(50.0,40.0);
        glTexCoord2f(0.0,1.0);
        glVertex2f(0.0,40.0);
        glEnd();
        glPopMatrix();}

    //Charlie
    for(int x=1020;x<=1140;x+=40){
        glPushMatrix();
        glTranslatef(x,720,0.0);
        glBegin(GL_QUADS);
        glTexCoord2f(1.0,0.0);
        glVertex2f(0.0,0.0);
        glTexCoord2f(1.0,1.0);
        glVertex2f(40.0,0.0);
        glTexCoord2f(0.0,1.0);
        glVertex2f(40.0,50.0);
        glTexCoord2f(0.0,0.0);
        glVertex2f(0.0,50.0);
        glEnd();
        glPopMatrix();}

    //India
    for(int y=310;y<=390;y+=40){
        glPushMatrix();
        glTranslatef(1280,y,0.0);
        glRotatef(180,0,0,-1);
        glBegin(GL_QUADS);
        glTexCoord2f(0.0,0.0);
        glVertex2f(0.0,0.0);
        glTexCoord2f(1.0,0.0);
        glVertex2f(50.0,0.0);
        glTexCoord2f(1.0,1.0);
        glVertex2f(50.0,40.0);
        glTexCoord2f(0.0,1.0);
        glVertex2f(0.0,40.0);
        glEnd();
        glPopMatrix();}

    //Echo
    for(int x=290;x<=410;x+=40){
        glPushMatrix();
        glTranslatef(x,50.0,0.0);
        glRotatef(180,0,0,-1);
        glBegin(GL_QUADS);
        glTexCoord2f(1.0,0.0);
        glVertex2f(0.0,0.0);
        glTexCoord2f(1.0,1.0);
        glVertex2f(40.0,0.0);
        glTexCoord2f(0.0,1.0);
        glVertex2f(40.0,50.0);
        glTexCoord2f(0.0,0.0);
        glVertex2f(0.0,50.0);
        glEnd();
        glPopMatrix();}

    //Julliet
    for(int x=930;x<=970;x+=40){
        glPushMatrix();
        glTranslatef(x,50.0,0.0);
        glRotatef(180,0,0,-1);
        glBegin(GL_QUADS);
        glTexCoord2f(1.0,0.0);
        glVertex2f(0.0,0.0);
        glTexCoord2f(1.0,1.0);
        glVertex2f(40.0,0.0);
        glTexCoord2f(0.0,1.0);
        glVertex2f(40.0,50.0);
        glTexCoord2f(0.0,0.0);
        glVertex2f(0.0,50.0);
        glEnd();
        glPopMatrix();}

    //Foxtrot
    glPushMatrix();
    glTranslatef(660,50.0,0.0);
    glRotatef(180,0,0,-1);
    glBegin(GL_QUADS);
    glTexCoord2f(1.0,0.0);
    glVertex2f(0.0,0.0);
    glTexCoord2f(1.0,1.0);
    glVertex2f(40.0,0.0);
    glTexCoord2f(0.0,1.0);
    glVertex2f(40.0,50.0);
    glTexCoord2f(0.0,0.0);
    glVertex2f(0.0,50.0);
    glEnd();
    glPopMatrix();

    //Golf
    double yg=350;
    for(double x=587;x<=630;x+=28){
        glPushMatrix();
        glTranslatef(x,yg,0.0);
        yg+=18.7;
        glRotatef(57,0,0,-1);
        glBegin(GL_QUADS);
        glTexCoord2f(0.0,0.0);
        glVertex2f(0.0,0.0);
        glTexCoord2f(1.0,0.0);
        glVertex2f(50.0,0.0);
        glTexCoord2f(1.0,1.0);
        glVertex2f(50.0,40.0);
        glTexCoord2f(0.0,1.0);
        glVertex2f(0.0,40.0);
        glEnd();
        glPopMatrix();}

    //Delta
    double yd=350;
    for(double x=595;x<=700;x+=28){
        glPushMatrix();
        glTranslatef(x,yd,0.0);
        yd+=18.7;
        glRotatef(57,0,0,-1);
        glRotatef(180,0,0,-1);
        glBegin(GL_QUADS);
        glTexCoord2f(0.0,0.0);
        glVertex2f(0.0,0.0);
        glTexCoord2f(1.0,0.0);
        glVertex2f(50.0,0.0);
        glTexCoord2f(1.0,1.0);
        glVertex2f(50.0,40.0);
        glTexCoord2f(0.0,1.0);
        glVertex2f(0.0,40.0);
        glEnd();
        glPopMatrix();}

    //Hotel
    double xh=1020;
    for(int y=315;y<=387;y+=37){
        glPushMatrix();
        glTranslatef(xh,y,0.0);
        xh-=11;
        glRotatef(16,0,0,1);
        glRotatef(180,0,0,-1);
        glBegin(GL_QUADS);
        glTexCoord2f(0.0,0.0);
        glVertex2f(0.0,0.0);
        glTexCoord2f(1.0,0.0);
        glVertex2f(50.0,0.0);
        glTexCoord2f(1.0,1.0);
        glVertex2f(50.0,40.0);
        glTexCoord2f(0.0,1.0);
        glVertex2f(0.0,40.0);
        glEnd();
        glPopMatrix();}

    //carstop
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,CarStopID);
    //Alpha
        glPushMatrix();
        glTranslatef(173,595,0.0);
        glRotatef(50,0,0,-1);
        glBegin(GL_QUADS);
        glTexCoord2f(1.0,0.0);
        glVertex2f(0.0,0.0);
        glTexCoord2f(1.0,1.0);
        glVertex2f(40.0,0.0);
        glTexCoord2f(0.0,1.0);
        glVertex2f(40.0,50.0);
        glTexCoord2f(0.0,0.0);
        glVertex2f(0.0,50.0);
        glEnd();
        glPopMatrix();
     //
    glPushMatrix();
    glTranslatef(150,279,0.0);
    glRotatef(41,0,0,1);
    glRotatef(180,0,0,-1);
    glBegin(GL_QUADS);
    glTexCoord2f(1.0,0.0);
    glVertex2f(0.0,0.0);
    glTexCoord2f(1.0,1.0);
    glVertex2f(40.0,0.0);
    glTexCoord2f(0.0,1.0);
    glVertex2f(40.0,50.0);
    glTexCoord2f(0.0,0.0);
    glVertex2f(0.0,50.0);
    glEnd();
    glPopMatrix();
//
    glPushMatrix();
    glTranslatef(365,270,0.0);
    glRotatef(202,0,0,-1);
    glRotatef(180,0,0,-1);
    glBegin(GL_QUADS);
    glTexCoord2f(1.0,0.0);
    glVertex2f(0.0,0.0);
    glTexCoord2f(1.0,1.0);
    glVertex2f(40.0,0.0);
    glTexCoord2f(0.0,1.0);
    glVertex2f(40.0,50.0);
    glTexCoord2f(0.0,0.0);
    glVertex2f(0.0,50.0);
    glEnd();
    glPopMatrix();
    //
    glPushMatrix();
    glTranslatef(575,585,0.0);
    glRotatef(28,0,0,1);
    glBegin(GL_QUADS);
    glTexCoord2f(1.0,0.0);
    glVertex2f(0.0,0.0);
    glTexCoord2f(1.0,1.0);
    glVertex2f(40.0,0.0);
    glTexCoord2f(0.0,1.0);
    glVertex2f(40.0,50.0);
    glTexCoord2f(0.0,0.0);
    glVertex2f(0.0,50.0);
    glEnd();//Delta&Bravo
    glPopMatrix();
    glPushMatrix();
    glTranslatef(529,677,0.0);
    glRotatef(28,0,0,1);
    glRotatef(180,0,0,1);
    glBegin(GL_QUADS);
    glTexCoord2f(1.0,0.0);
    glVertex2f(0.0,0.0);
    glTexCoord2f(1.0,1.0);
    glVertex2f(40.0,0.0);
    glTexCoord2f(0.0,1.0);
    glVertex2f(40.0,50.0);
    glTexCoord2f(0.0,0.0);
    glVertex2f(0.0,50.0);
    glEnd();
    glPopMatrix();

    //
    glPushMatrix();
    glTranslatef(475,85,0.0);
    glRotatef(105,0,0,-1);
    glBegin(GL_QUADS);
    glTexCoord2f(1.0,0.0);
    glVertex2f(0.0,0.0);
    glTexCoord2f(1.0,1.0);
    glVertex2f(40.0,0.0);
    glTexCoord2f(0.0,1.0);
    glVertex2f(40.0,50.0);
    glTexCoord2f(0.0,0.0);
    glVertex2f(0.0,50.0);
    glEnd();//Echo&Foxtrot
    glPopMatrix();
    glPushMatrix();
    glTranslatef(570,58,0.0);
    glRotatef(105,0,0,-1);
    glRotatef(180,0,0,1);
    glBegin(GL_QUADS);
    glTexCoord2f(1.0,0.0);
    glVertex2f(0.0,0.0);
    glTexCoord2f(1.0,1.0);
    glVertex2f(40.0,0.0);
    glTexCoord2f(0.0,1.0);
    glVertex2f(40.0,50.0);
    glTexCoord2f(0.0,0.0);
    glVertex2f(0.0,50.0);
    glEnd();
    glPopMatrix();

    //
    glPushMatrix();
    glTranslatef(675,87,0.0);
    glRotatef(1,0,0,1);
    glBegin(GL_QUADS);
    glTexCoord2f(1.0,0.0);
    glVertex2f(0.0,0.0);
    glTexCoord2f(1.0,1.0);
    glVertex2f(40.0,0.0);
    glTexCoord2f(0.0,1.0);
    glVertex2f(40.0,50.0);
    glTexCoord2f(0.0,0.0);
    glVertex2f(0.0,50.0);
    glEnd();//Golf&Foxtrot
    glPopMatrix();
    glPushMatrix();
    glTranslatef(675,185,0.0);
    glRotatef(180,0,0,1);
    glBegin(GL_QUADS);
    glTexCoord2f(1.0,0.0);
    glVertex2f(0.0,0.0);
    glTexCoord2f(1.0,1.0);
    glVertex2f(40.0,0.0);
    glTexCoord2f(0.0,1.0);
    glVertex2f(40.0,50.0);
    glTexCoord2f(0.0,0.0);
    glVertex2f(0.0,50.0);
    glEnd();
    glPopMatrix();

    //Delta&Hotel
    glPushMatrix();
    glTranslatef(736,553,0.0);
    glRotatef(-118,0,0,1);
    glBegin(GL_QUADS);
    glTexCoord2f(1.0,0.0);
    glVertex2f(0.0,0.0);
    glTexCoord2f(1.0,1.0);
    glVertex2f(40.0,0.0);
    glTexCoord2f(0.0,1.0);
    glVertex2f(40.0,50.0);
    glTexCoord2f(0.0,0.0);
    glVertex2f(0.0,50.0);
    glEnd();
    glPopMatrix();

    //
    glPushMatrix();
    glTranslatef(828,292,0.0);
    glRotatef(100,0,0,1);
    glBegin(GL_QUADS);
    glTexCoord2f(1.0,0.0);
    glVertex2f(0.0,0.0);
    glTexCoord2f(1.0,1.0);
    glVertex2f(40.0,0.0);
    glTexCoord2f(0.0,1.0);
    glVertex2f(40.0,50.0);
    glTexCoord2f(0.0,0.0);
    glVertex2f(0.0,50.0);
    glEnd();//Golf&Hotel
    glPopMatrix();
    glPushMatrix();
    glTranslatef(728,274,0.0);
    glRotatef(-79,0,0,1);
    glBegin(GL_QUADS);
    glTexCoord2f(1.0,0.0);
    glVertex2f(0.0,0.0);
    glTexCoord2f(1.0,1.0);
    glVertex2f(40.0,0.0);
    glTexCoord2f(0.0,1.0);
    glVertex2f(40.0,50.0);
    glTexCoord2f(0.0,0.0);
    glVertex2f(0.0,50.0);
    glEnd();
    glPopMatrix();

    //Hotel&Crilie
    glPushMatrix();
    glTranslatef(875,500,0.0);
    glRotatef(-22,0,0,1);
    glBegin(GL_QUADS);
    glTexCoord2f(1.0,0.0);
    glVertex2f(0.0,0.0);
    glTexCoord2f(1.0,1.0);
    glVertex2f(40.0,0.0);
    glTexCoord2f(0.0,1.0);
    glVertex2f(40.0,50.0);
    glTexCoord2f(0.0,0.0);
    glVertex2f(0.0,50.0);
    glEnd();
    glPopMatrix();

    //
    glPushMatrix();
    glTranslatef(1120,487,0.0);
    glRotatef(5,0,0,1);
    glBegin(GL_QUADS);
    glTexCoord2f(1.0,0.0);
    glVertex2f(0.0,0.0);
    glTexCoord2f(1.0,1.0);
    glVertex2f(40.0,0.0);
    glTexCoord2f(0.0,1.0);
    glVertex2f(40.0,50.0);
    glTexCoord2f(0.0,0.0);
    glVertex2f(0.0,50.0);
    glEnd();//C&India
    glPopMatrix();
    glPushMatrix();
    glTranslatef(1108.5,583,0.0);
    glRotatef(-175,0,0,1);
    glBegin(GL_QUADS);
    glTexCoord2f(1.0,0.0);
    glVertex2f(0.0,0.0);
    glTexCoord2f(1.0,1.0);
    glVertex2f(40.0,0.0);
    glTexCoord2f(0.0,1.0);
    glVertex2f(40.0,50.0);
    glTexCoord2f(0.0,0.0);
    glVertex2f(0.0,50.0);
    glEnd();
    glPopMatrix();

    //
    glPushMatrix();
    glTranslatef(1155,90,0.0);
    glRotatef(-27,0,0,1);
    glBegin(GL_QUADS);
    glTexCoord2f(1.0,0.0);
    glVertex2f(0.0,0.0);
    glTexCoord2f(1.0,1.0);
    glVertex2f(40.0,0.0);
    glTexCoord2f(0.0,1.0);
    glVertex2f(40.0,50.0);
    glTexCoord2f(0.0,0.0);
    glVertex2f(0.0,50.0);
    glEnd();//India&Juliette
    glPopMatrix();
    glPushMatrix();
    glTranslatef(1205,178,0.0);
    glRotatef(30,0,0,-1);
    glRotatef(180,0,0,-1);
    glBegin(GL_QUADS);
    glTexCoord2f(1.0,0.0);
    glVertex2f(0.0,0.0);
    glTexCoord2f(1.0,1.0);
    glVertex2f(40.0,0.0);
    glTexCoord2f(0.0,1.0);
    glVertex2f(40.0,50.0);
    glTexCoord2f(0.0,0.0);
    glVertex2f(0.0,50.0);
    glEnd();
    glPopMatrix();

    //
    glPushMatrix();
    glTranslatef(800,740,0.0);
    glRotatef(90,0,0,1);
    glBegin(GL_QUADS);
    glTexCoord2f(1.0,0.0);
    glVertex2f(0.0,0.0);
    glTexCoord2f(1.0,1.0);
    glVertex2f(40.0,0.0);
    glTexCoord2f(0.0,1.0);
    glVertex2f(40.0,50.0);
    glTexCoord2f(0.0,0.0);
    glVertex2f(0.0,50.0);
    glEnd();
    glPopMatrix();


    glEnable(GL_TEXTURE_2D);
    c.draw('b');
    c1 = car(0,450);
    c1.draw('o');
    d1= door(360,720);

    //draw car and door
    // c.draw();
    //d.draw();

    //function to get the curve
    c.curve(d);
    c1.curve(d1);

    //function to draw the curce
    //c.curvedr();


    glDisable(GL_TEXTURE_2D);

    glPopMatrix();

    glDisable(GL_TEXTURE_2D);}

}
void PolygonDraw::onQuit() {
    delete mesh;
    delete voronoi;
    delete server;
}

void PolygonDraw::onMouseMove(double cx, double cy) {
    static float w = server->getWidth()/2;
    static float h = server->getHeight()/2;
    auto m_it=servers.begin();
    while (m_it!=servers.end() && (cx>(*m_it)->position.x+w || cx<(*m_it)->position.x-w ||
                                   cy>(*m_it)->position.y+h || cy<(*m_it)->position.y-w)) {
        m_it++;
    }
    mouseOverServer =m_it;
    if (mouseOverServer!=servers.end()) {
        glutSetCursor(GLUT_CURSOR_CROSSHAIR);
    } else {
        glutSetCursor(GLUT_CURSOR_INHERIT);
    }
    mesh->onMouseMove(cx,cy);
}

void PolygonDraw::onMouseDrag(double cx, double cy) {
    if (mouseOverServer!=servers.end()) {
        (*mouseOverServer)->position.x=(float)cx;
        (*mouseOverServer)->position.y=(float)cy;
    }
}

void PolygonDraw::onMouseDown(int button, double cx, double cy) {

    cout << "click" <<endl;
    //c.go();
    click=true;
}
bool PolygonDraw::saveServerPositions(const string &title) {
    ofstream fout(title);

    if (fout.is_open()) {
        for (auto it:servers) {
            fout << (*it).name << ";" << (*it).position << ";" << (*it).colorName << "\n";
        }
    } else {
        return false;
    }
    return true;
}

void PolygonDraw::onKeyPressed(unsigned char c, double x, double y) {
    switch (c) {
        case 's':
            saveServerPositions(configFile);
            break;
        case 'v': showVoronoi=!showVoronoi; break;
        case 'z': {
            texturesShow =true;
            mesh->checkDelaunay();
            mesh->solveDelaunay();
            mesh->checkDelaunay();
            voronoi = new Voronoi(*mesh);
            voronoi->triangulatePolygons();
            auto s = servers.begin();
            while (s != servers.end()) {
                (*s)->ptrPolygon = voronoi->findPolygon((*s)->position);
                assert((*s)->ptrPolygon!= nullptr);
                array<float, 4> c = Triangle::getColorByName((*s)->colorName);
                (*s)->ptrPolygon->setColor(c);
                (*s)->surfaceRate = (*s)->ptrPolygon->surface()/fieldSurface;
                auto m_vert = mesh->vertices.begin(); // point of the mesh corresponding to s->position
                while (m_vert!=mesh->vertices.end() && (*m_vert!=(*s)->position)) {
                    m_vert++;
                }
                assert(m_vert!=mesh->vertices.end());

                auto mt_it = mesh->triangles.begin();
                vector<const Vector2D*> tabPts; // tabPts: list of vertices connected to m_vert

                while (mt_it!=mesh->triangles.end()) {
                    if ((*mt_it).hasVertex(&(*m_vert))) {
                        tabPts.push_back((*mt_it).getPrevVertex(&(*m_vert)));
                        tabPts.push_back((*mt_it).getNextVertex(&(*m_vert)));
                    }
                    mt_it++;
                }
                sort(tabPts.begin(),tabPts.end(),[](const Vector2D *a, const Vector2D *b) {
                    return (a->x > b->x)||((a->x==b->x)&&(a->y > b->y));
                });
                Vector2D prev;
                for (auto pp:tabPts) {
                    if (*pp!=prev) {
                        auto it_s = servers.begin();
                        while (it_s != servers.end() && ((*it_s)->position != *pp)) {
                            it_s++;
                        }
                        assert(it_s != servers.end());
                        (*s)->addNeighbor(*it_s);
                    }
                    prev=*pp;
                }
                cout << endl;
                s++;
            }
            showVoronoi=true;
        } break;

    }
}

void PolygonDraw::onUpdate(double dt) {
    // initialize every Car forces
    if (click) {c.animate();c1.animate();}
    auto d=Cars.begin();
    while (d!=Cars.end()) {
        (*d)->updateSpeed(dt);
        (*d)->sumF.init();
        d++;
    }
    // Associate Cars
    d=Cars.begin();
    while (d!=Cars.end()) {
        if ((*d)->ptrServer==nullptr || !(*d)->ptrServer->CarIsOver((*d)->position)) {
            if ((*d)->ptrServer!= nullptr) {
                (*d)->ptrServer->removeCar(*d);
            }
            auto s=servers.begin();
            while (s!=servers.end() && !(*s)->CarIsOver((*d)->position)){
                s++;
            }
            assert(s!=servers.end());
            (*s)->addCar(*d);
            (*d)->ptrServer=*s;
        }
        // collisions of d with others
        auto dcomp=d+1;
        while (dcomp!=Cars.end()) {
            Vector2D AB = (*dcomp)->position-(*d)->position;
            double dAB=AB.norm();
            if (dAB<dmax) {
                float F=(float)((dAB>dmin)?(Fmax/dAB)*(dAB-dmax)/(dmin-dmax):Fmax);
                (*d)->sumF-=F*AB;
                (*dcomp)->sumF+=F*AB;
            }
            dcomp++;
        }
        // collision of d with borders
        double dAB=(*d)->position.x;
        if (dAB<dmax) {
            float F=(float)((dAB>dmin)?(Fmax/dAB)*(dAB-dmax)/(dmin-dmax):Fmax);
            (*d)->sumF+=Vector2D(F,0);
        }
        dAB=width-(*d)->position.x;
        if (dAB<dmax) {
            float F=(float)((dAB>dmin)?(Fmax/dAB)*(dAB-dmax)/(dmin-dmax):Fmax);
            (*d)->sumF+=Vector2D(-F,0);
        }
        dAB=(*d)->position.y;
        if (dAB<dmax) {
            float F=(float)((dAB>dmin)?(Fmax/dAB)*(dAB-dmax)/(dmin-dmax):Fmax);
            (*d)->sumF+=Vector2D(0,F);
        }
        dAB=height-(*d)->position.y;
        if (dAB<dmax) {
            float F=(float)((dAB>dmin)?(Fmax/dAB)*(dAB-dmax)/(dmin-dmax):Fmax);
            (*d)->sumF+=Vector2D(0,-F);
        }
        d++;
    }
}


void PolygonDraw::loadServerPositions(const string &title) {
    try {
        ifstream fin(title);
        string name, color;
        Vector2D position;

        servers.clear();

        if (fin.is_open()) {
            char line[256];
            string strLine,vectorStr;
            int posBeg,posEnd;
            while (!fin.eof()) {
                fin.getline(line,256);
                strLine=line;
                if (strLine.size()>1) {
                    posEnd = strLine.find(';');
                    name = strLine.substr(0, posEnd);
                    posBeg = posEnd + 1;
                    posEnd = strLine.find(';', posBeg);
                    vectorStr = strLine.substr(posBeg, posEnd - posBeg);
                    color = strLine.substr(posEnd + 1);
                    posBeg = vectorStr.find('(');
                    posEnd = vectorStr.find(',');
                    position.x = stof(vectorStr.substr(posBeg + 1, posEnd - posBeg - 1));
                    posBeg = posEnd + 1;
                    posEnd = vectorStr.find(')', posBeg);
                    position.y = stof(vectorStr.substr(posBeg, posEnd - posBeg));
                    servers.push_back(new ServerData(name, position, color));
                }
            }
        }
        fin.close();
    } catch (ifstream::failure e) {
        cerr << "Exception opening/reading/closing file" << endl;
    }
}


int main(int argc,char **argv) {
    PolygonDraw win("ToyCars", argc,argv);
    win.start();

    return 0;
}






