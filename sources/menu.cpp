#include "globals.h"

PopupMenu::PopupMenu(){}


void PopupMenu::setParent(HWND hwnd){
this->menu=new QMenu();
this->parent=hwnd;
}


void PopupMenu::setPosition(short x, short y){
QRect p=this->parent->geometry();
QRect r=QRect(x+p.x(), y+p.y()+5, 100, 0);
this->menu->setGeometry(r);
}


void PopupMenu::open(){
this->menu->exec();
this->menu->clear();
}
