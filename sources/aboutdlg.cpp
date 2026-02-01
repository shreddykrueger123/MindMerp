#include "globals.h"


LRESULT CALLBACK AboutDlgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam){
AboutDialogEvents events;

    switch(msg){

        case WM_PAINT: events.paint(hwnd); break;

        case WM_MOUSEMOVE: events.mouseMove(hwnd, LOWORD(lParam), HIWORD(lParam)); break;

        case WM_LBUTTONDOWN: events.leftMouseDown(hwnd, LOWORD(lParam), HIWORD(lParam)); break;

        case WM_LBUTTONUP: events.leftMouseUp(hwnd, LOWORD(lParam), HIWORD(lParam)); break;

    }

return 0;
}
