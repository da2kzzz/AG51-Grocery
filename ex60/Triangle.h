// https://etudiants-stgi.pu-pm.univ-fcomte.fr/tp_bpiranda/adv_algo/circumscribe.zip
// Created by bpiranda on 22/11/2019.
//

#ifndef TRIANGLE_H
#define TRIANGLE_H
#include <GL/glut.h>
#include "Vector2D.h"

/*const float BLACK[4]={0.0,0.0,0.0,1.0f};
const float GREY[4]={0.75f,0.75f,0.75f,1.0f};
const float RED[4]={1.0f,0.0,0.0,1.0f};
const float ORANGE[4]={1.0f,0.27f,0.0,1.0f};
const float YELLOW[4]={1.0f,1.0f,0.0,1.0f};
const float GREEN[4]={0.0,1.0f,0.0,1.0f};
const float BLUE[4]={0.0,0.0,1.0f,1.0f};*/

const array<float,4> BLACK={0.0,0.0,0.0,1.0f};
const array<float,4> GREY={0.75f,0.75f,0.75f,1.0f};
const array<float,4> RED={1.0f,0.0,0.0,1.0f};
const array<float,4> ORANGE={1.0f,0.27f,0.0,1.0f};
const array<float,4> YELLOW={1.0f,1.0f,0.0,1.0f};
const array<float,4> GREEN={0.0,1.0f,0.0,1.0f};
const array<float,4> BLUE={0.0,0.0,1.0f,1.0f};
const array<float,4> CYAN={0.0,1.0,1.0f,1.0f};
const array<float,4> PINK={1.0,0.75,0.80f,1.0f};
const array<float,4> BROWN={0.55f,0.3f,0.21f,1.0f};
const array<float,4> SILVER={1.0f,1.0f,1.0f,1.0f};
const array<float,4> PURPLE={0.46f,0.0f,1.0f,1.0f};

class Triangle {
public:
    Vector2D *ptr[3];
    bool isHighlighted;
    Vector2D circumCenter;
    float circumRadius;
    bool isDelaunay=false;

    Triangle(Vector2D *ptr1,Vector2D *ptr2,Vector2D *ptr3) {
        ptr[0] = ptr1;
        ptr[1] = ptr2;
        ptr[2] = ptr3;
        isHighlighted = false;
        calculateCircle();
    }

    void updateVertices(Vector2D *ptr1,Vector2D *ptr2,Vector2D *ptr3) {
        ptr[0] = ptr1;
        ptr[1] = ptr2;
        ptr[2] = ptr3;
        isHighlighted = false;
        calculateCircle();
    }

    void calculateCircle() {
        Vector2D AB=*ptr[1]-*ptr[0];
        Vector2D AC=*ptr[2]-*ptr[0];
        Vector2D V=AC.ortho();
        // calculate circle parameters
        float k = 0.5f*(AB*AB - AC*AB)/(V*AB);

        Vector2D u = (0.5f*AC)+k*V;

        circumCenter=*ptr[0]+u;
        circumRadius = (float)(u.norm());
    }

    void onMouseMove(const Vector2D& pos) {
        isHighlighted=isInside(pos);
    }

    static array<float,4> getColorByName(const string &name) {
        if (name.substr(0,3)=="RED") return RED;
        else if (name.substr(0,4)=="BLUE") return BLUE;
        else if (name.substr(0,5)=="GREEN") return GREEN;
        else if (name.substr(0,4)=="CYAN") return CYAN;
        else if (name.substr(0,6)=="YELLOW") return YELLOW;
        else if (name.substr(0,4)=="PINK") return PINK;
        else if (name.substr(0,6)=="ORANGE") return ORANGE;
        else if (name.substr(0,5)=="BROWN") return BROWN;
        else if (name.substr(0,6)=="SILVER") return SILVER;
        else if (name.substr(0,6)=="PURPLE") return PURPLE;
        return BLACK;
    }

    bool isOnTheLeft(const Vector2D *P,const Vector2D *P1,const Vector2D *P2) {
        Vector2D AB = *P2-*P1,
                AP = *P-*P1;

        return (AB.x*AP.y - AB.y*AP.x)>=0;
    }

    bool ifVertex(const Vector2D *pt) const {
        return pt==ptr[0] || pt==ptr[1] || pt==ptr[2];
    }

    bool isEmpty(const vector<Vector2D*> &tmp,int n) {
        auto p=tmp.begin()+n;
        while (p!=tmp.end() && (!isOnTheLeft(*p,ptr[0],ptr[1]) || !isOnTheLeft(*p,ptr[1],ptr[2]) || !isOnTheLeft(*p,ptr[2],ptr[0]))) {
            p++;
        }
        return p==tmp.end();
    }

    bool isInside(const Vector2D &P) {
        return isOnTheLeft(&P,ptr[0],ptr[1]) && isOnTheLeft(&P,ptr[1],ptr[2]) && isOnTheLeft(&P,ptr[2],ptr[0]);
    }

