#include "globals.h"

LRESULT CALLBACK ColorOptionProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam){
ClrOptionWindowEvents events;

    switch(msg){

        case WM_LBUTTONDOWN: events.leftMouseDown(hwnd, LOWORD(lParam), HIWORD(lParam)); break;

        case WM_RBUTTONDOWN: events.rightMouseDown(hwnd, LOWORD(lParam), HIWORD(lParam)); break;

        case WM_PAINT: events.paint(hwnd); break;

    }

return 0;
}
