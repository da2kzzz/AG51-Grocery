//
// Created by Datingpool on 2021/1/4.
//

#ifndef CARS_CARS_H
#define CARS_CARS_H

#include "Polygon.h"

const float dmax=32*3;
const float dmin=32*1.5;
const float Fmax=100.0;

class CarData;

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
    void addCar(CarData *ptr);
    void removeCar(CarData *ptr);
    void setCarGoal(CarData *Car);
    void addNeighbor(ServerData *neighbor);
    bool CarIsOver(const Vector2D &p) { return ptrPolygon->isInsideTriangles(p.x,p.y); };
    void printCars();
};


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
    void updateSpeed(double dt);
};


#endif //CARS_CARS_H
