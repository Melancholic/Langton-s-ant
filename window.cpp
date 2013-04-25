#include <cstdlib>
#include "window.h"
#include <GL/glut.h>
#include<iostream>
std::vector< std::vector<bool> > window::Area;
int window::Width;
int window::Height;
int window::StepX;
int window::StepY;
ant window::Ant;
int window::Boxes;


int window::getHeight(){
    return Height;
}
int window::getWidth(){
    return Width;
}

int window::getStepX(){
    return StepX;
}
int window::getStepY(){
    return StepY;
}

std::vector< std::vector<bool> > window::getArea(){
    return Area;
}
void window::init(int w, int h, int b){    
    Width=w;
    Height=h;
    Boxes=b;
    StepX=Width/Boxes;
    StepY=Height/Boxes;  
    Ant= ant();
    window:Area.resize(Boxes);
    for(int i=0;i!=window::Area.size();++i){
       window::Area[i].resize(Boxes);
    }
    for(int i=0;i!=window::Area.size();++i){
        for(int j=0;j!=window::Area[i].size();++j){
           window::Area[i][j]=false;
        }
    }
    
}

int window::getCenter(){
    return window::Boxes/2; 
}

void window::process(int a){
    if(window::Area[window::Ant.getX()][window::Ant.getY()]){
        window::Area[window::Ant.getX()][window::Ant.getY()]=!window::Area[window::Ant.getX()][window::Ant.getY()];
        window::Ant.toLeft();
    }else{
        window::Area[window::Ant.getX()][window::Ant.getY()]=!window::Area[window::Ant.getX()][window::Ant.getY()];         
        window::Ant.toRight();  
    }
    window::draw();
    glutTimerFunc(300, window::process, 0);
}
void window::draw(){    
    glClear(GL_COLOR_BUFFER_BIT); 
    glBegin(GL_LINES);  
    glColor3f(.1, .1, 0); 
    for(int i=0;i<window::getWidth();i+=window::getStepX()){
        glVertex2f(i,0);
        glVertex2f(i,window::getHeight());
        
    }  
    for(int i=0;i<window::getHeight();i+=window::getStepY()){
        glVertex2f(0,i);
        glVertex2f(window::getWidth(),i);
        
    } 
    
    glClear(GL_COLOR_BUFFER_BIT);     
    glColor3f(0, 1, 0); 
    glClear(GL_COLOR_BUFFER_BIT);
    glEnd();
    glBegin(GL_QUADS);
    glColor3f(.1, .1, 0); 
    for(int i=0;i<window::Area.size();++i){
        for(int j=0;j<window::Area[i].size();++j){
            if(window::Area[i][j]){
                glVertex2f((i)*window::getStepX(),(j)*window::getStepY());
                glVertex2f((i+1)*window::getStepX(),(j)*window::getStepY());
                glVertex2f((i+1)*window::getStepX(),(j+1)*window::getStepY());//(4,5)
                glVertex2f((i)*window::getStepX(),(j+1)*window::getStepY());
            }
        }
    }  
    glEnd();
    glBegin(GL_QUADS);
    glColor3f(1, 0, 0);  
    glVertex2f((window::Ant.getX())*window::getStepX(),(window::Ant.getY())*window::getStepY());
    glVertex2f((window::Ant.getX()+1)*window::getStepX(),(window::Ant.getY())*window::getStepY());
    glVertex2f((window::Ant.getX()+1)*window::getStepX(),(window::Ant.getY()+1)*window::getStepY());
    glVertex2f((window::Ant.getX())*window::getStepX(),(window::Ant.getY()+1)*window::getStepY());
    glEnd();
    glFlush();
    glutSwapBuffers();
    
   
    
}