//
// Created by 11357 on 2020/12/30.
//

#ifndef CIRCUMSCRIBE_POLYGON_H
#define CIRCUMSCRIBE_POLYGON_H


#include "Vector2D.h"
#include "Triangle.h"
#include <ctime>
#include <stdlib.h>
#include <stack>
#include <vector>
#include <array>
#include <glutWindow.h>
#include <algorithm>

bool polarComparison(const Vector2D &P1,const Vector2D &P2) {
    double a1 = asin(P1.y/sqrt(P1.x*P1.x+P1.y*P1.y));
    if (P1.x<0.0) a1=M_PI-a1;
    double a2 = asin(P2.y/sqrt(P2.x*P2.x+P2.y*P2.y));
    if (P2.x<0.0) a2=M_PI-a2;
    return a1<a2;
}

class MyPolygon {
    Vector2D *tabPts;
    int Nmax; // Maximim number of vertices
    int N; // current number of vertices
    vector<Triangle> tabTriangles;
    array<float,4> color;
public :
    MyPolygon(int c_Nmax):Nmax(c_Nmax) {
        tabPts = new Vector2D[Nmax];
        N=0;
    }

    MyPolygon(vector<Vector2D> &points){
        assert(points.size()>3);
        auto p=points.begin();
        auto pymin=points.begin();

        // find point with minimal y and swap with first point
        while (p!=points.end()) {
            if (p->y<pymin->y) {
                pymin=p;
            }
            p++;
        }
        // swap
        if (pymin!=points.begin()) iter_swap(points.begin(), pymin);

        Vector2D origin(points.begin()->x,points.begin()->y);
        // copy points in a set of points relative to points[0]
        vector<Vector2D> pointsRelative;
        for (auto pOrig:points) {
            pointsRelative.push_back(Vector2D(pOrig.x-origin.x,pOrig.y-origin.y));
        }

        // sorting point with angular criteria
        sort(pointsRelative.begin()+1,
             pointsRelative.end(),polarComparison);

        stack<Vector2D*> CHstack;
        Vector2D *top_1,*top;
        CHstack.push(&pointsRelative[0]);
        CHstack.push(&pointsRelative[1]);
        CHstack.push(&pointsRelative[2]);

        vector<Vector2D>::iterator pi=pointsRelative.begin()+3;
        while (pi!=pointsRelative.end()) {
            top = CHstack.top();
            CHstack.pop();
            top_1 = CHstack.top();
            CHstack.push(top);
            while (!isOnTheLeft(&(*pi),top_1,top)) {
                CHstack.pop();
                // update values of top and top_1
                top = CHstack.top();
                CHstack.pop();
                top_1 = CHstack.top();
                CHstack.push(top);
            }
            CHstack.push(&(*pi));
            pi++;
        }

        // get stack points to create current polygon
        N=CHstack.size();
        Nmax = N;
        tabPts = new Vector2D[Nmax+1];
        int i=N-1;
        while (!CHstack.empty()) {
            tabPts[i--]=*(CHstack.top())+origin;
            CHstack.pop();
        }
        tabPts[N]=tabPts[0];
        setColor(YELLOW);
    }

    ~MyPolygon() {
        delete [] tabPts;
    }

    Vector2D* gettabPts(){
        return tabPts;
    }
    inline int getNbPts() { return N; };
    inline Vector2D* getPtrPt(int i) { return &tabPts[i]; };

    void addVertex(const Vector2D &p) {
        // we memorize N+1 vertices with tabPts[N]==tabPts[0]
        if (N!=Nmax-1){
            tabPts[N]=p;

        }
        if (N==0){
            tabPts[Nmax-1]=tabPts[0];
        }

        ++N;

    }

    void triangulation(){
        tabTriangles.clear();
        vector<Vector2D*> tmp; // copy the list of vertices into the tmp list
        for (int i=0; i<N; i++) {
            tmp.push_back(&(tabPts[i]));
        }
        int n=N;
        while (n>2) {
            int i=0;
            auto p = tmp.begin();
            bool test;
            Triangle T(*p,*(p+1),*(p+2));
            do {
                test=!T.isEmpty(tmp,i+3);
                if (test) {
                    i++;
                    p++;
                    T=Triangle(*p,*(p+1),*(p+2));
                }
            } while (i<n-2 && test);
            assert(i<n-2);
            tabTriangles.push_back(T);
            tmp.erase(p+1);
            n--;
        }
    }

