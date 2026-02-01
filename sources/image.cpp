#include "globals.h"

Image::Image(){
this->x=0;
this->y=0;
this->width=0;
this->height=0;
}


Image::Image(unsigned short width, unsigned short height){
this->x=0;
this->y=0;
this->setImageSize(width, height);
}


void Image::setImageSize(unsigned short width, unsigned short height){
this->pixels.resize(width*height*4);
this->width=width;
this->height=height;
}


void Image::fillImage(uchar r, uchar g, uchar b, uchar a){
unsigned int end=this->width*this->height*4;

    for(unsigned int i=0; i<end;){
    this->pixels[i++]=b;
    this->pixels[i++]=g;
    this->pixels[i++]=r;
    this->pixels[i++]=a;
    }

}


bool Image::ptInRange(unsigned short x, unsigned short y){

    if(x<this->width && y<this->height)
    return 1;

return 0;
}


void Image::setPixel(unsigned short x, unsigned short y, uchar r, uchar g, uchar b, uchar a){
int p=(x+(this->width*y))*4;

    if(this->ptInRange(x, y)){
    this->pixels[p++]=b;
    this->pixels[p++]=g;
    this->pixels[p++]=r;
    this->pixels[p++]=a;
    }

}


QColor Image::getPixel(unsigned short x, unsigned short y){
int p=(x+(this->width*y))*4;

    if(this->ptInRange(x, y))
    return QColor(this->pixels[p+2], this->pixels[p+1], this->pixels[p], this->pixels[p+3]);

return QColor(0, 0, 0, 0);
}


void Image::drawLine(unsigned short x, unsigned short y, unsigned short X, unsigned short Y, uchar r, uchar g, uchar b, uchar a){
float rad=sqrt(pow(X-x, 2)+pow(Y-y, 2));
float angle=(-(atan2((X-x),(Y-y))*180/PI)+90);

        for(float i=0; i<rad; i++){
        this->setPixel((float)(x+cos(angle/180.0*PI)*i), (float)(y+sin(angle/180.0*PI)*i), r, g, b, a);
        }

}


void Image::drawArc(unsigned short x, unsigned short y, unsigned short type, uchar r, uchar g, uchar b, uchar a){
float rad=25;
float A=0.0, B=0.0;

    switch(type){

        case 0:{A=90.0; B=180.0;}break;
        case 1:{A=0.0; B=90.0;}break;
        case 2:{A=270.0; B=360.0;}break;
        case 3:{A=180.0; B=270.0;}break;

    }

    for(; A<=B; A++){
    this->setPixel(((float)x+cos(A/180*PI)*rad), ((float)y-sin(A/180*PI)*rad), r, g, b, a);
    }

}


void Image::gatherFillPoints(Point& pt, vector<Point>& pts, QColor& target, uchar r, uchar g, uchar b, uchar a){

    if(this->getPixel(pt.x-1, pt.y)==target){
    this->setPixel(pt.x-1, pt.y, r, g, b, a);
    pts.push_back(Point(pt.x-1, pt.y));
    }

    if(this->getPixel(pt.x+1, pt.y)==target){
    this->setPixel(pt.x+1, pt.y, r, g, b, a);
    pts.push_back(Point(pt.x+1, pt.y));
    }

    if(this->getPixel(pt.x, pt.y-1)==target){
    this->setPixel(pt.x, pt.y-1, r, g, b, a);
    pts.push_back(Point(pt.x, pt.y-1));
    }

    if(this->getPixel(pt.x, pt.y+1)==target){
    this->setPixel(pt.x, pt.y+1, r, g, b, a);
    pts.push_back(Point(pt.x, pt.y+1));
    }

}


void Image::fillArea(unsigned short x, unsigned short y, uchar r, uchar g, uchar b, uchar a){
QColor target=this->getPixel(x, y);
vector<Point> pts;
this->setPixel(x, y, r, g, b, a);
pts.push_back(Point(x, y));

    while(pts.size()>0){
    Point& pt=pts[0];

        if(this->ptInRange(pt.x, pt.y)){
        this->gatherFillPoints(pt, pts, target, r, g, b, a);
        }

    pts.erase(pts.begin());
    }

}


void Image::draw(QPainter& painter, int x, int y){
QImage img(reinterpret_cast<uchar*>(this->pixels.data()), this->width, this->height, QImage::Format_ARGB32);
this->x=x;
this->y=y;
painter.drawImage(x, y, img);
}
