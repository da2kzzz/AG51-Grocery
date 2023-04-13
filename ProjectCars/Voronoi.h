//
// Created by 11357 on 2021/1/3.
//

#ifndef PROJECTCARS_VORONOI_H
#define PROJECTCARS_VORONOI_H

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
    void triangulatePolygons() {
        auto p=polygons.begin();
        while(p!=polygons.end()) {
            (*p)->triangulation();
            p++;
        }
    }
};

#endif //PROJECTCARS_VORONOI_H
