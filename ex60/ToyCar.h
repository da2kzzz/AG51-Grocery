//
// Created by 11357 on 2020/12/30.
//

#ifndef CIRCUMSCRIBE_TOYCAR_H
#define CIRCUMSCRIBE_TOYCAR_H

#include "Polygon.h"
#include <glutWindow.h>
#include <algorithm>

const float dmax=32*3;
const float dmin=32*1.5;
const float Fmax=100.0;

class ServerData;

class CarData {
public:
    int id;
    Vector2D position;
    Vector2D V;
    Vector2D goal;
    Vector2D sumF;
    ServerData *ptrServer;
    CarData() {
        ptrServer= nullptr;
    }

    CarData(const Vector2D& p_position):position(p_position) {
        static int memid=1;

        id=memid++;
        ptrServer= nullptr;
    }
    void glDraw();
    void updateSpeed(double dt){
        if (ptrServer!= nullptr) {
            Vector2D a = (goal-position)+sumF;
            V = 0.95 * V + ((float) (dt)) * a;
            position = position + ((float) (dt)) * V;
        }
    }
};


class ServerData {
public:
    string name;
    Vector2D position;
    string colorName;
    MyPolygon *ptrPolygon;
    vector<CarData*> links2Car;
    double surfaceRate;
    vector<ServerData*> neighbors;

    ServerData() { ptrPolygon= nullptr;};
    ServerData(const string &p_name,const Vector2D &p_position,const string &p_colorName):
            name(p_name),position(p_position),colorName(p_colorName)  { ptrPolygon= nullptr;};
    void addCar(CarData *ptr){
        links2Car.push_back(ptr);
        setCarGoal(ptr);
    }
    void removeCar(CarData *ptr){
        auto it = links2Car.begin();
        while (it!=links2Car.end() && (*it)->id!=ptr->id) {
            it++;
        }
        if (it!=links2Car.end()) {
            links2Car.erase(it);
        } else {
            printCars();
        }
    }
    void setCarGoal(CarData *Car){
        float serverWeight=(links2Car.size())/surfaceRate;
        //cout << "Server " << name << " weight=" << serverWeight << " (" << links2Car.size() << " Cars)" << endl;
        sort(neighbors.begin(), neighbors.end(), [](ServerData *a, ServerData *b) {
            return (a->links2Car.size() + 1) / a->surfaceRate < (b->links2Car.size() + 1) / b->surfaceRate;
        });
        int ind=Car->ptrServer==neighbors[0]?1:0;
        //cout << "Best " << neighbors[0]->name << " weight=" << (neighbors[0]->links2Car.size() + 1) / neighbors[0]->surfaceRate << " (" << neighbors[0]->links2Car.size() << " Cars)" << endl;
        //cout << "Next " << neighbors[1]->name << " weight=" << (neighbors[1]->links2Car.size() + 1) / neighbors[1]->surfaceRate << " (" << neighbors[1]->links2Car.size() << " Cars)" << endl;

        float neighborWeight=(neighbors[ind]->links2Car.size() + 1) / neighbors[ind]->surfaceRate;
        if(serverWeight<neighborWeight) {
            Car->goal = position;
        } else {
            Car->goal = neighbors[ind]->position;
        }
    }
    void addNeighbor(ServerData *neighbor){
        neighbors.push_back(neighbor);
    }
    bool CarIsOver(const Vector2D &p) { return ptrPolygon->isInsideTriangles(p.x,p.y); };
    void printCars(){
        cout << "size=" << links2Car.size() << endl;
        for (auto d:links2Car) {
            cout << d->id << " ";
        }
        cout << endl;
    }
};

void CarData::glDraw() {
    if (ptrServer!= nullptr) {
        glColor4fv(&BLACK[0]);
        glBegin(GL_LINES);
        glVertex2f(0,0);
        glVertex2f(ptrServer->position.x-position.x,ptrServer->position.y-position.y);
        glEnd();
    }
    if (!V.isNull()) {
        Vector2D X=V;
        X.normalize();
        double a,cs,sn;
        glLineWidth(3);
        glBegin(GL_LINES);
        glVertex2f(0,0);
        glVertex2f(V.x,V.y);

        for (int i=0; i<20; i++) {
            a = -0.5*M_PI+i*M_PI/20.0;
            cs = dmax*cos(a);
            sn = dmax*sin(a);
            glVertex2d(cs*X.x-sn*X.y,cs*X.y+sn*X.x);
        }
        a = dmax;
        for (int i=0; i<10; i++) {
            glVertex2d(-a*X.y,a*X.x);
            a-=dmax/5.0;
        }
        glEnd();
        glLineWidth(1);

    }
}


#endif //CIRCUMSCRIBE_TOYCAR_H