    bool isConvex() {
        bool result0=isOnTheLeft(tabPts[2],0);
        for(int i=1;i<Nmax-2;i++){
            bool result1=isOnTheLeft(tabPts[i+2],i);
            if(result1!=result0)
                return false;
        }
        return true;
    }

    void draw_point() {
        glPointSize(3);
        glBegin(GL_POINTS);
        glColor3f(1.0f, 0.0f, 0.0f);
        for(int i=0;i<Nmax;i++){
            glVertex2f(tabPts[i].x,tabPts[i].y);
        }
        glEnd();
    }


    double surface() {
        if (tabTriangles.size()==0) triangulation();
        double s=0;
        for (auto t:tabTriangles) {
            s+=t.surface();
        }
        return s;
    }

    void draw_point_B() {
        glPointSize(3);
        glBegin(GL_POINT);
        glColor3f(0.0f, 1.0f, 0.0f);
        for(int i=0;i<Nmax;i++){
            glVertex2f(tabPts[i].x,tabPts[i].y);
        }
        glEnd();
    }
    void draw_G() {
        std::vector<int> trianList;
        trianglation(trianList);


        for(int i=0;i<trianList.size();i+=3)
        {
            glBegin(GL_POLYGON);
            glColor3f(0.0f, 1.0f, 0.0f);
            glVertex2d(tabPts[trianList[i]].x,tabPts[trianList[i]].y);
            glVertex2d(tabPts[trianList[i+1]].x,tabPts[trianList[i+1]].y);
            glVertex2d(tabPts[trianList[i+2]].x,tabPts[trianList[i+2]].y);
            glEnd();
            glFlush();
        }
    }
    bool addPoint(const Vector2D &p) {
        if (Nmax==N-2) return false;
        tabPts[N++]=p;
        tabPts[N]=tabPts[0];
        return true;
    }

    int LineSide(const Vector2D & p,const Vector2D & pa,const Vector2D & pb)//Determine whether the point is on
    {                                                                       // the left or right or on the line
        float f = (pb.x-pa.x)*(p.y-pa.y) - (p.x-pa.x)*(pb.y-pa.y);
        if(f>0)
            return 1;
        else if(f<0)
            return -1;
        else
            return 0;
    }

    bool insertPoint(const Vector2D &p,int index) {
        if (Nmax==N-2) return false;
        for (int i=N; i>index; i--) {
            tabPts[i]=tabPts[i-1];
        }
        tabPts[index]=p;
        tabPts[++N]=tabPts[0];
        return true;
    }

