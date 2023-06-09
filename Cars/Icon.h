//
// Created by Datingpool on 2021/1/4.
//

#ifndef CARS_ICON_H
#define CARS_ICON_H
#include <GL/glut.h>
#include <string>
#include "Vector2D.h"

class Icon {
    GLuint textureId;
    float width,height;
    string title;
public:
    Icon(float c_width,float c_height,const string &c_title);
    ~Icon();
    void initTexture();
    void glDraw();
    inline float getWidth() { return width; };
    inline float getHeight() { return height; };
};

Icon::Icon(float c_width, float c_height, const string &c_title):width(c_width),height(c_height),title(c_title) {
    textureId=0;
}

Icon::~Icon() {

}

void Icon::glDraw() {
    if (textureId==0) {
        int w,h;
        textureId=GlutWindow::loadTGATexture(title,w,h);
    }
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,textureId);
    glScalef(width,height,1.0f);
    glBegin(GL_QUADS);
    glTexCoord2f(0,0);
    glVertex2f(-0.5,-0.5);
    glTexCoord2f(1.0f,0);
    glVertex2f(0.5,-0.5);
    glTexCoord2f(1.0f,1.0f);
    glVertex2f(0.5,0.5);
    glTexCoord2f(0,1.0f);
    glVertex2f(-0.5,0.5);
    glEnd();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
}

#endif //CARS_ICON_H
