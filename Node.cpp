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
    cout <<"Start to change the status of Node"<<_id<<endl;

    if(_status != s)
    {
        _status = s;
        cout << "The status of " << getID() << " is FINISHED now!" << endl;

    }else
    {
        cout<<"The status of "<< getID() <<" isn't changed" << endl;
    }
    cout<<endl;
    }


// 寻找除去同片段节点后某点的最小权重边
void  Node::minWeightUnfinished(int &min,int &route,vector<int> inFragment,int &extendNode){

    int st;


    cout<<"minWeightUnfinished() for "<<_id<<", which has "<<inFragment.size()<< " nodes in their fragment."<<endl;

    bool flag= false;

    for (vector<neighbourNodes>::iterator it = _NeighbourNodes.begin();it !=_NeighbourNodes.end();it++) {
        flag = false;
        for (int i = 0; i < inFragment.size(); ++i) {
            //如果邻居节点属于其大片段，则标注为true
            if((it->status)==inFragment[i]) flag= true;
        }
        if((flag== false)&&(it->weight < min))
        {
            min = it->weight;
            route = it->node;
            st = it->status;
            extendNode = _id;

            cout<<"min: "<<min<<"\t id: "<<route<<endl;
        }


    }
    return ;

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

void Node::setClass() {
    _class= true;
    cout<<"Set the Node "<<_id<<" to be common Node."<<endl;


}