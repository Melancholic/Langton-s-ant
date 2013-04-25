#include <cstdlib>
#include <GL/glut.h>
#include"window.h"
#include<iostream>
int main(int argc, char** argv) {
    int h,w,b;
    std::cout<<"Введите парметры окна: <ширину> <высоту> <кол-во клеток> : ";
    std::cin>>h>>w>>b;
    window::init(h,w,b);
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(window::getWidth(),window::getHeight());
    glutInitWindowPosition(80,80);
    glutCreateWindow("Langton ant");
    glClearColor(3.0, 3.0, 1.0, 1.0);
    glLoadIdentity();
    glMatrixMode(GL_PROJECTION);
    glViewport(0,0,400,300);
    gluOrtho2D(0.0, window::getWidth(), 0.0,window::getHeight() );
    glutDisplayFunc(window::draw);
    window::process(1);
    glutMainLoop();
    return 0;
}