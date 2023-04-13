//
// Created by bpiranda on 22/11/2019.
//

#ifndef VECTOR2D_H
#define VECTOR2D_H

class Vector2D {
public :
    float x,y;
    Vector2D():x(0),y(0) {};
    Vector2D(const Vector2D &v) {x=v.x; y=v.y; }
    Vector2D(float p_x,float p_y):x(p_x),y(p_y) {};
    Vector2D operator-(const Vector2D &op2) const {
        return Vector2D(x - op2.x, y - op2.y);
    }
    Vector2D operator+(const Vector2D &op2) const {
        return Vector2D(x + op2.x, y + op2.y);
    }
    float operator*(const Vector2D &op2) const {
        return x*op2.x+y*op2.y;
    }
    void set(float p_x,float p_y) {
        x=p_x;
        y=p_y;
    }
    void normalize() {
        float norm=sqrt(x*x+y*y);
        x/=norm;
        y/=norm;
    }
    double norm() {
        return sqrt(x*x+y*y);
    }
    Vector2D ortho() {
        return Vector2D(-y,x);
    }
    bool isNull() {
        return x==0 && y==0;
    }
    friend bool operator ==(const Vector2D&,const Vector2D&);
    friend bool operator !=(const Vector2D&,const Vector2D&);
    };

Vector2D operator*(float a,const Vector2D &v) {
    return Vector2D(a*v.x,a*v.y);
}

bool operator ==(const Vector2D&,const Vector2D&);
bool operator !=(const Vector2D&,const Vector2D&);



bool operator ==(const Vector2D &u,const Vector2D &v) {
    return (u.x == v.x && u.y == v.y);
}


bool operator !=(const Vector2D &u,const Vector2D &v) {
    return !(u==v);
}



ostream& operator<<(ostream& os,const Vector2D &V) {
    os << "(" << V.x << "," << V.y << ")";
    return os;
}

istream& operator>>(istream& is,Vector2D &V) {
    is >> V.x;
    is >> V.y;

    return is;
}

#endif //VECTOR2D_H
