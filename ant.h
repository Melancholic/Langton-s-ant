#ifndef ANT_H
#define	ANT_H
class ant{
    int X;
    int Y;
    int Orientation;
public:
    ant();
    void toLeft();
    void toRight();
    int getX();
    int getY();
    int getOrient();
    
};


#endif	/* ANT_H */

