//
// Created by 11357 on 2020/12/7.
//

#ifndef CIRCUMSCRIBE_MESH_H
#define CIRCUMSCRIBE_MESH_H

#include "Triangle.h"
#include "Polygon.h"
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

    Mesh(vector<Vector2D> &p_vert) {
        int n = p_vert.size();
        assert(n>=3);
        if (n==3) {
            for (auto v:p_vert) {
                vertices.emplace_back(Vector2D(v.x,v.y));
            }
            // order the 3 points
            Triangle T(&vertices[0],&vertices[1],&vertices[2]);
            if (T.isOnTheLeft(&vertices[2],&vertices[0],&vertices[1])) {
                triangles.push_back(T);
            } else {
                triangles.emplace_back(Triangle(&vertices[0],&vertices[2],&vertices[1]));
            }
        } else {
            MyPolygon CH(p_vert); // calculate convex hull
            Vector2D *ptrPt;
            int nCH = CH.getNbPts();
            for (int i=0; i<nCH; i++) {
                ptrPt=CH.getPtrPt(i);
                vertices.emplace_back(Vector2D(ptrPt->x,ptrPt->y));
            }

            // construct a triangulation of the hull
            for (int i=1; i<nCH-1; i++) {
                triangles.emplace_back(Triangle(&vertices[0],&vertices[i],&vertices[(i+1)%nCH]));
            }

            // add internal points
            auto v = p_vert.begin();
            while (v!=p_vert.end()) {
                if (!CH.isAVertex(*v)) {
                    cout << "internal point:" << *v << endl;
                    subdivide(*v);
                }
                v++;
            }
        }
        checkDelaunay();
    }


    void draw() {
        for (auto t :triangles) {
            t.draw();
        }
        int i=0;
        glColor3fv(&BLACK[0]);
        for (auto p : vertices) {
            GlutWindow::drawText(p.x-10,p.y,to_string(i++),GlutWindow::ALIGN_RIGHT);
        }
        for (auto t :triangles) {
            t.drawCircle();
        }

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

    void subdivide(const Vector2D &P) {
        auto it = triangles.begin();
        while (it != triangles.end() && !it->isInside(P)) it++;
        if (it != triangles.end()) {
            int i = vertices.size();
            vertices.emplace_back(Vector2D(P.x, P.y));
            Vector2D *v[4] = {(*it).ptr[0], (*it).ptr[1], (*it).ptr[2], &vertices[i]};
            triangles.erase(it);
            triangles.emplace_back(Triangle(v[0], v[3], v[2]));
            triangles.emplace_back(Triangle(v[1], v[2], v[3]));
            triangles.emplace_back(Triangle(v[0], v[1], v[3]));
            checkDelaunay();
        }
    }
};

#endif //CIRCUMSCRIBE_MESH_H
