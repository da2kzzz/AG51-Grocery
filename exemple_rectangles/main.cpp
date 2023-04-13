#include <iostream>
#include <cstdlib>
#include <glutWindow.h>

using namespace std;

class Rectangles: public GlutWindow {
    int value=10;
    bool isOverBox1,isOverBox2;
public:
    Rectangles(const string &title,int argc,char **argv):
    GlutWindow(argc,argv,title,800,100,PROPORTIONAL) {};

    void onStart() override;
    void onDraw() override;
    void onQuit() override;
    void onMouseMove(double cx,double cy) override;
    void onMouseDown(int button,double cx,double cy) override;
};

void Rectangles::onStart() {
    cout << "Start..."  << endl;
    glClearColor(0.25,0.25,0.25,1.0);
}

void Rectangles::onQuit() {
    cout << "The end."  << endl;
}

void Rectangles::onDraw() {
    glPushMatrix();

    glColor3f(1.0f,0.0f,0.0f);
    if (isOverBox1) {
        box(0.05, 0.05, 0.25, 0.9);
    } else {
        rect(0.05, 0.05, 0.25, 0.9);
    }
    glColor3f(0.0f,1.0f,0.0f);
    if (isOverBox2) {
        box(0.7, 0.05, 0.25, 0.9);
    } else {
        rect(0.7, 0.05, 0.25, 0.9);
    }

    glColor3f(1.0,1.0,1.0);
    ellipse(0.5,0.5,0.075,0.45);
    drawText(0.5,0.5,to_string(value),ALIGN_CENTER);
    glPopMatrix();
}

void Rectangles::onMouseMove(double cx,double cy) {
    isOverBox1 = isInRect(cx,cy,0.05,0.05,0.25,0.9);
    isOverBox2 = isInRect(cx,cy,0.7,0.05,0.25,0.9);
}

void Rectangles::onMouseDown(int button, double cx, double cy) {
    if (isOverBox1) {
        value--;
    } else if (isOverBox2) {
        value++;
    }
}

int main(int argc,char **argv) {
    Rectangles ex("Rectangles", argc,argv);
    ex.start();
    return 0;
}

