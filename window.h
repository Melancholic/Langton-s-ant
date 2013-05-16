#ifndef WINDOW_H
#define	WINDOW_H
#include"ant.h"
#include<vector>
#include <utility>
#include"parser.h"
class window {
    static int Width;
    static int Height;
    static double StepX;
    static double StepY;
    static int Speed;
    static std::vector< std::vector<bool> > Area;
    static ant Ant;
    static int Boxes;
    static void setAreaFalse();
    static void setAreaPoint(std::vector< std::pair<int,int>  > point);
public:
    static void init(int w, int h, int b,int s, parser &P );
    static void draw();
    static int getHeight();
    static int getWidth();
    static double getStepX();
    static double getStepY();
    static std::vector< std::vector<bool> > getArea();
    static void process(int a);
    static int getCenter();
    friend void Values();
    friend void draw_string(void *font, const char* string);
};

void draw_string(void *font, const char* string); 
#endif	/* WINDOW_H */

