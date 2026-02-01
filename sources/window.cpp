#include <QMouseEvent>
#include <QWheelEvent>
#include <QEvent>
#include <QKeyEvent>
#include <QPaintEvent>
#include <QCloseEvent>
#include <QResizeEvent>
#include "window.h"


Window::Window(WNDPROC windowProcedure, QWidget* parent, WIDGETPROP* widgetProps) : QWidget(parent){
setMouseTracking(true);

	if(widgetProps!=NULL)
	this->props=*widgetProps;
	
this->proc=(WNDPROC)windowProcedure;
this->proc(this, WM_CREATE, (WPARAM)&this->props, 0);
this->widgetRef=parent;
}


void Window::wheelEvent(QWheelEvent* e){
this->proc(this, WM_WHEEL, (WPARAM)&this->props, 0);    
}


void Window::mouseDoubleClickEvent(QMouseEvent* e){
this->props.event=MAKELONG(e->globalX(), e->globalY());
	
    if(e->button()==Qt::LeftButton){
    this->proc(this, WM_LBUTTONDBLCLK, (WPARAM)&this->props, MAKELONG(e->x(), e->y()));    
    }
    else if(e->button()==Qt::MiddleButton){
    this->proc(this, WM_MBUTTONDBLCLK, (WPARAM)&this->props, MAKELONG(e->x(), e->y()));    
    }
    else if(e->button()==Qt::RightButton){
    this->proc(this, WM_RBUTTONDBLCLK, (WPARAM)&this->props, MAKELONG(e->x(), e->y()));    
    }
    
}


void Window::mousePressEvent(QMouseEvent* e){
this->props.event=MAKELONG(e->globalX(), e->globalY());
	
    if(e->button()==Qt::LeftButton){
    this->proc(this, WM_LBUTTONDOWN, (WPARAM)&this->props, MAKELONG(e->x(), e->y()));    
    }
    else if(e->button()==Qt::MiddleButton){
    this->proc(this, WM_MBUTTONDOWN, (WPARAM)&this->props, MAKELONG(e->x(), e->y()));    
    }
    else if(e->button()==Qt::RightButton){
    this->proc(this, WM_RBUTTONDOWN, (WPARAM)&this->props, MAKELONG(e->x(), e->y()));    
    }
    
}

 
void Window::mouseReleaseEvent(QMouseEvent* e){
this->props.event=MAKELONG(e->globalX(), e->globalY());
	
    if(e->button()==Qt::LeftButton){
    this->proc(this, WM_LBUTTONUP, (WPARAM)&this->props, MAKELONG(e->x(), e->y()));    
    }
    else if(e->button()==Qt::MiddleButton){
    this->proc(this, WM_MBUTTONUP, (WPARAM)&this->props, MAKELONG(e->x(), e->y()));    
    }
    else if(e->button()==Qt::RightButton){
    this->proc(this, WM_RBUTTONUP, (WPARAM)&this->props, MAKELONG(e->x(), e->y()));    
    }    

}


void Window::mouseMoveEvent(QMouseEvent* e){
this->props.event=MAKELONG(e->globalX(), e->globalY());
this->proc(this, WM_MOUSEMOVE, (WPARAM)&this->props, MAKELONG(e->x(), e->y()));    
}


void Window::enterEvent(QEvent* e){
this->proc(this, WM_MOUSEENTER, (WPARAM)&this->props, 0);    
}


void Window::leaveEvent(QEvent* e){
this->proc(this, WM_MOUSELEAVE, (WPARAM)&this->props, 0);   
}


void Window::keyPressEvent(QKeyEvent* e){
this->proc(this, WM_KEYDOWN, (WPARAM)&this->props, e->key());    
}


void Window::keyReleaseEvent(QKeyEvent* e){
this->proc(this, WM_KEYUP, (WPARAM)&this->props, e->key());
}


void Window::paintEvent(QPaintEvent* e){
this->proc(this, WM_PAINT, (WPARAM)&this->props, 0);  
}


void Window::closeEvent(QCloseEvent* e){
this->proc(this, WM_CLOSE, (WPARAM)&this->props, 0);   
}


void Window::resizeEvent(QResizeEvent* e){
this->proc(this, WM_RESIZE, (WPARAM)&this->props, MAKELONG(e->size().width(), e->size().height()));
}


void Window::timerEvent(QTimerEvent* e){
this->proc(this, WM_TIMER, (WPARAM)&this->props, 0);
}

