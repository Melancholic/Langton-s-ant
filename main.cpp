#include <cstdlib>
#include <GL/glut.h>
#include"window.h"
#include<iostream>
#include"parser.h"
#include<string>
int main(int argc, char** argv) {
    parser Parse;
    if(argc!=1){
        std::string tmp(argv[1]);
        Parse= parser(tmp);
    }else{
        std::cerr<<"\nUse filename in parametr. Select default cfg\n" ;
        Parse= parser("default.cfg");
    }
    int h,w,b,s;
    std::cout<<"Введите парметры окна: <ширину> <высоту> <кол-во клеток> <скорость 0-10>: ";
    std::cin>>h>>w>>b>>s;
    window::init(h,w,b,s,Parse);
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
   glutTimerFunc(0, window::process, 1);
    glutMainLoop();
    return 0;
}
