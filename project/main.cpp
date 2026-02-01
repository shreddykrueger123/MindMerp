//Prepare yourself for insane levels of OOPery.
#include "globals.h"

GLOBALS globals;


LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam){
MainWindowEvents events;

    switch(msg){

        case WM_PAINT: events.paint(hwnd); break;

        case WM_MOUSEMOVE: events.mouseMove(hwnd, LOWORD(lParam), HIWORD(lParam)); break;

        case WM_LBUTTONDOWN: events.leftMouseDown(hwnd, LOWORD(lParam), HIWORD(lParam)); break;

        case WM_KEYDOWN: events.keyDown(lParam); break;

        case WM_KEYUP: events.keyUp(lParam); break;

        case WM_RESIZE: events.resize(hwnd); break;

    }

return 0;
}

int main(int argc, char* argv[]){
MindMerp mindmerp(argc, argv);
return 0;
}


