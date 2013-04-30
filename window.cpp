#include <cstdlib>
#include "window.h"
#include <GL/glut.h>
#include<iostream>
#include<boost/thread/thread.hpp>
#include <stdio.h>


std::vector< std::vector<bool> > window::Area;
int window::Width;
int window::Height;
int window::StepX;
int window::StepY;
ant window::Ant;
int window::Boxes;
int window::Speed;


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

void window::setAreaFalse(){
    for(int i=0;i!=window::Area.size();++i){
        for(int j=0;j!=window::Area[i].size();++j){
           window::Area[i][j]=false;
        }   
    }
}

void window::init(int w, int h, int b, int s){    
    Width=w;
    Height=h;
    Boxes=b;
    StepX=Width/Boxes;
    StepY=Height/Boxes;  
    Ant= ant();
    if(s>=0 ||s<=10){
            Speed=1000-s*100;
    }else{
        std::cout<<"\nErr value speed - set default(10) ";
        Speed=0;
    }
    window::Area.resize(Boxes);
    for(int i=0;i!=window::Area.size();++i){
       window::Area[i].resize(Boxes);
    }
   window::setAreaFalse();
    
}

int window::getCenter(){
    return window::Boxes/2; 
}
void Values(){
    if((window::Ant.getX()>0 && window::Ant.getX()<window::Area.size()) && (window::Ant.getY()>0 && window::Ant.getY()<window::Area.size())){
        if(window::Area[window::Ant.getX()][window::Ant.getY()]){
            window::Area[window::Ant.getX()][window::Ant.getY()]=!window::Area[window::Ant.getX()][window::Ant.getY()];
            window::Ant.toLeft();
        }else{
            window::Area[window::Ant.getX()][window::Ant.getY()]=!window::Area[window::Ant.getX()][window::Ant.getY()];      
            window::Ant.toRight(); 
        }	
    }else{
        exit(0);    
        window::Ant=ant();
        window::setAreaFalse();
    }
}

void window::process(int a){
  // window::draw();
    glutPostRedisplay();
   boost::thread my_thread1(Values);
   my_thread1.join();
   glutTimerFunc(window::Speed, window::process,1 );
}

void window::draw(){    
  glClear(GL_COLOR_BUFFER_BIT); 
  glLineWidth(1.0f);
    glBegin(GL_LINES);  
    glColor3f(.5, .5, .5); 
    for(int i=0;i<window::getWidth();i+=window::getStepX()){
        glVertex2f(i,0);
        glVertex2f(i,window::getHeight());
        
    }  
    for(int i=0;i<window::getHeight();i+=window::getStepY()){
        glVertex2f(0,i);
        glVertex2f(window::getWidth(),i);
        
    } 

    glEnd();
    
    glColor3f(.1, .1, 0); 
    for(int i=0;i<window::Area.size();++i){
        for(int j=0;j<window::Area[i].size();++j){
            if(window::Area[i][j]){
                glBegin(GL_QUADS);
                glVertex2f((i)*window::getStepX(),(j)*window::getStepY());
                glVertex2f((i+1)*window::getStepX(),(j)*window::getStepY());
                glVertex2f((i+1)*window::getStepX(),(j+1)*window::getStepY());//(4,5)
                glVertex2f((i)*window::getStepX(),(j+1)*window::getStepY());
                glEnd();
            }
        }
    }  
    
    glBegin(GL_QUADS);
    glColor3f(1, 0, 0);  
    glVertex2f((window::Ant.getX())*window::getStepX(),(window::Ant.getY())*window::getStepY());
    glVertex2f((window::Ant.getX()+1)*window::getStepX(),(window::Ant.getY())*window::getStepY());
    glVertex2f((window::Ant.getX()+1)*window::getStepX(),(window::Ant.getY()+1)*window::getStepY());
    glVertex2f((window::Ant.getX())*window::getStepX(),(window::Ant.getY()+1)*window::getStepY());
    glEnd();
    
    
  glPushMatrix();
  glLineWidth(1.5f);
  glTranslatef(window::getWidth()*0.8,window::getHeight()*0.9, 0);
  glScalef(0.15f, 0.15f, 1.0f);
  glColor3f(1, 0, 0); 
  draw_string(GLUT_STROKE_ROMAN, "Iteration:  ");
  char tmp[10];
  sprintf(tmp, "%d", window::Ant.getIter());
  draw_string(GLUT_STROKE_ROMAN, tmp );
  glPopMatrix();
  glPushMatrix();
  glLineWidth(1.5f);
  glTranslatef(window::getWidth()*0.8,window::getHeight()*0.88, 0);
  glScalef(0.15f, 0.15f, 1.0f);
  glColor3f(1, 0, 0);
  draw_string(GLUT_STROKE_ROMAN, "Orientation:  ");
   switch(window::Ant.getOrient()){
        case 0:draw_string(GLUT_STROKE_ROMAN, "UP");break;
        case 90: draw_string(GLUT_STROKE_ROMAN, "LEFT");break;
        case 180: draw_string(GLUT_STROKE_ROMAN, "DOWN");break;      
        case 270: draw_string(GLUT_STROKE_ROMAN, "RIGHT");break; 
    }
  glPopMatrix();
    
    glFlush();
    glutSwapBuffers();
    
   
    
}

void draw_string(void *font, const char* string){
  while (*string)
    glutStrokeCharacter(font, *string++);
}