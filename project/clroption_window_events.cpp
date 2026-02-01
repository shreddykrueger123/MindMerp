#include <QColorDialog>
#include "globals.h"

ClrOptionWindowEvents::ClrOptionWindowEvents(){}


void ClrOptionWindowEvents::leftMouseDown(HWND hwnd, short x, short y){
this->selectColor(x, y);
hwnd->hide();
}

void ClrOptionWindowEvents::rightMouseDown(HWND hwnd, short x, short y){
this->openSystemColorPickerDialog(x, y);
hwnd->hide();
}

void ClrOptionWindowEvents::paint(HWND hwnd){
Color* colors=globals.colorSelect[globals.whichColorSelect].palette;
QPainter painter;
painter.begin(hwnd);
painter.fillRect(QRect(0, 0, 50, 50), QBrush(QColor(colors[0].toQColor())));
painter.fillRect(QRect(50, 0, 100, 50), QBrush(QColor(colors[1].toQColor())));
painter.fillRect(QRect(0, 50, 50, 100), QBrush(QColor(colors[2].toQColor())));
painter.fillRect(QRect(50, 50, 100, 100), QBrush(QColor(colors[3].toQColor())));
painter.setPen(QColor(0, 0, 0));
painter.drawRect(hwnd->geometry());
painter.end();
}






void ClrOptionWindowEvents::selectColor(short x, short y){
ColorOption& colorSelect=globals.colorSelect[globals.whichColorSelect];
bool quadrantHitTest[4]={(x>0 && x<50 && y>0 && y<50), (x>50 && x<100 && y>0 && y<50),
                         (x>0 && x<50 && y>50 && y<100), (x>50 && x<100 && y>50 && y<100)};

    for(unsigned int i=0; i<4; i++){

        if(quadrantHitTest[i])
        colorSelect.selectedColor=i;

    }

colorSelect.setPixelsToSelectedColor();
globals.mainWnd->update();
}


void ClrOptionWindowEvents::openSystemColorPickerDialog(short x, short y){
ColorOption& colorSelect=globals.colorSelect[globals.whichColorSelect];
bool quadrantHitTest[4]={(x>0 && x<50 && y>0 && y<50), (x>50 && x<100 && y>0 && y<50),
                         (x>0 && x<50 && y>50 && y<100), (x>50 && x<100 && y>50 && y<100)};

    for(unsigned int i=0; i<4; i++){

        if(quadrantHitTest[i])
        colorSelect.selectedColor=i;

    }

colorSelect.palette[colorSelect.selectedColor]=Color(QColor(QColorDialog::getColor(QColor(255, 255, 255), globals.mainWnd, "Select color")));
colorSelect.setPixelsToSelectedColor();
globals.mainWnd->update();
}
