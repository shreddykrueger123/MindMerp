#ifndef GLOBALS_H
#define GLOBALS_H 1
#include <iostream>
#include <QApplication>
#include <QMenu>
#include "window.h"
#include "textedit.h"

using namespace std;

#define PI 3.1415926535898
#define addMenuItem(menu, title, func) QAction::connect(menu->addAction(title), &QAction::triggered, [&](){func;});


class Point{
public:

    Point();
    Point(unsigned short x, unsigned short y);
    unsigned int toPosition(unsigned short width);
    void toCoordinate(unsigned int p, unsigned short width);
    unsigned int x;
    unsigned int y;

};


class Rect{
public:

    Rect();
    Rect(int x, int y, int w, int h);
    bool hitTest(const Point& pt);

    int x;
    int y;
    int width;
    int height;

};


class Color{
public:

    Color();
    Color(uchar r, uchar g, uchar b, uchar a=255);
    Color(const QColor& color);
    QColor toQColor();
    QString toHTML();

    uchar r;
    uchar g;
    uchar b;
    uchar a;

};


class Image{
public:

    Image();
    Image(unsigned short width, unsigned short height);
    void setImageSize(unsigned short width, unsigned short height);
    void fillImage(uchar r, uchar g, uchar b, uchar a=255);
    bool ptInRange(unsigned short x, unsigned short y);
    void setPixel(unsigned short x, unsigned short y, uchar r, uchar g, uchar b, uchar a=255);
    QColor getPixel(unsigned short x, unsigned short y);
    void drawLine(unsigned short x, unsigned short y, unsigned short X, unsigned short Y, uchar r, uchar g, uchar b, uchar a=255);
    void drawArc(unsigned short x, unsigned short y, unsigned short type, uchar r, uchar g, uchar b, uchar a=255);
    void fillArea(unsigned short x, unsigned short y, uchar r, uchar g, uchar b, uchar a=255);
    void draw(QPainter& painter, int x, int y);

    int x;
    int y;
    unsigned short width;
    unsigned short height;
    QByteArray pixels;

private:

    void gatherFillPoints(Point& pt, vector<Point>& pts, QColor& target, uchar r, uchar g, uchar b, uchar a);

};


class Connection{
public:
    Connection();
    Connection(int id);


int ref;
int id;
};


class Node: public Image{
public:

    Node(Color color=Color(155, 155, 155, 255));
    bool hitTest(const Point& pt);
    void drawFrame(const Color& color);
    void resize(unsigned short width, unsigned short height);
    void calculateStringDimensions(QString& str, unsigned short* width, unsigned short* height);
    void drawString(QPainter& painter, QString& str);
    bool isVisible(Node& node, QRect& wr);
    void drawNode(QPainter& painter, int x, int y, QRect& wr);

    static int nodeIDCounter;
    vector<Connection> connections;
    QString str;
    Color color;
    Color textColor;
    int id;
    int parentID;
    bool markForDeletion;

};


class PopupMenu{
public:

    PopupMenu();
    void setParent(HWND hwnd);
    void setPosition(short x, short y);
    void open();

    HWND parent;
    QMenu* menu;

};


class FileIO{
public:

    FileIO();
    bool readProc(const char* progName);
    bool getUser();
    off_t filesize(const char* filename);
    bool readfile(const char* filename, bool mode);
    bool writefile(const char* filename, const char* data, off_t size, bool mode);
    bool writefile(const char* filename, const string& data);
    bool open(const char* filename, bool mode);
    FileIO operator[](char* v);
    FileIO operator[](char v);
    FileIO operator[](short* v);
    FileIO operator[](short v);
    FileIO operator[](int* v);
    FileIO operator[](int v);
    FileIO operator[](float* v);
    FileIO operator[](float v);
    FileIO operator()(string& v, size_t size);
    FileIO operator[](const string& v);
    void close();
    bool listFiles(const char* path, vector<string>& files, vector<string>& folders);

    FILE* file;
    bool filemode;
    string output;
    string error;
    const bool read=0;
    const bool write=1;

private:

    int dummyRes;
};


class ColorOption{
public:

    ColorOption(bool id);
    void setPixelsToSelectedColor();
    void draw(QPainter& painter, short x, short y);

    Image img;
    Color palette[4];
    short selectedColor;
    bool id;

};


class FileMenu{
public:

    FileMenu();
    void openFileMenu(HWND hwnd);
    void setSaveFilename();
    bool validateSaveFilename();
    void saveNode(FileIO& file, Node& node);
    void loadNode(FileIO& file, Node& node);
    void saveMap(const char* filename);
    void loadMap(const char* filename);
    void newMap();
    void open();
    void save();
    void saveAs();
    void exit();

};

class InfoMenu{
public:

