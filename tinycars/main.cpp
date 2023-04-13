#include <iostream>
#include "glutWindow.h"
#include "car.h"
#include "door.h"


car c;
door d;


class TexturedWindow: public GlutWindow {
private:
    GLuint backgroundId;
    GLuint pacmanId,ghostId;
public:

    TexturedWindow(const string &title,int argc,char **argv):
            GlutWindow(argc,argv,title,1200,675,FIXED) {
        backgroundId=0;
        ghostId=0;
        pacmanId=0;
    };

    void onStart() override;
    void onDraw() override;
    void onQuit() override;

    void onMouseDown(int button, double x, double y) override;
};

void TexturedWindow::onStart() {
    glClearColor(1.0,1.0,1.0,1.0); // background color
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void TexturedWindow::onDraw() {

    glEnable(GL_TEXTURE_2D);
    c.draw();

    //draw car and door
   // c.draw();
    d.draw();

    //function to get the curve
    c.curve(d);

    //function to draw the curce
    c.curvedr();


    glDisable(GL_TEXTURE_2D);


}


void TexturedWindow::onMouseDown(int button, double x, double y) {
    glEnable(GL_TEXTURE_2D);
    cout << "click" <<endl;
    c.go();
    glDisable(GL_TEXTURE_2D);

}

void TexturedWindow::onQuit() {
    glDeleteTextures(1,&backgroundId);
}

int main(int argc,char **argv) {
    TexturedWindow win("Single Car", argc,argv);
    win.start();
    return 0;
}
