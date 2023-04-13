//
// Created by 11357 on 2020/12/7.
//

#ifndef CIRCUMSCRIBE_DETERMINANT_H
#define CIRCUMSCRIBE_DETERMINANT_H

class Matrix33;
class Matrix44;

class Matrix22 {
public:
    float m[2][2];

    void get2x2From3x3(const Matrix33 &mat33,int shadowLin, int shadowCol);
    inline float determinant() {
        return m[0][0]*m[1][1]-m[0][1]*m[1][0];
    }
};

class Matrix33 {
public:
    float m[3][3];

    void get3x3From4x4(const Matrix44 &mat44,int shadowLin, int shadowCol);
    float determinant();
};

class Matrix44 {
public:
    float m[4][4];

    float determinant();
};


void Matrix22::get2x2From3x3(const Matrix33 &mat33,int shadowLin, int shadowCol) {
    int l=0;
    for (int lig=0; lig<3; lig++) {
        if (lig!=shadowLin) {
            int c=0;
            for (int col=0; col<3; col++) {
                if (col!=shadowCol) {
                    m[l][c] = mat33.m[lig][col];
                    c++;
                }
            }
            l++;
        }
    }
}

void Matrix33::get3x3From4x4(const Matrix44 &mat44,int shadowLin, int shadowCol) {
    int l=0;
    for (int lig=0; lig<4; lig++) {
        if (lig!=shadowLin) {
            int c=0;
            for (int col=0; col<4; col++) {
                if (col!=shadowCol) {
                    m[l][c] = mat44.m[lig][col];
                    c++;
                }
            }
            l++;
        }
    }
}

float Matrix33::determinant() {
    Matrix22 mat22;
    float det=0;

    float sign=1;
    for (int i=0; i<3; i++) {
        mat22.get2x2From3x3(*this,i,0);
        det += sign*m[i][0]*mat22.determinant();
        sign = -sign;
    }
    return det;
}


float  Matrix44::determinant() {
    Matrix33 mat33;
    float det=0;

    float sign=1;
    for (int i=0; i<4; i++) {
        mat33.get3x3From4x4(*this,i,0);
        det += sign*m[i][0]*mat33.determinant();
        sign = -sign;
    }
    return det;
}


#endif //CIRCUMSCRIBE_DETERMINANT_H
