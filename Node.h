
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
#define UNFINISHED 0

class Node {
private:
    int _status;
    int _id;
    int _neighbourNum;




public:

    std::vector <neighbourNodes> _NeighbourNodes;

    Node(int id,std::vector <neighbourNodes> Nodes){
        this -> _status = 0;
        this -> _id = id;
        this -> _NeighbourNodes = Nodes;
        this -> _neighbourNum = _NeighbourNodes.size();
    }



    int getStatus(){
        return _status;
    }
    int getID(){
        return _id;
    }

    int getNeighbourNum(){
        return _neighbourNum;
    }

    void printNeighbourNodes();

    void setNeighbourNode(int node,int weight,int status);

    void setStatus(int s);
    void printAllStatusAround();

    void minWeightUnfinished(int &min,int &route);
    void updateStatusOfNeighbour(int id,int s);





};




