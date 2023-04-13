#include <iostream>
#include <glutWindow.h>

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
};

void TexturedWindow::onStart() {
    int lx,ly;
    backgroundId = loadTGATexture("../Textures/femto-st_1200x675.tga",lx,ly);
    assert(backgroundId!=0);
    pacmanId = loadTGATexture("../Textures/pacman.tga",lx,ly);
    assert(pacmanId!=0);
    ghostId = loadTGATexture("../Textures/red_ghost.tga",lx,ly);
    assert(ghostId!=0);
    glClearColor(1.0,1.0,1.0,1.0); // background color
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void TexturedWindow::onDraw() {
    // draw the background
    glEnable(GL_TEXTURE_2D);
    glColor3f(1.0f,1.0f,1.0f);
    glBindTexture(GL_TEXTURE_2D,backgroundId);
    glPushMatrix();
    glBegin(GL_QUADS);
    glTexCoord2f(0.0,0.0);
    glVertex2f(0.0,0.0);
    glTexCoord2f(1.0,0.0);
    glVertex2f(1200.0,0.0);
    glTexCoord2f(1.0,1.0);
    glVertex2f(1200.0,675.0);
    glTexCoord2f(0.0,1.0);
    glVertex2f(0.0,675.0);
    glEnd();

    glBindTexture(GL_TEXTURE_2D,pacmanId);
    glPushMatrix();
    glTranslatef(250,120,1.0);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0,0.0);
    glVertex2f(0.0,0.0);
    glTexCoord2f(1.0,0.0);
    glVertex2f(96.0,0.0);
    glTexCoord2f(1.0,1.0);
    glVertex2f(96.0,96.0);
    glTexCoord2f(0.0,1.0);
    glVertex2f(0.0,96.0);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(400,120,1.0);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0,0.0);
    glVertex2f(0.0,0.0);
    glTexCoord2f(1.0,0.0);
    glVertex2f(96.0,0.0);
    glTexCoord2f(1.0,1.0);
    glVertex2f(96.0,96.0);
    glTexCoord2f(0.0,1.0);
    glVertex2f(0.0,192.0);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(550,120,1.0);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0,0.0);
    glVertex2f(0.0,0.0);
    glTexCoord2f(1.0,0.0);
    glVertex2f(96.0,0.0);
    glTexCoord2f(1.0,1.0);
    glVertex2f(192.0,96.0);
    glTexCoord2f(0.0,1.0);
    glVertex2f(0.0,96.0);
    glEnd();
    glPopMatrix();

    glBindTexture(GL_TEXTURE_2D,ghostId);
    glPushMatrix();
    glTranslatef(250,300,1.0);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0,0.0);
    glVertex2f(0.0,0.0);
    glTexCoord2f(1.0,0.0);
    glVertex2f(96.0,0.0);
    glTexCoord2f(1.0,1.0);
    glVertex2f(96.0,96.0);
    glTexCoord2f(0.0,1.0);
    glVertex2f(0.0,96.0);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(400,300,1.0);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0,0.0);
    glVertex2f(0.0,0.0);
    glTexCoord2f(1.0,0.0);
    glVertex2f(96.0,0.0);
    glTexCoord2f(1.0,1.0);
    glVertex2f(96.0,96.0);
    glTexCoord2f(0.0,1.0);
    //glVertex2f(0.0,192.0);
    glVertex2f(0.0,96.0);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(550,300,1.0);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0,0.0);
    glVertex2f(0.0,0.0);
    glTexCoord2f(1.0,0.0);
    glVertex2f(96.0,0.0);
    glTexCoord2f(1.0,1.0);
    glVertex2f(192.0,96.0);
    glTexCoord2f(0.0,1.0);
    glVertex2f(0.0,96.0);
    glEnd();
    glPopMatrix();

    glPopMatrix();

    glDisable(GL_TEXTURE_2D);
}
void TexturedWindow::onQuit() {
    glDeleteTextures(1,&backgroundId);
}

int main(int argc,char **argv) {
    TexturedWindow win("Textures", argc,argv);
    win.start();

    return 0;
}
