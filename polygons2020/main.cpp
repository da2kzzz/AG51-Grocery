#include <iostream>
#include <glutWindow.h>
#include <vector>
#include "MyPolygon.h"

using namespace std;

class PolygonsExercise: public GlutWindow {
    vector<MyPolygon*> polygons;
public:
    PolygonsExercise(const string &title,int argc,char **argv)
            :GlutWindow(argc, argv, title, 1280, 840, FIXED) {};

    void onStart() override;
    void onDraw() override;
//    void onJudge() override;
    void onQuit() override;
    void onMouseMove(double cx,double cy) override;
//    void onMouseDown(int button,double cx,double cy) override;
};

void PolygonsExercise::onStart() {
    cout << "Start..."  << endl;
    glClearColor(1.0,1.0,1.0,1.0);
// create the polygons
    /*MyPolygon *P = new MyPolygon(5);
    P->addVertex(Vector2D(120,40));
    P->addVertex(Vector2D(400, 160));
    P->addVertex(Vector2D(320, 400));
    P->addVertex(Vector2D(40, 80));
    polygons.push_back(P);
     ... add the other polygons (see booklet pp. 88)
    MyPolygon *L = new MyPolygon(7);
    L->addVertex(Vector2D(620,40));
    L->addVertex(Vector2D(820, 60));
    L->addVertex(Vector2D(900, 160));
    L->addVertex(Vector2D(820, 400));
    L->addVertex(Vector2D(680, 240));
    L->addVertex(Vector2D(540, 80));
    polygons.push_back(L);

    MyPolygon *Q = new MyPolygon(8);
    Q->addVertex(Vector2D(500,500));//0
    Q->addVertex(Vector2D(800, 600));//1
    Q->addVertex(Vector2D(900, 900));//2
    Q->addVertex(Vector2D(400, 900));//3
    Q->addVertex(Vector2D(680, 800));//4
    Q->addVertex(Vector2D(640, 650));//5
    Q->addVertex(Vector2D(240, 680));//6
    polygons.push_back(Q);*/
    MyPolygon *P = new MyPolygon(11);
    P->addVertex(Vector2D(110,450));
    P->addVertex(Vector2D(400,700));
    P->addVertex(Vector2D(1100,720));
    P->addVertex(Vector2D(510,470));
    P->addVertex(Vector2D(370,120));
    P->addVertex(Vector2D(680,40));
    P->addVertex(Vector2D(670,230));
    P->addVertex(Vector2D(900,280));
    P->addVertex(Vector2D(1140,350));
    P->addVertex(Vector2D(970,80));
    polygons.push_back(P);


    //int i=1;
    //for (auto p:polygons){
      //  bool result=p->isConvex();
      //  if(result==true) cout<<"polygon No."<<i<<" is a convex."<<endl;
      //  else cout<<"polygon No."<<i<<" is not a convex."<<endl;
      //  i++;
    //}
}

void PolygonsExercise::onDraw() {
    for (auto p:polygons) {

        p->draw_dot();

    }
}


void PolygonsExercise::onMouseMove(double cx, double cy) {
    //for (auto p:polygons){
       // p->onMouseMove(cx,cy);
   // }
}

void PolygonsExercise::onQuit() {
    // free the memory
    auto p=polygons.begin();
    while (p!=polygons.end()) {
        delete *p;
        p++;
    }
    polygons.clear();
}

int main(int argc,char **argv) {
    PolygonsExercise ex("Drawing polygons",argc,argv);
    ex.start();
    return 0;
}

