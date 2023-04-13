//
// Created by 11357 on 2020/12/7.
//

#ifndef CIRCUMSCRIBE_MESH_H
#define CIRCUMSCRIBE_MESH_H

#include "Triangle.h"
#include <vector>
#include <list>

class Mesh{
public:
    std::vector<Vector2D> vertices;
    std::vector<Triangle> triangles;
    Mesh(float v_t[][2], int v_n, int t_t[][3], int t_n){
        for (int i=0; i<v_n; i++) {
            vertices.emplace_back(Vector2D(v_t[i][0],v_t[i][1]));}
        for (int i=0; i<t_n; i++) {
            triangles.emplace_back(Triangle(&vertices.at(t_t[i][0]),
                                            &vertices.at(t_t[i][1]),
                                            &vertices.at(t_t[i][2])));
        }
        checkDelaunay();
    }

    bool checkDelaunay(){
        bool status=true;
        auto t = triangles.begin();
        while (t!=triangles.end()){
            if(t->checkDelauney(vertices)&&status){status=true;}
            else status = false;
            t++;
        }
        return status;
    }

    void changeDelaunay() {
        list<Triangle*> listrian;
        auto t = triangles.begin();
        while (t!=triangles.end()) {
            listrian.push_back(&(*t));
            t++;}
        while (listrian.size()>1) {
            Triangle *Tri = listrian.front();
            listrian.pop_front();
            if (!Tri->isDelaunay) {
                Triangle *neigbr = getNeighbor(Tri);
                if (neigbr!=nullptr) {
                    flip(*Tri,*neigbr);
                    auto tri=listrian.begin();
                    while (tri!=listrian.end() && (*tri)!=neigbr) {tri++;}
                    if (tri!=listrian.end()) listrian.erase(tri);
                }
                else listrian.push_back(Tri);
            }
        }
    }

    Triangle* findTriangle(const Vector2D *P1,const Vector2D *P2) {
        auto tri = triangles.begin();
        while (tri!=triangles.end() && !((tri->ptr[0]==P1&&tri->ptr[1]==P2)||
            (tri->ptr[1]==P1&&tri->ptr[2]==P2)||(tri->ptr[2]==P1&&tri->ptr[0]==P2))){tri++;}
        if (tri==triangles.end()){return nullptr;}
        return &*tri;
    }
    
    Triangle* getNeighbor(const Triangle *T) {
        Triangle *tri1 = findTriangle(T->ptr[1],T->ptr[0]);
        if(tri1){
            if (tri1->ptr[0]!=T->ptr[0] && tri1->ptr[0]!=T->ptr[1] &&
                tri1->ptr[0]!=T->ptr[2] && T->isInsideCircle(*tri1->ptr[0])) return tri1;
            if (tri1->ptr[1]!=T->ptr[0] && tri1->ptr[1]!=T->ptr[1] &&
                tri1->ptr[1]!=T->ptr[2] && T->isInsideCircle(*tri1->ptr[1])) return tri1;
            if (tri1->ptr[2]!=T->ptr[0] && tri1->ptr[2]!=T->ptr[1] &&
                tri1->ptr[2]!=T->ptr[2] && T->isInsideCircle(*tri1->ptr[2])) return tri1;
        }
        tri1 = findTriangle(T->ptr[2],T->ptr[1]);
        if (tri1) {
            if (tri1->ptr[0]!=T->ptr[0] && tri1->ptr[0]!=T->ptr[1] && tri1->ptr[0]!=T->ptr[2] &&
                T->isInsideCircle(*tri1->ptr[0])) return tri1;
            if (tri1->ptr[1]!=T->ptr[0] && tri1->ptr[1]!=T->ptr[1] && tri1->ptr[1]!=T->ptr[2] &&
                T->isInsideCircle(*tri1->ptr[1])) return tri1;
            if (tri1->ptr[2]!=T->ptr[0] && tri1->ptr[2]!=T->ptr[1] && tri1->ptr[2]!=T->ptr[2] &&
                T->isInsideCircle(*tri1->ptr[2])) return tri1;
        }
        tri1 = findTriangle(T->ptr[0],T->ptr[2]);
        if (tri1) {
            if (tri1->ptr[0]!=T->ptr[0] && tri1->ptr[0]!=T->ptr[1] && tri1->ptr[0]!=T->ptr[2] &&
                T->isInsideCircle(*tri1->ptr[0])) return tri1;
            if (tri1->ptr[1]!=T->ptr[0] && tri1->ptr[1]!=T->ptr[1] && tri1->ptr[1]!=T->ptr[2] &&
                T->isInsideCircle(*tri1->ptr[1])) return tri1;
            if (tri1->ptr[2]!=T->ptr[0] && tri1->ptr[2]!=T->ptr[1] && tri1->ptr[2]!=T->ptr[2] &&
                T->isInsideCircle(*tri1->ptr[2])) return tri1;
        }
        return nullptr;
    }

    Triangle* returnTriangle(const Vector2D P1) {
        auto tri = triangles.begin();
        while (tri!=triangles.end() && !(tri->isInside(P1))){tri++;}
        if (tri==triangles.end()) return nullptr;
        return &*tri;
    }

    void flip(Triangle &ptr1,Triangle &ptr2) {
        Vector2D *P1 = ptr1.VertexOutside(ptr2);
        Vector2D *P2 = ptr2.VertexOutside(ptr1);
        Vector2D *P3 = ptr1.NextVertex(P1);
        Vector2D *P4 = ptr2.NextVertex(P2);
        ptr1.updateVertices(P1,P3,P2);
        ptr2.updateVertices(P2,P4,P1);
    }

};

#endif //CIRCUMSCRIBE_MESH_H
