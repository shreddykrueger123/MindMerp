#include "globals.h"


CanvasEvents::CanvasEvents(){}


void CanvasEvents::leftMouseDown(short x, short y){
this->beginMovingNode(x, y);
}


void CanvasEvents::rightMouseDown(short x, short y){

    if(!this->createChildNode(x, y))
    this->beginMoveCanvas(x, y);

}


void CanvasEvents::doubleClick(HWND hwnd, short x, short y){

    if(!this->editNodeText(x, y))
    this->createNode(hwnd, x, y);

}


void CanvasEvents::mouseMove(HWND hwnd, short x, short y){

    switch(globals.nodeInteractionMode){

        case 1: this->positioningChildNode(hwnd, x, y); break;

        case 2: this->moveNode(hwnd, x, y); break;

        case 3: this->moveCanvas(hwnd, x, y); break;

    }

}


void CanvasEvents::leftMouseUp(HWND hwnd, short x, short y){

    if(this->isDeleteMode()){
    this->deleteBranch(hwnd, x, y);
    return;
    }

globals.nodeInteractionMode=0;
}


void CanvasEvents::rightMouseUp(){
globals.nodeInteractionMode=0;
}


void CanvasEvents::paint(HWND hwnd){
QRect wr=QRect(0, 0, hwnd->geometry().width(), hwnd->geometry().height());
QPainter painter;
painter.begin(hwnd);
painter.fillRect(wr, QBrush(QColor(42, 46, 50)));
this->drawNodes(painter, wr);
painter.end();
}





void CanvasEvents::createNode(HWND hwnd, short x, short y){
Node node(globals.colorSelect[0].palette[globals.colorSelect[0].selectedColor]);
node.x=x;
node.y=y;
globals.nodes.push_back(node);
hwnd->update();
}


bool CanvasEvents::createChildNode(short x, short y){

    if(globals.nodeInteractionMode>0)
    return 0;

    for(unsigned int i=0; i<globals.nodes.size(); i++){
    Node& node=globals.nodes[i];

        if(node.hitTest(Point(x, y))){
        Node newNode(globals.colorSelect[0].palette[globals.colorSelect[0].selectedColor]);
        Connection connection(newNode.id);
        globals.nodeInteractionMode=1;
        globals.xDrag=x-node.x;
        globals.yDrag=y-node.y;
        newNode.parentID=node.id;

            if(globals.yDrag>50)
            globals.yDrag=25;

        node.connections.push_back(connection);
        globals.nodes.push_back(newNode);
        globals.setConnections(globals.nodes[i]);
        return 1;
        }

    }

return 0;
}


void CanvasEvents::positioningChildNode(HWND hwnd, short x, short y){
Node* node=globals.getLastNode();
node->x=x-globals.xDrag;
node->y=y-globals.yDrag;
hwnd->update();
}


bool CanvasEvents::editNodeText(short x, short y){

    for(unsigned int i=0; i<globals.nodes.size(); i++){
    Node& node=globals.nodes[i];

        if(node.hitTest(Point(x, y))){
        QString css;
        css+="QTextEdit{background-color:";
        css+=node.color.toHTML();
        css+=";color:";
        css+=node.textColor.toHTML();
        css+=";border:none;}";
        globals.nodeInteractionMode=4;
        globals.targetNode=i;
        globals.textEdit->setGeometry(QRect(node.x+22, node.y+39, node.width-50, node.height-25));
        globals.textEdit->setPlainText(node.str);
        globals.textEdit->setStyleSheet(css);
        globals.textEdit->show();
        globals.textEdit->setFocus();
        return 1;
        }

    }

return 0;
}


void CanvasEvents::beginMovingNode(short x, short y){

    if(globals.nodeInteractionMode>0)
    return;

    for(unsigned int i=0; i<globals.nodes.size(); i++){
    Node& node=globals.nodes[i];

        if(node.hitTest(Point(x, y))){
        globals.nodeInteractionMode=2;
        globals.targetNode=i;
        globals.xDrag=x-node.x;
        globals.yDrag=y-node.y;
        return;
        }

    }

}


bool CanvasEvents::isDeleteMode(){

    if(globals.nodeInteractionMode==5)
    return 1;

return 0;
}


void CanvasEvents::deleteBranch(HWND hwnd, short x, short y){

    for(unsigned int i=0; i<globals.nodes.size(); i++){
    Node& node=globals.nodes[i];

        if(node.hitTest(Point(x, y))){
        globals.deleteBranch(node);
        hwnd->update();
        return;
        }

    }

}


void CanvasEvents::beginMoveCanvas(short x, short y){
globals.nodeInteractionMode=3;
globals.xDrag=x;
globals.yDrag=y;
}


void CanvasEvents::moveNode(HWND hwnd, short x, short y){
Node* node=globals.getTargetNode();
node->x=x-globals.xDrag;
node->y=y-globals.yDrag;
hwnd->update();
}


void CanvasEvents::moveCanvas(HWND hwnd, short x, short y){

    for(unsigned int i=0; i<globals.nodes.size(); i++){
    Node& node=globals.nodes[i];
    node.x+=x-globals.xDrag;
    node.y+=y-globals.yDrag;
    }

globals.xDrag=x;
globals.yDrag=y;
hwnd->update();
}


void CanvasEvents::drawNodes(QPainter& painter, QRect& windowRect){

    for(unsigned int i=0; i<globals.nodes.size(); i++){
    globals.drawConnections(painter, globals.nodes[i]);
    }

    for(unsigned int i=0; i<globals.nodes.size(); i++){
    Node& node=globals.nodes[i];
    node.drawNode(painter, node.x, node.y, windowRect);
    }

}