    void trianglation(std::vector<int>& trianList)//Ear clipping method
    {
        bool pIsConvex = isConvex();  // if convex


        std::vector<int> flagList;
        for(int i=0;i<Nmax;i++)
        {
            flagList.push_back(i);  // the number of nodes
        }


        while(true)
        {
            // the last 3 node must be a triangle
            if(flagList.size()==3)
            {
                trianList.push_back(flagList[0]);
                trianList.push_back(flagList[1]);
                trianList.push_back(flagList[2]);
                break;
            }

            // Traverse and take three adjacent vertices to find a suitable vertex that can form a triangle
            for(int i=0;i<flagList.size();i++)
            {
                int i1= (i+1)%flagList.size();
                int i2 = (i+2)%flagList.size();
                int index1 = flagList[i];
                int index2 = flagList[i1];
                int index3 = flagList[i2];

                // Determine whether it is a bump
                int result = LineSide(tabPts[index3],tabPts[index1],tabPts[index2]);
                if(result!=1)  // 1 means on the left
                    continue;

                // Determine whether there are other vertices in the generated triangle
                if(!pIsConvex)
                {
                    bool bIncludeOtherVertex = false;
                    for(int j=0;j<flagList.size();j++)
                    {
                        if(j==i||j==i1||j==i2)  // pass this
                            continue;

                        int pointIndex = flagList[j];
                        if( LineSide(tabPts[pointIndex], tabPts[index1],tabPts[index2])==1 &&
                            LineSide(tabPts[pointIndex], tabPts[index2],tabPts[index3])==1 &&
                            LineSide(tabPts[pointIndex], tabPts[index3],tabPts[index1])==1 )
                        {
                            bIncludeOtherVertex = true;
                            break;
                        }
                    }
                    if(bIncludeOtherVertex)  // The formed triangle contains other vertices
                        continue;
                }


                flagList.erase( flagList.begin() + i1 );  // Delete intermediate amount
                trianList.push_back(index1);
                trianList.push_back(index2);
                trianList.push_back(index3);
                break;
            }

        }


    }
    void draw_old(){
        std::vector<int> trianList;
        trianglation(trianList);


        for(int i=0;i<trianList.size();i+=3)
        {
            glBegin(GL_POLYGON);
            glColor3f(1.0f, 1.0f, 0.0f);
            glVertex2d(tabPts[trianList[i]].x,tabPts[trianList[i]].y);
            glVertex2d(tabPts[trianList[i+1]].x,tabPts[trianList[i+1]].y);
            glVertex2d(tabPts[trianList[i+2]].x,tabPts[trianList[i+2]].y);
            glEnd();
            /*glBegin(GL_LINE_LOOP);
            glColor3f(0.0f, 0.0f, 0.0f);
            glVertex2d(tabPts[trianList[i]].x,tabPts[trianList[i]].y);
            glVertex2d(tabPts[trianList[i+1]].x,tabPts[trianList[i+1]].y);
            glVertex2d(tabPts[trianList[i+2]].x,tabPts[trianList[i+2]].y);
            glEnd();*/
            glFlush();
        }

    }

    void draw() {
        if (tabTriangles.empty()) {
            triangulation();
        }

        // draw the interior
        glColor4fv(&color[0]);
        /*glBegin(GL_POLYGON);
        for (int i=0; i<N; i++) {
            glVertex2f(tabPts[i].x,tabPts[i].y);
        }
        glEnd();
        glBegin(GL_TRIANGLES);
        for (int i=0; i<N-1; i++) {
            glVertex2f(tabPts[0].x,tabPts[0].y);
            glVertex2f(tabPts[i].x,tabPts[i].y);
            glVertex2f(tabPts[i+1].x,tabPts[i+1].y);
        }
        glEnd();*/

        for (auto t:tabTriangles) {
            glBegin(GL_TRIANGLES);
            glVertex2f(t.ptr[0]->x,t.ptr[0]->y);
            glVertex2f(t.ptr[1]->x,t.ptr[1]->y);
            glVertex2f(t.ptr[2]->x,t.ptr[2]->y);
            glEnd();
        }
        // draw the border
        /*glColor4fv(&BLUE[0]);
        glBegin(GL_LINE_LOOP);
        for (auto t:tabTriangles) {
            glVertex2f(t.ptr[0]->x,t.ptr[0]->y);
            glVertex2f(t.ptr[1]->x,t.ptr[1]->y);
            glVertex2f(t.ptr[2]->x,t.ptr[2]->y);
        }
        glEnd();*/

        glColor3fv(&BLACK[0]);
        glLineWidth(3);
        glBegin(GL_LINE_LOOP);
        for (int i=0; i<N; i++) {
            glVertex2f(tabPts[i].x,tabPts[i].y);
        }
        glEnd();
        glLineWidth(1);
        // draw the number of points
        /*for (int i=0; i<N; i++) {
            glBegin(GL_LINES);
            glVertex2f(tabPts[i].x-10,tabPts[i].y-10);
            glVertex2f(tabPts[i].x+10,tabPts[i].y+10);
            glEnd();
            glBegin(GL_LINES);
            glVertex2f(tabPts[i].x+10,tabPts[i].y-10);
            glVertex2f(tabPts[i].x-10,tabPts[i].y+10);
            glEnd();
            GlutWindow::drawText(tabPts[i].x-10,tabPts[i].y,to_string(i),GlutWindow::ALIGN_RIGHT);
        }*/
    }

