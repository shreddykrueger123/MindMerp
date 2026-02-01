#include "globals.h"


char AboutDialogEvents::okbtnEffect=0;


AboutDialogEvents::AboutDialogEvents(){}


void AboutDialogEvents::leftMouseDown(HWND hwnd, short x, short y){

    if(x>135 && x<235 && y>200 && y<225){
    AboutDialogEvents::okbtnEffect=2;
    hwnd->update();
    }

}


void AboutDialogEvents::mouseMove(HWND hwnd, short x, short y){
char hoverState=AboutDialogEvents::okbtnEffect;

    if(AboutDialogEvents::okbtnEffect==2)
    return;

    if(x>135 && x<235 && y>200 && y<225)
    hoverState=1;

    else
    hoverState=0;

    if(hoverState!=AboutDialogEvents::okbtnEffect){
    AboutDialogEvents::okbtnEffect=hoverState;
    hwnd->update();
    }

}


void AboutDialogEvents::leftMouseUp(HWND hwnd, short x, short y){
AboutDialogEvents::okbtnEffect=0;
hwnd->update();

    if(x>135 && x<235 && y>200 && y<225)
    this->okButtonClicked(hwnd);

}


void AboutDialogEvents::paint(HWND hwnd){
char okbtnState;
QPainter painter;
painter.begin(hwnd);

    if(AboutDialogEvents::okbtnEffect==1)
    okbtnState=2;

    else if(AboutDialogEvents::okbtnEffect==2)
    okbtnState=4;

    else
    okbtnState=0;

this->drawText(painter);
this->drawOkButton(painter, okbtnState);
painter.end();
}


void AboutDialogEvents::drawText(QPainter& painter){
QRect textbnd={10, 10, 350, 175};
painter.drawText(textbnd, Qt::AlignCenter, "About MindMerp\n-------------------------\n\nThis software allows you to make mind maps.\n\nVersion: 0.5 beta\nDeveloped by: ShreddyKrueger\nJanuary 31, 2026\nDeveloped using Qt6\nLicense: GPL3");
}


void AboutDialogEvents::drawOkButton(QPainter& painter, char okbtnState){
QRect okbtn={135, 200, 100, 25};
QColor okbtnColors[6]={QColor(200, 200, 200), QColor(0, 0, 0),
                       QColor(255, 255, 255), QColor(0, 155, 255),
                       QColor(100, 100, 100), QColor(155, 155, 155)};

painter.fillRect(okbtn, QBrush(okbtnColors[(int)okbtnState]));
painter.setPen(QPen(okbtnColors[okbtnState+1]));
painter.drawText(okbtn, Qt::AlignCenter, "OK");
}


void AboutDialogEvents::okButtonClicked(HWND hwnd){
hwnd->hide();
}
