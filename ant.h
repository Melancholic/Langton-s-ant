#ifndef ANT_H
#define	ANT_H
#include"parser.h"
class ant{
    int X;
    int Y;
    int Orientation;
    int Iteration;
public:
    ant();
    ant(par_ant_start start);
    void toLeft();
    void toRight();
    int getX();
    int getY();
    int getOrient();
    int getIter();
    void setX(int x);
    void setY(int y);
};


#endif	/* ANT_H */

