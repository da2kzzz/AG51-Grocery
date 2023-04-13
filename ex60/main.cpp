#include <iostream>
#include <cstdlib>
#include <vector>
#include <array>
#include <glutWindow.h>
#include "Mesh.h"
#include "Vector2D.h"
#include "Voronoi.h"
#include "ToyCar.h"
using namespace std;

const string serversFileName("../Data/servers.txt");

class PolygonDraw: public GlutWindow {
private:
   // array<Vector2D,5> vertices;
    array<Triangle*,11> tris;
    Mesh *mesh;
    Voronoi *voronoi;
    bool showVoronoi;
    string configFile;
    vector<ServerData*> servers;
    vector<ServerData*>::iterator mouseOverServer;
    double fieldSurface;
public:

    PolygonDraw(const string &title,int argc,char **argv):GlutWindow(argc,argv,title,1280,840,FIXED) {
        mesh= nullptr;
        voronoi= nullptr;

        configFile = serversFileName;
        fieldSurface = width*height;
        int i=0;
        while (i<argc) {
            cout << "argv[" << i << "]=" << argv[i] << endl;
            if (strncmp(argv[i],"-c",2)==0) {
                i++;
                if (i<argc) {
                    configFile=argv[i++];
                }
            }
            i++;
        }
    };

    void onStart() override;
    void onDraw() override;
    void onQuit() override;
    void onMouseMove(double cx,double cy) override;
    void onMouseDown(int button,double cx,double cy) override;
    void onKeyPressed(unsigned char c,double x,double y) override;
};

void PolygonDraw::onStart() {
    /* vector<Vector2D> tabVertices;
     tabVertices.push_back(Vector2D(110,450));
     tabVertices.push_back(Vector2D(400,700));
     tabVertices.push_back(Vector2D(1100,720));
     tabVertices.push_back(Vector2D(510,470));
     tabVertices.push_back(Vector2D(370,120));
     tabVertices.push_back(Vector2D(680,40));
     tabVertices.push_back(Vector2D(670,230));
     tabVertices.push_back(Vector2D(900,280));
     tabVertices.push_back(Vector2D(1140,350));
     tabVertices.push_back(Vector2D(970,80));
     mesh = new Mesh(tabVertes);*/
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
    mouseOverServer = servers.end();
    glClearColor(1.0,1.0,1.0,1.0); // background color
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void PolygonDraw::onDraw() {
    // draw the referential
    /*glPushMatrix();
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
    glPopMatrix();*/

    for (auto t:tris) {
        t->draw();
    }
    for (auto t:tris) {
        t->drawCircle();
    }
    //mesh->draw();


    if (voronoi && showVoronoi) {
       voronoi->draw();
    }

}

void PolygonDraw::onQuit() {

}

void PolygonDraw::onMouseMove(double cx, double cy) {
   // Vector2D v((float)cx,(float)cy);
   // for (auto t:tris) {
     //   t->onMouseMove(v);
   // }
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
        case 'w': {// auto delaunay change
            mesh->checkDelaunay();
            mesh->changeDelaunay();
            mesh->checkDelaunay();
        }break;
        case 'z': {
            mesh->checkDelaunay();
            mesh->changeDelaunay();
            mesh->checkDelaunay();
            voronoi = new Voronoi(*mesh);
            voronoi->triangulatePolygons();
            //---------------------------
            auto s = servers.begin();
            while (s != servers.end()) {
                (*s)->ptrPolygon = voronoi->findPolygon((*s)->position);
                assert((*s)->ptrPolygon!= nullptr);
                array<float, 4> c = Triangle::getColorByName((*s)->colorName);

                (*s)->ptrPolygon->setColor(c);
                (*s)->surfaceRate = (*s)->ptrPolygon->surface()/fieldSurface;
                cout << (*s)->name << ":" << 0.1 * floor(((*s)->surfaceRate) * 1000 + 0.5) << endl;
                // construct neighbor list -------------------------------
                auto m_vert = mesh->vertices.begin(); // point of the mesh corresponding to s->position
                while (m_vert!=mesh->vertices.end() && (*m_vert!=(*s)->position)) {
                    m_vert++;
                }
                assert(m_vert!=mesh->vertices.end());

                auto mt_it = mesh->triangles.begin();
                vector<const Vector2D*> tabPts; // tabPts: list of vertices connected to m_vert

                while (mt_it!=mesh->triangles.end()) {
                    if ((*mt_it).ifVertex(&(*m_vert))) {
                        tabPts.push_back((*mt_it).PrevVertex(&(*m_vert)));
                        tabPts.push_back((*mt_it).NextVertex(&(*m_vert)));
                    }
                    mt_it++;
                }
                sort(tabPts.begin(),tabPts.end(),[](const Vector2D *a, const Vector2D *b) {
                    return (a->x > b->x)||((a->x==b->x)&&(a->y > b->y));
                });
                // add unique neighbor
                cout << "Neighbors: ";
                Vector2D prev;
                for (auto pp:tabPts) {
                    if (*pp!=prev) {
                        auto it_s = servers.begin();
                        while (it_s != servers.end() && ((*it_s)->position != *pp)) {
                            it_s++;
                        }
                        assert(it_s != servers.end());
                        (*s)->addNeighbor(*it_s);
                        cout << (*it_s)->name << ", ";
                    }
                    prev=*pp;
                }
                cout << endl;
                // end construct neighbor list ---------------------------


                s++;
            }
            //---------------------------
            showVoronoi=true;
        }break;
    }
}

int main(int argc,char **argv) {
    //cout<<"press mouse to change one by one, press w to auto change"<<endl;
    PolygonDraw win("Triangulation", argc,argv);
    win.start();

    return 0;
}