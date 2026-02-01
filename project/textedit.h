#ifndef TEXTEDIT_H
#define TEXTEDIT_H 1
#include <QTextEdit>
#include <QKeyEvent>

class TextEdit : public QTextEdit{
Q_OBJECT
public:

    explicit TextEdit();
    void keyPressEvent(QKeyEvent* ev);
    virtual void finished();

};
#endif
