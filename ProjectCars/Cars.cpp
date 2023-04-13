//
// Created by 11357 on 2021/1/3.
//

#include "glutWindow.h"
#include "Cars.h"
#include <algorithm>

void CarData::updateSpeed(double dt) {
    if (ptrServer!= nullptr) {
        Vector2D a = (goal-position)+sumF;
        V = 0.95 * V + ((float) (dt)) * a;
        position = position + ((float) (dt)) * V;
    }
}

void CarData::glDraw() {
    /*if (ptrServer!= nullptr) {
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

    }*/
}

void TextureData::addCar(CarData *ptr) {
    links2Car.push_back(ptr);
    setCarGoal(ptr);
    cout << "Car " << ptr->id << " added to " << name << endl;
    cout << "verif=" << links2Car[links2Car.size()-1]->id << endl;
}

void TextureData::removeCar(CarData *ptr) {
    auto it = links2Car.begin();
    while (it!=links2Car.end() && (*it)->id!=ptr->id) {
        it++;
    }
    if (it!=links2Car.end()) {
        links2Car.erase(it);
        cout << "Car " << ptr->id << " removed from " << name << endl;
    } else {
        cerr << "Car " << ptr->id << " not found in " << name << endl;
        printCars();
    }
}

void TextureData::printCars() {
    cout << "size=" << links2Car.size() << endl;
    for (auto d:links2Car) {
        cout << d->id << " ";
    }
    cout << endl;
}

void TextureData::addNeighbor(TextureData *neighbor) {
    neighbors.push_back(neighbor);
}

void TextureData::setCarGoal(CarData *Car) {
    float serverWeight=(links2Car.size())/surfaceRate;
    //cout << "Server " << name << " weight=" << serverWeight << " (" << links2Car.size() << " Cars)" << endl;
    sort(neighbors.begin(), neighbors.end(), [](TextureData *a, TextureData *b) {
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