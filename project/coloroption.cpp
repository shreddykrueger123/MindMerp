#include "globals.h"

ColorOption::ColorOption(bool id){

    if(id==0){
    this->selectedColor=0;
    this->palette[0]=Color(155, 155, 155, 255);
    this->palette[1]=Color(255, 255, 255, 255);
    this->palette[2]=Color(255, 255, 0, 255);
    this->palette[3]=Color(0, 255, 255, 255);
    this->img.setImageSize(25, 25);
    }
    else{
    this->selectedColor=0;
    this->palette[0]=Color(0, 0, 0, 255);
    this->palette[1]=Color(255, 255, 255, 255);
    this->palette[2]=Color(255, 0, 0, 255);
    this->palette[3]=Color(0, 255, 255, 255);
    this->img.setImageSize(25, 25);
    }

this->setPixelsToSelectedColor();
this->id=id;
}


void ColorOption::setPixelsToSelectedColor(){
Color c=this->palette[this->selectedColor];
this->img.fillImage(c.r, c.g, c.b, c.a);
this->img.drawLine(0, 0, 24, 0, 0, 0, 0);
this->img.drawLine(24, 0, 24, 24, 0, 0, 0);
this->img.drawLine(24, 24, 0, 24, 0, 0, 0);
this->img.drawLine(0, 24, 0, 0, 0, 0, 0);
}


void ColorOption::draw(QPainter& painter, short x, short y){
this->img.draw(painter, x, y);
}
