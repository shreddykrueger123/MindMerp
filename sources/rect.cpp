#include "globals.h"

Rect::Rect(){
this->x=0;
this->y=0;
this->width=0;
this->height=0;
}


Rect::Rect(int x, int y, int width, int height){
this->x=x;
this->y=y;
this->width=width;
this->height=height;
}


bool Rect::hitTest(const Point& p){

    if((int)p.x>this->x && (int)p.x<=this->x+this->width && (int)p.y>this->y && (int)p.y<this->y+this->height)
    return 1;

return 0;
}
