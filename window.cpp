#include <cstdlib>
#include "window.h"
#include <GL/glut.h>
#include<iostream>
#include<thread>
#include <stdio.h>
#include"parser.h"
#include <utility>

std::vector< std::vector<bool> > window::Area;
int window::Width;
int window::Height;
double window::StepX;
double window::StepY;
ant window::Ant;
int window::Boxes;
int window::Speed;


int window::getHeight(){
    return Height;
}
int window::getWidth(){
    return Width;
}

double window::getStepX(){
    return StepX;
}
double window::getStepY(){
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

void window::init(int w, int h, int b,int s, parser &P ){    
    Width=w;
    Height=h;
    Boxes=b;
    StepX=(double)Width/Boxes;
    StepY=(double)Height/Boxes;  
    if(P.getCfgStatus()){
        Ant=ant(P.getParAntStart());
    }else{
        std::cerr<<"\nSet default ant\n";
        Ant= ant();
    }

    if(s>=0 ||s<=10){
            window::Speed=1000-s*100;
    }else{
        std::cout<<"\nErr value speed - set default(10) ";
        window::Speed=0;
    }
    window::Area.resize(Boxes);
    for(int i=0;i!=window::Area.size();++i){
       window::Area[i].resize(Boxes);
    }
    if(P.getCfgStatus()){
        window::setAreaPoint(P.getPoints());
    }else{
        std::cerr<<"\nSet default point\n";
        window::setAreaFalse();
    }    
}

int window::getCenter(){
    return window::Boxes/2; 
}
void Values(){
    if((window::Ant.getX()>=0 && window::Ant.getX()<window::Boxes) && (window::Ant.getY()>=0 && window::Ant.getY()<window::Boxes)){
        if(window::Area[window::Ant.getX()][window::Ant.getY()]){
            window::Area[window::Ant.getX()][window::Ant.getY()]=!window::Area[window::Ant.getX()][window::Ant.getY()];
            window::Ant.toLeft();
        }else{
            window::Area[window::Ant.getX()][window::Ant.getY()]=!window::Area[window::Ant.getX()][window::Ant.getY()];      
            window::Ant.toRight(); 
        }	
    }else{  
        int AntX=window::Ant.getX();       
        if(AntX<0){
            window::Ant.setX(window::Boxes+AntX);
        } else if(AntX>=window::Boxes){
            window::Ant.setX(AntX-window::Boxes);
        }
        int AntY=window::Ant.getY();
        if(AntY<0){
            window::Ant.setY(window::Boxes+AntY);
        } else if(AntY>=window::Boxes){
            window::Ant.setY(AntY-window::Boxes);
        }

    }
}

void window::process(int a){
    glutPostRedisplay();
    std::thread ValTh(Values);
    ValTh.join();
   glutTimerFunc(window::Speed, window::process,1 );
}

void window::draw(){    
  glClear(GL_COLOR_BUFFER_BIT); 
  glLineWidth(1.0f);
  glColor3f(.5, .5, .5); 
  for(int i=0;i<=window::Boxes;++i){
      glBegin(GL_LINES);
      glVertex2f(i*window::getStepX(),0);
      glVertex2f(i*window::getStepX(),window::getHeight());
      glEnd();
      glBegin(GL_LINES);
      glVertex2f(0,i*window::getStepY());
      glVertex2f(window::getWidth(),i*window::getStepY());
      glEnd();
    } 
    glColor3f(.1, .1, 0); 
    for(int i=0;i<window::Area.size();++i){
        for(int j=0;j<window::Area[i].size();++j){
            if(window::Area[i][j]){
                glBegin(GL_QUADS);
                glVertex2f((i)*window::getStepX(),(j)*window::getStepY());
                glVertex2f((i+1)*window::getStepX(),(j)*window::getStepY());
                glVertex2f((i+1)*window::getStepX(),(j+1)*window::getStepY());
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
  
    glBegin(GL_QUADS);
    glColor3f(1, 1, 1);  
    glVertex2f(window::getWidth()*0.75,window::getHeight()*0.83);
    glVertex2f(window::getWidth()*0.75,window::getHeight()*0.93);
    glVertex2f(window::getWidth()*0.98,window::getHeight()*0.93);
    glVertex2f(window::getWidth()*0.98,window::getHeight()*0.83);
    glEnd();
    
  glPushMatrix();
  glLineWidth(window::Width/500);
  glTranslatef(window::getWidth()*0.78,window::getHeight()*0.9, 0);
  glScalef(0.15f, 0.15f, 1.0f);
  glColor3f(0, 0, 0); 
  draw_string(GLUT_STROKE_ROMAN, "Iteration:  ");
  char tmp[10];
  sprintf(tmp, "%d", window::Ant.getIter());
  draw_string(GLUT_STROKE_ROMAN, tmp );
  glPopMatrix();
  glPushMatrix();
  glLineWidth(window::Width/500);
  glTranslatef(window::getWidth()*0.78,window::getHeight()*0.85, 0);
  glScalef(0.15f, 0.15f, 1.0f);
  glColor3f(0, 0, 0);
  draw_string(GLUT_STROKE_ROMAN, "Orientation:  ");
   switch(window::Ant.getOrient()){
        case 0:draw_string(GLUT_STROKE_ROMAN, "RIGHT");break;
        case 90: draw_string(GLUT_STROKE_ROMAN, "UP");break;
        case 180: draw_string(GLUT_STROKE_ROMAN, "LEFT");break;      
        case 270: draw_string(GLUT_STROKE_ROMAN, "DOWN");break; 
    }
  glPopMatrix();
    
    glFlush();
    glutSwapBuffers();
    
   
    
}

void draw_string(void *font, const char* string){
  while (*string)
    glutStrokeCharacter(font, *string++);
}

void window::setAreaPoint(std::vector< std::pair<int,int>  > point){
    window::setAreaFalse();
    for(int i=0;i<point.size();++i){
        if (point[i].first < Area.size() && point[i].second < Area.size()){
            Area[point[i].first][ point[i].second]=true;
        }
    }
}
