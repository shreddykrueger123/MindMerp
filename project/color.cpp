#include "globals.h"

Color::Color(){
this->r=0;
this->g=0;
this->b=0;
this->a=0;
}

Color::Color(uchar r, uchar g, uchar b, uchar a){
this->r=r;
this->g=g;
this->b=b;
this->a=a;
}

Color::Color(const QColor& color){
this->r=color.red();
this->g=color.green();
this->b=color.blue();
this->a=color.alpha();
}

QColor Color::toQColor(){
return QColor(this->r, this->g, this->b, this->a);
}

QString Color::toHTML(){
QString html="rgb(";
html+=QString::number((unsigned int)this->r);
html+=", ";
html+=QString::number((unsigned int)this->g);
html+=", ";
html+=QString::number((unsigned int)this->b);
html+=")";
return html;
}
