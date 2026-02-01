#include "globals.h"

Connection::Connection(){
this->ref=0;
this->id=0;
}


Connection::Connection(int id){
this->ref=id;
this->id=globals.nodes.size();
}


GLOBALS::GLOBALS(){
this->nodeInteractionMode=0;
this->targetNode=-1;
this->multilineTextEditMode=0;
this->xDrag=0;
this->yDrag=0;
this->colorSelect.push_back(ColorOption(0));
this->colorSelect.push_back(ColorOption(1));
};


void GLOBALS::reset(){
globals.nodes.clear();
Node::nodeIDCounter=0;
globals.nodeInteractionMode=0;
globals.targetNode=-1;
globals.multilineTextEditMode=0;
}


void GLOBALS::setTitleFilename(){
QString title="MindMerp - ";
unsigned int i=globals.filename.length()-1;

    while(i>4 && globals.filename[i]!='/')
    i--;


    if(i>4){
    i++;

        for(; i<globals.filename.length(); i++)
        title+=globals.filename[i];

    this->mainWnd->setWindowTitle(title);
    }

}


bool GLOBALS::identifyNodeConnection(Connection& connection){

    for(unsigned int i=0; i<this->nodes.size(); i++){
    Node& node=this->nodes[i];

        if(connection.ref==node.id){
        connection.id=i;
        return 1;
        }

    }

return 0;
}


void GLOBALS::setConnections(Node& target){

    for(unsigned int i=0; i<target.connections.size(); i++){
    Connection& connection=target.connections[i];
    bool found=this->identifyNodeConnection(connection);

        if(!found){
        target.connections.erase(target.connections.begin()+i);
        i--;
        }

    }

}


void GLOBALS::connectAllNodes(){

    for(unsigned int i=0; i<this->nodes.size(); i++){
    this->setConnections(this->nodes[i]);
    }

}


void GLOBALS::drawConnections(QPainter& painter, Node& node){

    for(unsigned int i=0; i<node.connections.size(); i++){
    Node& conn=this->nodes[node.connections[i].id];
    painter.drawLine(node.x+(node.width/2), node.y+(node.height/2), conn.x+(conn.width/2), conn.y+(conn.height/2));
    }

}


Node* GLOBALS::getNodeById(int id){

    for(unsigned int i=0; i<this->nodes.size(); i++){

        if(id==this->nodes[i].id)
        return &this->nodes[i];

    }

return NULL;
}


Node* GLOBALS::getLastNode(){
return &(this->nodes[this->nodes.size()-1]);
}


Node* GLOBALS::getTargetNode(){
return &(this->nodes[this->targetNode]);
}


void GLOBALS::markConnectionsForDeletion(Node& node, Node& target, vector<int>& nodeIDs){

    for(unsigned int i=0; i<node.connections.size(); i++){
    Connection& connection=node.connections[i];

        if(this->nodes[connection.id].id!=target.parentID){
        nodeIDs.push_back(connection.id);
        this->nodes[connection.id].markForDeletion=1;
        }

    }

}


void GLOBALS::deleteBranch(Node& target){
vector<int> nodeIDs;
target.markForDeletion=1;

    for(unsigned int i=0; i<this->nodes.size(); i++){
    Node& node=this->nodes[i];

        if(node.id==target.id)
        nodeIDs.push_back(i);

    }

    while(nodeIDs.size()>0){
    this->markConnectionsForDeletion(this->nodes[nodeIDs[0]], target, nodeIDs);
    nodeIDs.erase(nodeIDs.begin());
    }

    for(unsigned int i=0; i<this->nodes.size(); i++){
    Node& node=this->nodes[i];

        if(node.markForDeletion){
        this->nodes.erase(this->nodes.begin()+i--);
        }

    }

this->connectAllNodes();
}


