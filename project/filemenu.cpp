#include <QFileDialog>
#include "globals.h"


FileMenu::FileMenu(){}


void FileMenu::openFileMenu(HWND hwnd){
globals.file.setParent(hwnd);
addMenuItem(globals.file.menu, "New", this->newMap());
addMenuItem(globals.file.menu, "Open", this->open());
addMenuItem(globals.file.menu, "Save", this->save());
addMenuItem(globals.file.menu, "Save As", this->saveAs());
addMenuItem(globals.file.menu, "Exit", this->exit());
globals.file.setPosition(10, 22);
globals.file.open();
}


bool FileMenu::validateSaveFilename(){
QString& filename=globals.filename;
unsigned int len=filename.length();

    if(filename.length()<=4)
    return 0;

    if(filename[len-4]!='.' && filename[len-3]!='k' && filename[len-2]!='m' && filename[len-1]!='m')
    return 0;

return 1;
}


void FileMenu::saveNode(FileIO& file, Node& node){
file[(int)node.x][(int)node.y][(int)node.width][(int)node.height][(int)node.id][(int)node.parentID][(int)node.connections.size()];

    if(node.connections.size()>0){

        for(unsigned int i=0; i<node.connections.size(); i++){
        file[(int)node.connections[i].ref][(int)node.connections[i].id];
        }

    }

file[(char)node.color.r][(char)node.color.g][(char)node.color.b][(char)node.color.a];
file[(char)node.textColor.r][(char)node.textColor.g][(char)node.textColor.b][(char)node.textColor.a];
file[(int)node.str.length()][node.str.toStdString()];
}


void FileMenu::saveMap(const char* filename){
FileIO file;

    if(file.open(filename, file.write)){
    globals.setTitleFilename();
    file[(char)1][(int)globals.nodes.size()];

        for(unsigned int i=0; i<globals.nodes.size(); i++){
        this->saveNode(file, globals.nodes[i]);
        }

    file[(int)Node::nodeIDCounter];
    file.close();
    }

}


void FileMenu::loadNode(FileIO& file, Node& node){
unsigned int connectionsCount;
unsigned int slen;
string str;

file[(int*)&node.x][(int*)&node.y][(int*)&node.width][(int*)&node.height][(int*)&node.id][(int*)&node.parentID][(int*)&connectionsCount];

    if(connectionsCount>0){

        for(unsigned int i=0; i<connectionsCount; i++){
        Connection connection;
        file[(int*)&connection.ref][(int*)&connection.id];
        node.connections.push_back(connection);
        }

    }

file[(char*)&node.color.r][(char*)&node.color.g][(char*)&node.color.b][(char*)&node.color.a];
file[(char*)&node.textColor.r][(char*)&node.textColor.g][(char*)&node.textColor.b][(char*)&node.textColor.a];
file[(int*)&slen](str, (int)slen);
node.str=str.c_str();
node.resize(node.width, node.height);
}




void FileMenu::loadMap(const char* filename){
FileIO file;

    if(file.open(filename, file.read)){
    unsigned int nodeCount;
    unsigned char version;
    globals.setTitleFilename();
    globals.reset();
    file[(char*)&version][(int*)&nodeCount];

        for(unsigned int i=0; i<nodeCount; i++){
        Node node;
        this->loadNode(file, node);
        globals.nodes.push_back(node);
        }

    file[(int*)&Node::nodeIDCounter];
    file.close();
    }

}


void FileMenu::newMap(){
Node::nodeIDCounter=0;
globals.nodeInteractionMode=0;
globals.targetNode=-1;
globals.multilineTextEditMode=0;
globals.nodes.clear();
globals.filename="";
globals.canvasWnd->update();
}


void FileMenu::open(){
QFileDialog qFileDlg(globals.mainWnd);
globals.filename=qFileDlg.getOpenFileName(globals.mainWnd, "Open mind map", "", "mindmerp files (*.mmf);;All Files (*)");
this->loadMap(globals.filename.toStdString().c_str());
globals.canvasWnd->update();
}


void FileMenu::setSaveFilename(){
QFileDialog qFileDlg(globals.mainWnd);
globals.filename=qFileDlg.getSaveFileName(globals.mainWnd, "Save mind map", "", "mindmerp files (*.mmf);;All Files (*)");

        if(!this->validateSaveFilename())
        globals.filename+=".mmf";

}


void FileMenu::save(){

    if(globals.filename.length()==0){
    this->setSaveFilename();
    }

this->saveMap(globals.filename.toStdString().c_str());
}


void FileMenu::saveAs(){
this->setSaveFilename();
this->saveMap(globals.filename.toStdString().c_str());
}


void FileMenu::exit(){
QApplication::quit();
}
