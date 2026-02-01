#include <QScreen>
#include "globals.h"

MindMerp::MindMerp(int argc, char* argv[]){
bool tutorialMode=0;

    if(this->handleTerminalCommands(argc, argv[1], tutorialMode)){
    QApplication app(argc, argv);
    QScreen* screen=app.primaryScreen();
    this->createWindows();
    this->setWindowAttributes(screen);
    this->handleTerminalLoadFile(argc, argv[1], tutorialMode);
    globals.mainWnd->show();
    app.exec();
    }

}


void MindMerp::createWindows(){
Window* wnd=new Window(WndProc);
Window* canvas=new Window(CanvasProc);
Window* about=new Window(AboutDlgProc);
Window* colorOption=new Window(ColorOptionProc);
globals.textEdit=new TextEdit();
globals.mainWnd=wnd;
globals.canvasWnd=canvas;
globals.aboutWnd=about;
globals.colorOptionWnd=colorOption;
}


void MindMerp::setWindowAttributes(QScreen* screen){
globals.mainWnd->setGeometry(0, 0, screen->geometry().width(), screen->geometry().height());
globals.mainWnd->setWindowTitle("MindMerp");
globals.canvasWnd->setParent(globals.mainWnd);
globals.colorOptionWnd->setGeometry(0, 0, 100, 100);
globals.colorOptionWnd->setWindowFlags(Qt::Popup);
globals.aboutWnd->setWindowFlags((Qt::Dialog | Qt::WindowStaysOnTopHint) & ~Qt::WindowMaximizeButtonHint);
globals.aboutWnd->setFixedSize(360, 260);
globals.aboutWnd->setWindowTitle("About MindMerp");
globals.textEdit->setParent(globals.mainWnd);
globals.textEdit->setCurrentFont(QApplication::font());
globals.textEdit->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
globals.textEdit->hide();
QObject::connect(globals.textEdit, &QTextEdit::textChanged, [&](){this->textEditingModeSizeControl();});
}


void MindMerp::showMainWindow(){
globals.mainWnd->show();
globals.mainWnd->setFocus();
}


void MindMerp::textEditingModeSizeControl(){
QString text=globals.textEdit->toPlainText();
unsigned short width, height;
Node& node=globals.nodes[globals.targetNode];
QRect r=globals.textEdit->geometry();
node.calculateStringDimensions(text, &width, &height);
globals.textEdit->setGeometry(r.left(), r.top(), r.width(), height);
node.resize(node.width, height+30);
globals.canvasWnd->update();
}


void MindMerp::tutorialMode(FileMenu& fileMenuOp){
FileIO getUsername;
string path="/home/";
getUsername.readProc("id -un");
path+=getUsername.output;

    if(path[path.length()-1]=='\n')
    path.erase(path.begin()+path.length()-1);

path+="/.local/share/mindmerp/guidedtour.mmf";
fileMenuOp.loadMap(path.c_str());
}


void MindMerp::handleTerminalLoadFile(int argc, char* cmd, bool& tutorialMode){
FileMenu fileMenuOp;
globals.filename=cmd;

    if(argc<2)
    return;

    if(!tutorialMode)
    fileMenuOp.loadMap(cmd);

    else
    this->tutorialMode(fileMenuOp);

}


bool MindMerp::handleTerminalCommands(int argc, char* cmd, bool& tutorialMode){

    if(argc>1){

        if(!strcmp(cmd, "--help"))
        return this->displayMindMerpHelp();

        else if(!strcmp(cmd, "--version"))
        return this->displayMindMerpVersion();

        else if(!strcmp(cmd, "--license"))
        return this->displayMindMerpLicense();

        else if(!strcmp(cmd, "--tour"))
        tutorialMode=1;

    }

return 1;
}


bool MindMerp::displayMindMerpHelp(){
cout<<"MindMerp user manual."<<endl<<endl;
cout<<"=============================================="<<endl;
cout<<"mindmerp --help: of course shows this manual."<<endl;
cout<<"mindmerp --version: shows the version of MindMerp."<<endl;
cout<<"mindmerp --license: shows the license for MindMerp"<<endl;
cout<<"mindmerp --tour: will take you on a guided tour of MindMerp's functionality and how to use it (works when installed)"<<endl;
cout<<"mindmerp <file>: will load the specified (.mmf) file."<<endl;
cout<<"=============================================="<<endl<<endl;
cout<<"Double click on an empty part of the canvas to create a node."<<endl<<endl;
cout<<"Double click on a node to edit its text."<<endl<<endl;
cout<<"While editing a node's text, pressing the Enter key will exit text editing mode."<<endl<<endl;
cout<<"While editing a node's text, if you press the Alt key you can switch on/off multiline editing mode."<<endl<<endl;
cout<<"Holding the left mouse button down over a node will allow you to move the node around the canvas area."<<endl<<endl;
cout<<"Holding the right mouse button down over a node will allow you to create a child-node and place it wherever you want in the canvas area."<<endl<<endl;
cout<<"Holding the right mouse button down on an empty area of the canvas will allow you to drag the canvas around giving you more room to work with."<<endl<<endl;
cout<<"Holding the Ctrl key and clicking on a node will delete the node and all nodes connected to it except its parent node."<<endl<<endl;
cout<<"Ctrl+S saves the mind map to a file"<<endl<<endl;
cout<<"You'll notice two different colored squares at the top of the window in the middle of the menu bar, if you click the one on the left you can change"<<endl;
cout<<"the background color of your nodes, the one on the right changes the text color. After selecting colors the changes will take place the next time you"<<endl;
cout<<"create a node or drag out a child node"<<endl<<endl;
cout<<"When you click to change colors a small window will pop up, it'll be a palette with 4 colors to choose from, you click one of the colors to set the associated"<<endl;
cout<<"color, if you right click any of them it will open up the system color picker dialog, and you'll be able to set the associated color within the palette and it'll be"<<endl;
cout<<"automatically selected"<<endl;
return 0;
}


bool MindMerp::displayMindMerpVersion(){
cout<<"MindMerp version: 0.5 beta"<<endl;
return 0;
}


bool MindMerp::displayMindMerpLicense(){
cout<<"MindMerp license: GPL3"<<endl;
return 0;
}
