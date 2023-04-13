//
// Created by 11357 on 2020/12/7.
//

#ifndef CARS_VORONOI_H
#define CARS_VORONOI_H
#include <vector>
#include "Mesh.h"
#include "Polygon.h"


class Voronoi {
    std::vector<MyPolygon*> polygons;
public:
    Voronoi(const Mesh &mesh);
    ~Voronoi();
    void draw();
    MyPolygon* findPolygon(const Vector2D &pos);
    void triangulatePolygons();
};

#endif //CARS_VORONOI_H
