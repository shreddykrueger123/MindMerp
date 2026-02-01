#include "globals.h"

LRESULT CALLBACK CanvasProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam){
CanvasEvents events;

    switch(msg){

        case WM_LBUTTONDOWN: events.leftMouseDown(LOWORD(lParam), HIWORD(lParam)); break;

        case WM_RBUTTONDOWN: events.rightMouseDown(LOWORD(lParam), HIWORD(lParam)); break;

        case WM_MOUSEMOVE: events.mouseMove(hwnd, LOWORD(lParam), HIWORD(lParam)); break;

        case WM_LBUTTONUP: events.leftMouseUp(hwnd, LOWORD(lParam), HIWORD(lParam)); break;

        case WM_RBUTTONUP: events.rightMouseUp(); break;

        case WM_LBUTTONDBLCLK: events.doubleClick(hwnd, LOWORD(lParam), HIWORD(lParam)); break;

        case WM_PAINT: events.paint(hwnd); break;

    }

return 0;
}
