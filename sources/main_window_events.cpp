#include "globals.h"


bool MainWindowEvents::mouseOverMenu[2]={0, 0};


MainWindowEvents::MainWindowEvents(){

}


void MainWindowEvents::leftMouseDown(HWND hwnd, short x, short y){
short wd=hwnd->geometry().width()/2;
MainWindowEvents::mouseOverMenu[0]=0;
MainWindowEvents::mouseOverMenu[1]=0;
hwnd->update();

    if(x>10 && x<30 && y>5 && y<22)
    this->openFileMenu(hwnd);

    else if(x>45 && x<75 && y>5 && y<22)
    this->openInfoMenu(hwnd);

    else if(x>wd-25 && x<wd && y>0 && y<25)
    this->showNodeColorSelect(hwnd);

    else if(x>wd && x<wd+25 && y>0 && y<25)
    this->showTextColorSelect(hwnd);

}


void MainWindowEvents::mouseMove(HWND hwnd, short x, short y){
this->menuHover(hwnd, x, y);
}


void MainWindowEvents::keyDown(int key){

    if(globals.nodeInteractionMode==5 && key==83)
    this->saveViaCtrlS();

    if(key==16777249)
    this->enterNodeDeletionMode();

}


void MainWindowEvents::keyUp(int key){

    if(key==16777249)
    this->leaveNodeDeletionMode();

}


void MainWindowEvents::paint(HWND hwnd){
QPainter painter;
painter.begin(hwnd);
this->drawBackground(hwnd, painter);
this->drawMenu(painter);
this->drawNodeColorButton(hwnd, painter);
this->drawTextColorButton(hwnd, painter);
painter.end();
}


void MainWindowEvents::resize(HWND hwnd){
QRect r=hwnd->geometry();
this->fixChildWindowDimensions(r);
}




void MainWindowEvents::menuHover(HWND hwnd, short x, short y){
bool hitTest[2]={(x>10 && x<30 && y>5 && y<22),
                 (x>45 && x<75 && y>5 && y<22)};

    for(unsigned int i=0; i<2; i++){

        if(hitTest[i])
        MainWindowEvents::mouseOverMenu[i]=1;
        else
        MainWindowEvents::mouseOverMenu[i]=0;

    }

hwnd->update();
}


void MainWindowEvents::openFileMenu(HWND hwnd){
FileMenu fileMenu;
fileMenu.openFileMenu(hwnd);
}


void MainWindowEvents::openInfoMenu(HWND hwnd){
InfoMenu infoMenu;
infoMenu.openInfoMenu(hwnd);
}


void MainWindowEvents::drawBackground(HWND hwnd, QPainter& painter){
painter.fillRect(QRect(0, 0, hwnd->geometry().width(), 25), QColor(200, 200, 200));
}


void MainWindowEvents::drawNodeColorButton(HWND hwnd, QPainter& painter){
globals.colorSelect[0].draw(painter, (hwnd->width()/2)-25, 0);
}


void MainWindowEvents::drawTextColorButton(HWND hwnd, QPainter& painter){
globals.colorSelect[1].draw(painter, (hwnd->width()/2), 0);
}


void MainWindowEvents::drawMenu(QPainter& painter){
QString menus[2]={"File", "Info"};
QRect textbnd[2]={QRect(10, 5, 75, 25), QRect(45, 5, 75, 25)};

    for(unsigned int i=0; i<2; i++){

        if(MainWindowEvents::mouseOverMenu[i])
        painter.setPen(QPen(QColor(255, 255, 255)));
        else
        painter.setPen(QPen(QColor(0, 0, 0)));

    painter.drawText(textbnd[i], menus[i]);
    }

}


void MainWindowEvents::enterNodeDeletionMode(){
globals.nodeInteractionMode=5;
}


void MainWindowEvents::leaveNodeDeletionMode(){
globals.nodeInteractionMode=0;
}


void MainWindowEvents::fixChildWindowDimensions(QRect& wndRect){
globals.canvasWnd->setGeometry(0, 25, wndRect.width(), wndRect.height());
}


void MainWindowEvents::showNodeColorSelect(HWND hwnd){
QRect g=hwnd->geometry();
globals.whichColorSelect=0;
globals.colorOptionWnd->setGeometry(g.left()+(g.width()/2)-100, g.top(), 100, 100);
globals.colorOptionWnd->show();
}


void MainWindowEvents::showTextColorSelect(HWND hwnd){
QRect g=hwnd->geometry();
globals.whichColorSelect=1;
globals.colorOptionWnd->setGeometry(g.left()+(g.width()/2), g.top(), 100, 100);
globals.colorOptionWnd->show();
}


void MainWindowEvents::saveViaCtrlS(){
FileMenu fileMenuOp;
fileMenuOp.save();
globals.nodeInteractionMode=0;
}

