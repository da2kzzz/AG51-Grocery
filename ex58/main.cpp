#include <iostream>
#include <glutWindow.h>
#include <vector>
#include "MyPolygon.h"
#include "grahams.h"
#include<cstdio>
#include<stack>
#include<algorithm>
#include<cmath>

using namespace std;

/*const int maxn = 1000;
struct Node{
    int x,y;
}u,node[maxn];
int N=50;


int cmp1(const Node &a, const Node &b)
{
    return a.y < b.y;
}
//极角排序
int cmp2(const Node &a, const Node &b)
{
    return atan2(1.0*(a.y-u.y), 1.0*(a.x-u.x)) < atan2(1.0*(b.y-u.y), 1.0*(b.x-u.x));
}
//计算叉积
int Direction(Node a, Node b, Node c)
{
    return (c.x-a.x) * (b.y-a.y) - (b.x-a.x) * (c.y - a.y);
}
//判断是否向右
bool right(Node a, Node b, Node c)
{
    if(Direction(a, b, c) < 0)
    {
        return true;
    }
    else
        return false;
}*/

class PolygonsExercise: public GlutWindow {
    vector<MyPolygon*> polygons;
public:
    PolygonsExercise(const string &title,int argc,char **argv)
            :GlutWindow(argc, argv, title, 1000, 1000, FIXED) {};

    void onStart() override;
    void onDraw() override;
//    void onJudge() override;
    void onQuit() override;
//    void onMouseMove(double cx,double cy) override;
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

    MyPolygon *Q50 = new MyPolygon(51);
    srand((unsigned int) (time(NULL)));
    for(int i=0;i<50;i++) {
        Q50->addVertex(Vector2D((rand() % (450 - 50 + 1)) + 50,(rand() % (450 - 50 + 1)) + 50));
    }
    //polygons.push_back(Q50);
    /*MyPolygon *Qpoint = new MyPolygon(51);

    srand((unsigned int) (time(NULL)));
    for(int i=0; i<N; i++)
    {
        node[i].x=(rand() % (450 - 50 + 1)) + 50;
        node[i].y=(rand() % (450 - 50 + 1)) + 50;
        Qpoint->addVertex(Vector2D(node[i].x,node[i].y));
    }
    polygons.push_back(Qpoint);
    sort(node, node+N, cmp1);
    stack<Node> s;
    s.push(node[0]);
    u = node[0];
    sort(node+1, node+N, cmp2);
    s.push(node[1]);
    s.push(node[2]);
    for(int i=3; i<N; i++){
        Node top = s.top();
        s.pop();
        Node n_top = s.top();
        if(right(node[i], top, n_top)){
            s.push(node[i]);
        }
        else{
            s.push(top);
            s.push(node[i]);
        }
    }
    vector<Vector2D> tabs;
    while(!s.empty()){
        printf("%d %d\n",s.top().x, s.top().y);
        tabs.push_back(Vector2D(s.top().x,s.top().y));
        s.pop();
    }
    MyPolygon *Q200 = new MyPolygon(tabs.size()+1);
    for(int i=0;i<tabs.size();i++){
        Q200->addVertex(tabs.at(i));
    }
    polygons.push_back(Q200);*/
    /*MyPolygon *Q = new MyPolygon(Q200->getN());
    Vector2D* tab=Q200->gettabPts();
    for(int i=0;i<N;i++){
        Q->addVertex(tab[i]);
    }
   polygons.push_back(Q);*/
    /*int i=1;
    for (auto p:polygons){
        bool result=p->isConvex();
        if(result==true) cout<<"polygon No."<<i<<" is a convex."<<endl;
        else cout<<"polygon No."<<i<<" is not a convex."<<endl;
        i++;
    }*/
    vector<Vector2D> tabs;

    int nPtCnt = 200; //生成的随机点数
    MyPolygon *Q50o = new MyPolygon(nPtCnt+1);
    PTARRAY vecSrc, vecCH;
    for (int i = 0; i < nPtCnt; ++i) {
        Vector2D ptIn ( (rand() % (450 - 50 + 1)) + 50, (rand() % (450 - 50 + 1)) + 50 );
        vecSrc.push_back(ptIn);
       // cout << ptIn.x << ", " << ptIn.y << endl;
       Q50o->addVertex(Vector2D(ptIn.x,ptIn.y));
    }
    polygons.push_back(Q50o);
    CalcConvexHull(vecSrc);
   // cout << "\nConvex Hull:\n";
    for (PTARRAY::iterator i = vecSrc.begin(); i != vecSrc.end(); ++i) {
       // cout << i->x << ", " << i->y << endl;
       tabs.push_back(Vector2D(i->x,i->y));
    }
    MyPolygon *Q = new MyPolygon(tabs.size()+1);
    for(int i=0;i<tabs.size();i++){
        Q->addVertex(tabs.at(i));
    }
    polygons.push_back(Q);
}



void PolygonsExercise::onDraw() {
    //for (auto p:polygons) {
        //p->draw_point();
   // }
    polygons[1]->draw();
    polygons[0]->draw_point();
}


/*void PolygonsExercise::onMouseMove(double cx, double cy) {
    for (auto p:polygons){
        p->onMouseMove(cx,cy);
    }
}*/

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

