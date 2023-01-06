
#include <iostream>
#include <unordered_map>
#include <vector>


using namespace std;


struct neighbourNodes{
    int node;
    int weight;
    int status;
};

#define FINISHED 1
#define UNFINISHED -1

class Node {
private:
    int _status;
    int _id;
    int _neighbourNum;
    bool _class;




public:

    std::vector <neighbourNodes> _NeighbourNodes;

    Node(int id,std::vector <neighbourNodes> Nodes){
        this -> _status = UNFINISHED;
        this -> _id = id;
        this -> _NeighbourNodes = Nodes;
        this -> _neighbourNum = _NeighbourNodes.size();
        this ->_class = false;
    }



    int getStatus(){
        return _status;
    }
    int getID(){
        return _id;
    }
    bool getClass(){
        return _class;
    }

    int getNeighbourNum(){
        return _neighbourNum;
    }

    void printNeighbourNodes();

    void setNeighbourNode(int node,int weight,int status);

    void setStatus(int s);
    void setClass();
    void printAllStatusAround();

    void minWeightUnfinished(int &min,int &route,vector<int> inFragment,int &extendNode);
    void updateStatusOfNeighbour(int id,int s);





};