    Vector2D *VertexOutside(const Triangle &T) const {
        if (ptr[0]!=T.ptr[0] && ptr[0]!=T.ptr[1] && ptr[0]!=T.ptr[2]) return ptr[0];
        if (ptr[1]!=T.ptr[0] && ptr[1]!=T.ptr[1] && ptr[1]!=T.ptr[2]) return ptr[1];
        if (ptr[2]!=T.ptr[0] && ptr[2]!=T.ptr[1] && ptr[2]!=T.ptr[2]) return ptr[2];
        return nullptr;
    }

    Vector2D *NextVertex(const Vector2D *pt) const {
        if (pt==ptr[0]) return ptr[1];
        if (pt==ptr[1]) return ptr[2];
        if (pt==ptr[2]) return ptr[0];
        return nullptr;
    }

    Vector2D *PrevVertex(const Vector2D *pt) const {
        if (pt==ptr[0]) return ptr[2];
        if (pt==ptr[1]) return ptr[0];
        if (pt==ptr[2]) return ptr[1];
        return nullptr;
    }

    Vector2D nextEdgeNormal(const Vector2D *pt) const {
        if (pt==ptr[0]) return Vector2D(ptr[1]->y-ptr[0]->y,-(ptr[1]->x-ptr[0]->x));
        if (pt==ptr[1]) return Vector2D(ptr[2]->y-ptr[1]->y,-(ptr[2]->x-ptr[1]->x));
        if (pt==ptr[2]) return Vector2D(ptr[0]->y-ptr[2]->y,-(ptr[0]->x-ptr[2]->x));
        return Vector2D(0,0);
    }

    Vector2D previousEdgeNormal(const Vector2D *pt) const {
        if (pt==ptr[0]) return Vector2D(-(ptr[2]->y-ptr[0]->y),ptr[2]->x-ptr[0]->x);
        if (pt==ptr[1]) return Vector2D(-(ptr[0]->y-ptr[1]->y),ptr[0]->x-ptr[1]->x);
        if (pt==ptr[2]) return Vector2D(-(ptr[1]->y-ptr[2]->y),ptr[1]->x-ptr[2]->x);
        return Vector2D(0,0);
    }
    void draw() {
        // glColor3fv(isHighlighted?ORANGE:(isDelaunay?GREY:YELLOW));
        glColor4fv(isDelaunay?(isHighlighted?&GREEN[0]:&GREY[0]):(isHighlighted?&RED[0]:&YELLOW[0]));
        glBegin(GL_TRIANGLES);
        glVertex2f(ptr[0]->x,ptr[0]->y);
        glVertex2f(ptr[1]->x,ptr[1]->y);
        glVertex2f(ptr[2]->x,ptr[2]->y);
        glEnd();
        glColor3fv(&BLACK[0]);
        glBegin(GL_LINE_LOOP);
        glVertex2f(ptr[0]->x,ptr[0]->y);
        glVertex2f(ptr[1]->x,ptr[1]->y);
        glVertex2f(ptr[2]->x,ptr[2]->y);
        glEnd();
    }

    void drawCircle() {
        // draw circle
        if (isHighlighted) {
            glColor3fv(&RED[0]);
            glPushMatrix();
            glTranslatef(circumCenter.x,circumCenter.y,0);
            glLineWidth(3);
            glBegin(GL_LINE_LOOP);
            float a=0.0;
            for (int i=0; i<40; i++) {
                glVertex2f(circumRadius*cos(a),circumRadius*sin(a));
                a+=(float)(M_PI/20.0);
            }
            glEnd();
            glLineWidth(1);
            glPopMatrix();
        }
    }

    bool isInsideCircle(const Vector2D &p) const {
        if (p==*ptr[0] || p==*ptr[1] || p==*ptr[2]) return false;
        return ((p-circumCenter).norm()<circumRadius);
    }

    double surface() const {
        double a=(*ptr[1]-*ptr[0]).norm();
        double b=(*ptr[2]-*ptr[1]).norm();
        double c=(*ptr[0]-*ptr[2]).norm();
        double p=0.5*(a+b+c);

        return sqrt(p*(p-a)*(p-b)*(p-c));
    }

    bool checkDelauney(const vector<Vector2D> &vertices) {
        auto v=vertices.begin();
        while (v!=vertices.end() && !isInsideCircle(*v)) {
            v++;
        }
        isDelaunay = (v==vertices.end());
        return isDelaunay;
    }



    string whoami(const vector<Vector2D>& points) const {
        return string("Triangle (") + to_string((int)(ptr[0]-&points[0])) +
               string(",") + to_string((int)(ptr[1]-&points[0])) + string(",") +
               to_string((int)(ptr[2]-&points[0])) + string(")");

    }
};

#endif //TRIANGLE_H