    void setColor(const array<float,4> &t_color) {
        color = t_color;
    }

    bool isOnTheLeft(const Vector2D *P,const Vector2D *P1,const Vector2D *P2) {
        Vector2D AB = *P2-*P1,
                AP = *P-*P1;
        return (AB.x*AP.y - AB.y*AP.x)>=0; // z component of AB X AP
    }

    bool isOnTheLeft(const Vector2D &P,int i) {
        Vector2D AB = tabPts[i+1]-tabPts[i],
                AP = P-tabPts[i];
        return (AB.x*AP.y - AB.y*AP.x)>=0;
    }

    bool isInside(Vector2D p){
        int i,j;
        bool status = false;
        for(i=1,j=0;i<Nmax;j=i++){
            bool pInLineY = tabPts[i].y<=p.y && p.y<tabPts[j].y || tabPts[j].y<=p.y && p.y<tabPts[i].y;
            if(!pInLineY) continue;

            float fSlope = (tabPts[j].x - tabPts[i].x) / (tabPts[j].y - tabPts[i].y);  // slope
            float x = (p.y - tabPts[i].y) * fSlope + tabPts[i].x;

            if ( pInLineY && p.x < x )
                status = !status;
        }
        return status;
    }

    bool isInsideTriangles(double cx,double cy){
        std::vector<int> trianList;
        trianglation(trianList);
        bool status = false;
        for(int i=0;i<trianList.size();i+=3)
        {
            int k,j;
            for(k=i,j=k+2;k<i+3;j=++k){
                bool pInLineY = tabPts[trianList[k]].y<=cy && cy<tabPts[trianList[j]].y || tabPts[trianList[j]].y<=cy && cy<tabPts[trianList[k]].y;
                if(!pInLineY) continue;

                float fSlope = (tabPts[trianList[j]].x - tabPts[trianList[k]].x) / (tabPts[trianList[j]].y - tabPts[trianList[k]].y);  // slope
                float x = (cy - tabPts[trianList[k]].y) * fSlope + tabPts[trianList[k]].x;

                if ( pInLineY && cx < x )
                    status = !status;
            }
            if (status==true) break;
        }
        return status;
    }

    void onMouseMove(double cx,double cy){
        time_t now = time(0);
        char* dt = ctime(&now);
        cout << "time: " << dt<<"  ";
        if (isInsideTriangles(cx,cy)){
            cout<<"inside"<<endl;
            draw_G();
        }else cout<<"outside"<<endl;
    }

    void clip(int x0,int y0,int x1,int y1) {
        int i=0;
        while (i<N) {
            // case Left/Bottom
            if (tabPts[i].x==x0 && tabPts[i+1].y==y0) {
                insertPoint(Vector2D(x0,y0),i+1);
                i++;
            } else // case Bottom/Right
            if (tabPts[i].y==y0 && tabPts[i+1].x==x1) {
                insertPoint(Vector2D(x1,y0),i+1);
                i++;
            } else // case Right/Top
            if (tabPts[i].x==x1 && tabPts[i+1].y==y1) {
                insertPoint(Vector2D(x1,y1),i+1);
                i++;
            } else // case Top/Left
            if (tabPts[i].y==y1 && tabPts[i+1].x==x0) {
                insertPoint(Vector2D(x0,y1),i+1);
                i++;
            }

            i++;
        }
    }


    double angle(double cx, double cy){
        double leng=sqrt(cx*cx+cy*cy);
        double ang=asin(cy/leng)*180/3.1415;
        return ang;
    }

    bool isAVertex(const Vector2D &pt) {
        int i=0;
        Vector2D *ptr = tabPts;
        while (i<N && (pt.x!=ptr->x || pt.y!=ptr->y)) {
            i++;
            ptr++;
        }
        return (i!=N);
    }

    vector<double> getAngle(){
        vector<double> angles;
        for(int i=0;i<Nmax;i++){
            angles.push_back(angle(tabPts[i].x,tabPts[i].y));
        }
        return angles;
    }


};

#endif //CIRCUMSCRIBE_POLYGON_H
