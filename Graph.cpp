#include <iostream>
#include <vector>
#include <unordered_map>

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


void Graph::findStatusById(int id) {

    Node n = VectorNodes[id];
    cout << n.getStatus() << endl;
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
            cout <<"Notified the "<< i <<" to update status"<<endl;
        }

    }
}
void Graph::wakeup(int id){

    cout << "Hello!! Wakeup " << id <<endl;
    setNodeStatus(id,1);


}