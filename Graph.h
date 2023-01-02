#include <iostream>
#include <unordered_map>
#include <vector>
#include <list>
#include "Node.h"

using namespace std;



class Graph {


    private:
    int _num;
    std::vector <int> graph;
    // 存储不同点的邻边都有谁，这里仍需要更改，状态有些冗余




    public:
    //std::list <Node> ListNodes;
    std::vector <Node> VectorNodes;

    Graph(int num, std::vector<int> v) {
        _num = num;
        graph=v;
    }
    /*
     * //todo:重载未正常运行，但不影响
    Node &operator[](int id) {
        return VectorNodes[id];
    }
     */
    //打印输入矩阵
    void printGraph();
    //打印获取的点与权重
    void printListNodes();

    // void allNodeClass();

    // 当前片段数（进程数）
    // void numberOfPart();

    // 当前结果值
    // void printResultNow();

    // 将node进行初始化
     void distribute();

     int findStatusById(int id);

    void findAllNodesByStatus(int s,std::vector <int>&res);
     void setNodeStatus(int id,int s);

     void wakeup(int id,int status);
};

