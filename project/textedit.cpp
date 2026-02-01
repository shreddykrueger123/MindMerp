#include "globals.h"

TextEdit::TextEdit() : QTextEdit(){}


void TextEdit::keyPressEvent(QKeyEvent* e){

    if(e->key()==16777220){

        if(!globals.multilineTextEditMode)
        this->finished();
        else
        QTextEdit::keyPressEvent(e);

    }
    else if(e->key()==16777251)
    globals.multilineTextEditMode=!globals.multilineTextEditMode;
    else
    QTextEdit::keyPressEvent(e);

}

void TextEdit::finished(){

    if(!globals.multilineTextEditMode){
    unsigned short width, height;
    Node* node=globals.getTargetNode();
    node->str=this->toPlainText();
    globals.multilineTextEditMode=0;
    this->hide();
    this->clear();
    node->calculateStringDimensions(node->str, &width, &height);
    node->resize(node->width, height+30);
    globals.mainWnd->setFocus();
    globals.canvasWnd->update();
    }

}