    InfoMenu();
    void openInfoMenu(HWND hwnd);
    void about();

};


class MindMerp{
public:

    MindMerp(int argc, char* argv[]);
    bool handleTerminalCommands(int argc, char* cmd, bool& tutorialMode);
    void handleTerminalLoadFile(int argc, char* cmd, bool& tutorialMode);
    void createWindows();
    void setWindowAttributes(QScreen* screen);
    void showMainWindow();
    void tutorialMode(FileMenu& fileMenuOp);
    bool displayMindMerpHelp();
    bool displayMindMerpVersion();
    bool displayMindMerpLicense();
    void textEditingModeSizeControl();

};


class GLOBALS{
public:

    GLOBALS();
    void reset();
    void setTitleFilename();
    Node* getNodeById(int id);
    Node* getLastNode();
    Node* getTargetNode();
    bool identifyNodeConnection(Connection& connection);
    void setConnections(Node& target);
    void connectAllNodes();
    void markConnectionsForDeletion(Node& node, Node& target, vector<int>& nodeIDs);
    void deleteBranch(Node& target);
    void drawConnections(QPainter& painter, Node& node);

    PopupMenu file;
    PopupMenu info;
    QString filename;
    TextEdit* textEdit;
    Window* mainWnd;
    Window* canvasWnd;
    Window* aboutWnd;
    Window* colorOptionWnd;
    vector<Node> nodes;
    vector<ColorOption> colorSelect;
    bool whichColorSelect;
    unsigned short nodeInteractionMode;
    bool multilineTextEditMode;
    int targetNode;
    short xDrag;
    short yDrag;


};


class MainWindowEvents{
public:

    MainWindowEvents();
    void leftMouseDown(HWND hwnd, short x, short y);
    void mouseMove(HWND hwnd, short x, short y);
    void keyDown(int key);
    void keyUp(int key);
    void paint(HWND hwnd);
    void resize(HWND hwnd);

    void menuHover(HWND hwnd, short x, short y);
    void openFileMenu(HWND hwnd);
    void openInfoMenu(HWND hwnd);
    void drawBackground(HWND hwnd, QPainter& painter);
    void drawMenu(QPainter& painter);
    void drawNodeColorButton(HWND hwnd, QPainter& painter);
    void drawTextColorButton(HWND hwnd, QPainter& painter);
    void enterNodeDeletionMode();
    void leaveNodeDeletionMode();
    void fixChildWindowDimensions(QRect& wndRect);
    void showNodeColorSelect(HWND hwnd);
    void showTextColorSelect(HWND hwnd);
    void saveViaCtrlS();

    static bool mouseOverMenu[2];

};


class AboutDialogEvents{
public:

    AboutDialogEvents();
    void leftMouseDown(HWND hwnd, short x, short y);
    void mouseMove(HWND hwnd, short x, short y);
    void leftMouseUp(HWND hwnd, short x, short y);
    void paint(HWND hwnd);

    void drawText(QPainter& painter);
    void drawOkButton(QPainter& painter, char okbtnState);
    void okButtonClicked(HWND hwnd);

    static char okbtnEffect;
};


class ClrOptionWindowEvents{
public:

    ClrOptionWindowEvents();
    void leftMouseDown(HWND hwnd, short x, short y);
    void rightMouseDown(HWND hwnd, short x, short y);
    void paint(HWND hwnd);
    void selectColor(short x, short y);
    void openSystemColorPickerDialog(short x, short y);

};

class CanvasEvents{
public:

        CanvasEvents();

        void leftMouseDown(short x, short y);
        void rightMouseDown(short x, short y);
        void doubleClick(HWND hwnd, short x, short y);
        void mouseMove(HWND hwnd, short x, short y);
        void leftMouseUp(HWND hwnd, short x, short y);
        void rightMouseUp();
        void paint(HWND hwnd);

        void createNode(HWND hwnd, short x, short y);
        bool createChildNode(short x, short y);
        void positioningChildNode(HWND hwnd, short x, short y);
        bool editNodeText(short x, short y);
        bool isDeleteMode();
        void deleteBranch(HWND hwnd, short x, short y);
        void beginMovingNode(short x, short y);
        void beginMoveCanvas(short x, short y);
        void moveNode(HWND hwnd, short x, short y);
        void moveCanvas(HWND hwnd, short x, short y);
        void drawNodes(QPainter& painter, QRect& windowRect);

};




#endif

//main.cpp
extern GLOBALS globals;
extern LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

//canvas.cpp
extern LRESULT CALLBACK CanvasProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

//aboutdlg.cpp
extern LRESULT CALLBACK AboutDlgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

//clroptionproc.cpp
extern LRESULT CALLBACK ColorOptionProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

