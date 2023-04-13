//
// Created by 11357 on 2020/11/30.
//

#ifndef POLYGONS2020_GRAHAMS_H
#define POLYGONS2020_GRAHAMS_H

#include <algorithm>
#include <iostream>
#include <vector>
#include <math.h>
using namespace std;


typedef vector<Vector2D> PTARRAY;



bool polarComparison(const Vector2D &pt1, const Vector2D &pt2) {
    float m1 = sqrt((float)(pt1.x * pt1.x + pt1.y * pt1.y));
    float m2 = sqrt((float)(pt2.x * pt2.x + pt2.y * pt2.y));
    float v1 = pt1.x / m1, v2 = pt2.x / m2;
    return (v1 > v2 || (v1 == v2 && m1 < m2));
}

void CalcConvexHull(PTARRAY &vecSrc) {
    if (vecSrc.size() < 3) {
        return;
    }

    Vector2D ptBase = vecSrc.front();
    for (PTARRAY::iterator i = vecSrc.begin() + 1; i != vecSrc.end(); ++i) {
        if (i->y < ptBase.y || (i->y == ptBase.y && i->x > ptBase.x)) {
            ptBase = *i;
        }
    }

    for (PTARRAY::iterator i = vecSrc.begin(); i != vecSrc.end();) {
        if (*i == ptBase) {
            i = vecSrc.erase(i);
        }
        else {
            i->x -= ptBase.x, i->y -= ptBase.y;
            ++i;
        }
    }
    sort(vecSrc.begin(), vecSrc.end(), &polarComparison);
    vecSrc.erase(unique(vecSrc.begin(), vecSrc.end()), vecSrc.end());
    for (PTARRAY::reverse_iterator ri = vecSrc.rbegin();
         ri != vecSrc.rend() - 1; ++ri) {
        PTARRAY::reverse_iterator riNext = ri + 1;
        ri->x -= riNext->x, ri->y -= riNext->y;
    }
    for (PTARRAY::iterator i = vecSrc.begin() + 1; i != vecSrc.end(); ++i) {
        for (PTARRAY::iterator iLast = i - 1; iLast != vecSrc.begin();) {
            int v1 = i->x * iLast->y, v2 = i->y * iLast->x;
            if (v1 < v2 || (v1 == v2 && i->x * iLast->x > 0 &&
                            i->y * iLast->y > 0)) {
                break;
            }
            i->x += iLast->x, i->y += iLast->y;
            iLast = (i = vecSrc.erase(iLast)) - 1;
        }
    }
    vecSrc.front().x += ptBase.x, vecSrc.front().y += ptBase.y;
    for (PTARRAY::iterator i = vecSrc.begin() + 1; i != vecSrc.end(); ++i) {
        i->x += (i - 1)->x, i->y += (i - 1)->y;
    }
    vecSrc.push_back(ptBase);
}

#endif //POLYGONS2020_GRAHAMS_H
