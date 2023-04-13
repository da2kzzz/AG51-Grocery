#include <stdio.h>
#include <Windows.h>
#include <GL/glut.h>

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(300, 300);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("testgl");
    const char* version = (const char*)glGetString(GL_VERSION);
    printf("OpenGL 版本: %s\n", version);
    glutMainLoop();
    return 0;
}