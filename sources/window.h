#ifndef WINDOW_H
#define WINDOW_H

//Yeah I subclassed my QWindow and made my basic Qt windowing library resemble win32 API.
//I'm sure you've noticed, or you thought it weird that I would do it this way.
//it's what I was used to so I stuck with it.

#include <QWidget>
#include <QPainter>

#define WM_CREATE 0
#define WM_LBUTTONDBLCLK 1
#define WM_MBUTTONDBLCLK 2
#define WM_RBUTTONDBLCLK 3
#define WM_LBUTTONDOWN 4
#define WM_LBUTTONUP 5
#define WM_MBUTTONDOWN 6
#define WM_MBUTTONUP 7
#define WM_RBUTTONDOWN 8
#define WM_RBUTTONUP 9
#define WM_MOUSEENTER 10
#define WM_MOUSELEAVE 11
#define WM_MOUSEMOVE 12
#define WM_WHEEL 13
#define WM_PAINT 14
#define WM_KEYUP 15
#define WM_KEYDOWN 16
#define WM_CLOSE 17
#define WM_DESTROY 17
#define WM_RESIZE 18
#define WM_TIMER 19

#define HWND QWidget*
#define UINT unsigned int
#define WPARAM long long
#define LPARAM long long
#define LRESULT long
#define CALLBACK

typedef unsigned short WORD;
typedef unsigned long DWORD;
typedef long LONG;

#define MAKELONG(a, b) ((LONG) (((WORD) (a)) | ((DWORD) ((WORD) (b))) << 16))
#define MAKELPARAM(a, b) MAKELONG(a, b)
#define MAKEWPARAM(a, b) MAKELONG(a, b) 
#define LOWORD(l) ((WORD) (l))
#define HIWORD(l) ((WORD) (((DWORD) (l) >> 16) & 0xFFFF))

#define SetTimer(timer, hwnd, id, time_out, procName){QObject::connect(timer, &QTimer::timeout, [&](){procName(hwnd, WM_TIMER, (WPARAM)timer, id);});timer->start(time_out);}
#define KillTimer(timer){timer->stop();delete timer;timer=0;}

typedef long (*WNDPROC)(QWidget*, UINT, WPARAM, LPARAM);

struct WIDGETPROP{
WPARAM id;
WPARAM userData;
WPARAM event;
};


class Window : public QWidget{
Q_OBJECT
public:
    explicit Window(WNDPROC, QWidget* parent=0, WIDGETPROP* widgetProps=NULL);
    WIDGETPROP props;
    WNDPROC proc;
    QPainter surface;
    QWidget* widgetRef;

    void wheelEvent(QWheelEvent*);
    void mouseDoubleClickEvent(QMouseEvent*);
    void mousePressEvent(QMouseEvent*);
    void mouseMoveEvent(QMouseEvent*);
    void mouseReleaseEvent(QMouseEvent*);
    void enterEvent(QEvent*);
    void leaveEvent(QEvent*);
    void keyPressEvent(QKeyEvent*);
    void keyReleaseEvent(QKeyEvent*);
    void paintEvent(QPaintEvent*);
    void closeEvent(QCloseEvent*);
    void resizeEvent(QResizeEvent*);
    void timerEvent(QTimerEvent*);
};

#endif
