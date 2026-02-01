#include <QFileDialog>
#include "globals.h"

InfoMenu::InfoMenu(){}

void InfoMenu::openInfoMenu(HWND hwnd){
globals.info.setParent(hwnd);
addMenuItem(globals.info.menu, "About", this->about());
globals.info.setPosition(45, 22);
globals.info.open();
}

void InfoMenu::about(){
QRect m=globals.mainWnd->geometry();
short x=m.left()+(m.width()/2)-180;
short y=m.top()+(m.height()/2)-130;
globals.aboutWnd->setGeometry(x, y, 360, 260);
globals.aboutWnd->show();
}
