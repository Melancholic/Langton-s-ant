#include <cstdlib>
#include<stdio.h>
#include"window.h"
#include<iostream>
ant::ant(){
    this->X=window::getCenter();
    this->Y=window::getCenter();
    this->Orientation=90; 
    this->Iteration=0;
}

void ant::toLeft(){
    switch(Orientation){
        case 0:X--;break;
        case 90: Y--; break;
        case 180: X++;break;
        case 270: Y++;break;
    }
   
    this->Orientation+=90;
    this->Iteration++;
    if(Orientation<0){
        Orientation+=360;
    }else{
        this->Orientation=this->Orientation%360;
    }
    
}

void ant::toRight(){
    switch(Orientation){
        case 0:X++;break;
        case 90: Y++; break;
        case 180: X--;break;
        case 270: Y--;break;
    }
    this->Orientation-=90;
    this->Iteration++; 
    if(Orientation<0){
        Orientation+=360;          
    }else{
        this->Orientation=this->Orientation%360;
        }
}

int ant::getX(){
    return this->X;
}
int ant::getY(){
    return this->Y;
}

int ant::getOrient(){
    return this->Orientation;
}

int ant::getIter(){
    return this->Iteration;
}