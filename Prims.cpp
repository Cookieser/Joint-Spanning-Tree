#include <iostream>
#include <limits.h>

#include "Prims.h"

using namespace std;

extern int number_of_nodes;

// 获得i,j 边权重
int Prims::getEdgeBetween(int i, int j) {
    return graph[i*number_of_nodes + j];
}

// 只要不是min意味着它就已经被连接启动了
int Prims::minIndexNotInSet(const vector <int> key) {
    int min = INT_MAX, min_index;
    for (int i = 0; i < number_of_nodes; i++) {
        // 遍历所有的点,如果该点不在set中并且key[i]<min,则更改 min 与 min index
        if (mst_set.find(i) == mst_set.end() && key[i] < min) {
            min = key[i];
            min_index = i;
        }

    }
    return min_index;
}

void Prims::printMst() {
    // 将所有存储的mst都打印出来即可
    for (int i = 0; i < number_of_nodes; i++) {
        if (mst[i] != -1) 
            cout << i<< " --- " << mst[i] << " " << getEdgeBetween(mst[i], i)<<endl;
    }

}

void Prims::printVector(string name, vector <int> key){
    cout << name <<": ";
    for (int i = 0; i < number_of_nodes; ++i) {

        cout << "[" << i << "]" << key[i] << " ";
    }
    cout << endl;

}

void Prims::printSet(set<int> &s){
    cout << "set: ";
    for (set<int>::iterator it = s.begin();it !=s.end();it++) {
        cout<<*it<<" ";
    }
    cout<<endl;
}
// 算法核心
void Prims::findMst() {
    // Key vector to manage the validity of various vertices.
    vector <int> key(number_of_nodes);
    mst.resize(number_of_nodes);
    // 初始化数组key与mst
    for (int i = 0; i < number_of_nodes; i++) { 
        key[i] = INT_MAX;
        mst[i] = -1;
    }

    printVector("key",key);
    printVector("mst",mst);
    printSet(mst_set);

    // Include 1st node;
    key[0] = 0;
    printVector("key",key);
    printVector("mst",mst);
    printSet(mst_set);

    cout << "--------------------------" << endl;
    // 初始化启动
    for (int i = 0; i < number_of_nodes; i++) {
        //寻找当前片段的最小邻边对应点
        int min_index = minIndexNotInSet(key);
        cout <<"Find the min index: " << min_index << endl;
        // 加入集合
        mst_set.insert(min_index);

        // 该循环用于找到刚刚加入集合点的周围边（不与片段内节点相连的边）的最小值与最小边
        for (int i = 0; i < number_of_nodes; i++) {

            //这里对第一个点来说由于初始化为0，自然没有满足的条件
            // 刚刚加入集合点的周围边（不与片段内节点相连的边）
            if (getEdgeBetween(min_index, i) && mst_set.find(i) == mst_set.end() 
                    && getEdgeBetween(min_index, i) <= key[i]) {
                cout << "i: "<< i <<endl;
                mst[i] = min_index;
                key[i] = getEdgeBetween(min_index, i);
            }

            printVector("key",key);
            printVector("mst",mst);
            printSet(mst_set);


        }
    }
}
