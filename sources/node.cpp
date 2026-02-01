#include "globals.h"


int Node::nodeIDCounter=0;

Node::Node(Color color){
this->color=color;
this->textColor=globals.colorSelect[1].palette[globals.colorSelect[1].selectedColor];
this->setImageSize(200, 50);
this->fillImage(0, 0, 0, 0);
this->drawFrame(color);
this->id=Node::nodeIDCounter++;
this->parentID=-1;
this->markForDeletion=0;
}


bool Node::hitTest(const Point& pt){

    if(Rect(this->x, this->y, this->width, this->height).hitTest(pt))
    return 1;

return 0;
}


void Node::drawFrame(const Color& color){
unsigned short width=this->width;
unsigned short height=this->height;
this->drawArc(25, 25, 0, 0, 0, 0);
this->drawArc(width-25, 25, 1, 0, 0, 0);
this->drawArc(width-25, height-25, 2, 0, 0, 0);
this->drawArc(25, height-25, 3, 0, 0, 0);
this->drawLine(25, 0, width-25, 0, 0, 0, 0);
this->drawLine(0, 25, 0, height-25, 0, 0, 0);
this->drawLine(25, height-1, width-25, height-1, 0, 0, 0);
this->drawLine(width-1, 25, width-1, height-25, 0, 0, 0);
this->fillArea(width/2, height/2, color.r, color.g, color.b, color.a);
}


void Node::resize(unsigned short width, unsigned short height){
this->setImageSize(width, height);
this->fillImage(0, 0, 0, 0);
this->drawFrame(this->color);
}


void Node::calculateStringDimensions(QString& str, unsigned short* width, unsigned short* height){
QFont font=QApplication::font();
QFontMetrics fm(font);
QRect nodeRect={0, 0, this->width-60, this->height};
QRect rect=fm.boundingRect(nodeRect, Qt::TextWordWrap, str);
*width=rect.width();
*height=rect.height();
}


void Node::drawString(QPainter& painter, QString& str){
QRect r=QRect(this->x+25, this->y+14, this->width-60, this->height);
painter.setPen(QColor(this->textColor.toQColor()));
painter.drawText(r, str);
}


bool Node::isVisible(Node& node, QRect& wr){

    if((node.x<0 && node.x+node.width<0) ||
        node.x>wr.width() ||
       (node.y<0 && node.y+node.height<0) ||
        node.y>wr.height()){
    return 0;
    }

return 1;
}


void Node::drawNode(QPainter& painter, int x, int y, QRect& wr){

    if(this->isVisible(*this, wr)){
    this->draw(painter, x, y);
    this->drawString(painter, this->str);
    }

}
