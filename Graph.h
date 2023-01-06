#include <iostream>
#include <unordered_map>
#include <vector>
#include <list>
#include "Node.h"
#include <mutex>

using namespace std;



class Graph {


    private:
    int _num;
    std::vector <int> graph;
    mutex mutexM;
    mutex mutexP;





    public:
    std::vector <Node> VectorNodes;
    vector<vector<int>> pool;
    vector<int> res;

    Graph(int num, std::vector<int> v) {
        _num = num;
        graph=v;
    }

    void setNodeStatus(int id,int s);
    void setNodeClass(int id);

    // 将node进行初始化
    void distribute();
    void initPool(int threadNum);

    //打印输入矩阵
    void printGraph();
    //打印获取的点与权重
    void printListNodes();
    void printRes();
    void printPool();


     int findStatusById(int id);
     bool findClassById(int id);

     //寻找整个片段的最小权重边
     void findMinPresentById(int wakeupNode,int &min,int &id,int &extendNode);
};

