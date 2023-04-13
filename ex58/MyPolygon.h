//
// Created by 11357 on 2020/11/20.
//

#ifndef POLYGONS2020_MYPOLYGON_H
#define POLYGONS2020_MYPOLYGON_H

#include "Vector2D.h"
#include <ctime>
#include <stdlib.h>

class MyPolygon {
    Vector2D *tabPts;
    int Nmax; // Maximim number of vertices
    int N; // current number of vertices
public :
    MyPolygon(int c_Nmax):Nmax(c_Nmax) {
        tabPts = new Vector2D[Nmax];
        N=0;
    }

    ~MyPolygon() {
        delete [] tabPts;
    }

    Vector2D* gettabPts(){
        return tabPts;
    }
    int getN(){
        return N;
    }

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

    int LineSide(const Vector2D & p,const Vector2D & pa,const Vector2D & pb)//Determine whether the point is on
    {                                                                       // the left or right or on the line
        float f = (pb.x-pa.x)*(p.y-pa.y) - (p.x-pa.x)*(pb.y-pa.y);
        if(f>0)
            return 1;
        else if(f<0)
            return -1;
        else
            return 0;
    };


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
    void draw(){
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


    bool isOnTheLeft(const Vector2D &p,int i){
        float f = (tabPts[i+1].x-tabPts[i].x)*(p.y-tabPts[i].y)-(p.x-tabPts[i].x)*(tabPts[i+1].y-tabPts[i].y);
        if (f>=0) return true;// actually =0 means p is on the line [Pi,Pi+1]
        else return false;
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

    double angle(double cx, double cy){
        double leng=sqrt(cx*cx+cy*cy);
        double ang=asin(cy/leng)*180/3.1415;
        return ang;
    }

    vector<double> getAngle(){
        vector<double> angles;
        for(int i=0;i<Nmax;i++){
            angles.push_back(angle(tabPts[i].x,tabPts[i].y));
        }
        return angles;
    }


};

#endif //POLYGONS2020_MYPOLYGON_H
