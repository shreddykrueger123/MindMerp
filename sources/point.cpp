#include "globals.h"

Point::Point(){
this->x=0;
this->y=0;
}


Point::Point(unsigned short x, unsigned short y){
this->x=x;
this->y=y;
}


unsigned int Point::toPosition(unsigned short width){
return ((this->y*width)+this->x)*4;
}


void Point::toCoordinate(unsigned int p, unsigned short width){
unsigned int P=p/4;

    if(P<width){
    this->x=P;
    this->y=0;
    }
    else{
    this->y=floor(P/width);
    this->x=P-(this->y*width);
    }

}
