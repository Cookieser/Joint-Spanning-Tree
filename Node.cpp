//
// Created by 32442 on 2022/12/21.
//

#include "Node.h"


void Node::printNeighbourNodes(){
    cout << "The NeighbourNodes of " << getID() << ": ";
    for (int i = 0; i < _neighbourNum; ++i) {

        cout << "\t" <<_NeighbourNodes[i].node << ":["<<_NeighbourNodes[i].weight << "]" <<":{"<<_NeighbourNodes[i].status << "}";
    }
    cout << endl;

}

void Node::setNeighbourNode(int node,int weight,int status){
    neighbourNodes neighbourNodes = {node,weight,status};

    _NeighbourNodes.push_back(neighbourNodes);

}

void Node::setStatus(int s){

    if(_status != s)
    {
        _status = s;
        cout << "The status of " << getID() << " is FINISHED now!" << endl;

    }else
    {
        cout<<"The status of "<< getID() <<" isn't changed" << endl;
    }

    }



void  Node::minWeightUnfinished(int &min,int &route){

    cout <<_id<<" starts to min process" <<endl;

    for (vector<neighbourNodes>::iterator it = _NeighbourNodes.begin();it !=_NeighbourNodes.end();it++) {
        if(((it->status)==0)&&(it->weight < min))
        {
            min = it->weight;
            route = it->node;

        }

    }

}

void Node::printAllStatusAround(){
    for (vector<neighbourNodes>::iterator it = _NeighbourNodes.begin();it !=_NeighbourNodes.end();it++){
       cout <<"For "<< _id <<" ,Neighbour id: "<<it->node<<"  status: " << it->status<<endl;
    }
}

void Node::updateStatusOfNeighbour(int id,int s){
    for (vector<neighbourNodes>::iterator it = _NeighbourNodes.begin();it !=_NeighbourNodes.end();it++) {

        if ((it->node) == id) {
            it->status = s;
            return;
        }

    }

 cout<<"Not found the neighbour in this node "<<endl;
}