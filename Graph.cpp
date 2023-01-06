#include <iostream>
#include <vector>
#include "Graph.h"

using namespace std;



void Graph::printGraph() {
    for (int i = 0; i < _num; i++) {
        for (int j = 0; j < _num; j++) {
            cout << graph[i*_num + j] << " ";
        }
        cout << endl;
    }
    cout << endl;

}

void Graph::distribute(){
    for (int i = 0; i < _num; ++i) {

        std::vector <neighbourNodes> neighbourNodes;
        for (int j = 0; j < _num; ++j) {
            int weight = graph[i*_num + j];

            if(weight!=0) {
                neighbourNodes.push_back({j,weight,UNFINISHED});


            }
            else continue;
        }

        Node *n = new Node(i,neighbourNodes);

        VectorNodes.push_back(*n);

    }
}
void Graph::printListNodes() {
    for (int i = 0; i < _num; ++i) {
        VectorNodes[i].printNeighbourNodes();
    }
    cout << endl;
    }


int Graph::findStatusById(int id) {

    Node n = VectorNodes[id];
    return n.getStatus();
}

bool Graph::findClassById(int id) {

    Node n = VectorNodes[id];
    return n.getClass();
}


void Graph::setNodeStatus(int id,int s){

    Node &n = VectorNodes[id];

    n.setStatus(s);

    //通知邻边修改状态
    for (int i = 0; i < _num; ++i) {
        int weight = graph[id*_num + i];

        if(weight!=0) {
            Node &node = VectorNodes[i];
            node.updateStatusOfNeighbour(id,s);

        }

    }
}


void  Graph::setNodeClass(int id) {
    Node &n = VectorNodes[id];
    n.setClass();

}

void Graph::printRes(){
    cout<<"------------------------------------"<<endl;
    cout<<"Res: "<<endl;
    for (int i = 0; i < (res.size()/2); ++i) {
        cout<<res[i*2]<<" - "<<res[i*2+1]<<endl;
    }

    cout<<"------------------------------------"<<endl;

}

void Graph::printPool(){
    vector<vector<int>> &vec=pool;
    vector<int>::iterator it;
    vector<vector<int>>::iterator iter;
    vector<int> vec_tmp;

    cout<<endl;
    cout<<"------------------------------------"<<endl;
    cout<<"pool:"<<endl;
    int i = 0;
    for(iter = vec.begin(); iter != vec.end(); iter++)
    {
        vec_tmp = *iter;
        cout<<"["<<i++<<"]: ";
        for(it = vec_tmp.begin(); it != vec_tmp.end(); it++)
            cout << *it << " ";
        cout << endl;
    }
    cout<<"------------------------------------"<<endl;
}

void Graph::initPool(int threadNum ) {

    for (int i = 0; i < threadNum; ++i) {
        vector<int> vector;
        pool.push_back(vector);

    }

}

void  Graph::findMinPresentById(int wakeupNode,int &min,int &id,int &extendNode){
    vector <int> &inFragment=pool[wakeupNode];
    min = INT_MAX;
    id = INT_MAX;

    //遍历片段中的点，更新出最小值

    for (int i = 0; i < inFragment.size(); ++i) {

        int nodeId = inFragment[i];
        mutexP.lock();

        VectorNodes[nodeId].minWeightUnfinished(min,id,inFragment,extendNode);

        cout<<"main: min: "<<min<<"\t id: "<<id<<"\t"<<extendNode<<endl;
        mutexP.unlock();
    }
}