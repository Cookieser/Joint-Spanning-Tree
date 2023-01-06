#include <iostream>

#include <mutex>
#include <thread>
#include <vector>
#include <cstring>
#include <sstream>
#include <mutex>
#include "Graph.h"
#include "Prims.h"

#include<windows.h>
using namespace std;




int number_of_nodes;
mutex mutexM;
mutex mutexP;
int threadNum=6;



void func1(Graph &g,int wakeupNode) {
    //lock_guard<mutex> lk(mutex1);
    vector <int> r_weigh;

    vector <int> r_route;

    vector<vector<int>> &pool=g.pool;
    vector<int> &res =g.res;

    vector <int> &inFragment=pool[wakeupNode];

    int id = wakeupNode;

    int min;

    int extendNode;

    // 初始化唤醒
    r_route.push_back(wakeupNode);

    mutexM.lock();
    if(g.findStatusById(id)==UNFINISHED) {
        g.setNodeStatus(id, wakeupNode);
        inFragment.push_back(id);
    }else
    {
        cout<<"Have finished"<<endl;
    }


    mutexM.unlock();



    for (int i = 0; i < number_of_nodes+2; ++i) {


        mutexP.lock();
        g.printListNodes();
        g.printPool();
        mutexP.unlock();

        mutexM.lock();

        //遍历片段中的点，更新出最小值

        g.findMinPresentById(wakeupNode,min,id,extendNode);

        r_route.push_back(id);
        r_weigh.push_back(min);


        // 判断是否终止
        if(min == INT_MAX)
        {
            cout << "Finished!!!" << endl;
            mutexM.unlock();
            break;
        }

        if(g.findClassById(id)){
           cout<<"Connect the Common Node"<<id<<endl;
           cout<<"Inter the New world"<<endl;
            Sleep(10);
            break;
        }



        //判断：如果已经完成，就直接合并
        if(g.findStatusById(id)!=UNFINISHED){

            int st=g.findStatusById(id);
            mutexP.lock();
            cout<<"Merged by "<<id<<", which is in status "<< st <<endl;

            mutexP.unlock();
            for (int l = inFragment.size()-1; l >= 0; --l) {
                int tmp = inFragment[l];
                g.setNodeStatus(tmp,st);
                pool[st].push_back(tmp);
                inFragment.pop_back();

            }
            mutexP.lock();
            cout<<"This thread should be stopped here!!!"<<endl;
            cout << endl;

            for (int j = 0; j < r_route.size()-2; ++j) {

                cout << r_route[j]<<" - "<<r_route[j+1] << "\t"
                     << r_weigh[j] <<endl;
            }

            cout<<extendNode<<" - "<<id<<endl;
            res.push_back(extendNode);
            res.push_back(id);
            cout<<endl;
            mutexP.unlock();
            mutexM.unlock();
            return;

        }

        //判断：未完成的比较简单，直接记录并修改即可
        res.push_back(extendNode);
        res.push_back(id);
        g.setNodeStatus(id,wakeupNode);
        inFragment.push_back(id);

        mutexM.unlock();


    }

    return;


}




vector<int> create(){
    cin >> number_of_nodes;

    vector <int> graph;

    graph.resize(number_of_nodes * number_of_nodes);

    int temp;

    for (int i = 0; i < number_of_nodes * number_of_nodes; i++) {
        cin >> temp;
        graph[i] = temp;
    }
    return graph;


}



int main (void) {

    vector<int>graph=create();

    Graph *g= new Graph(number_of_nodes,graph);

    g -> distribute();

    g -> initPool(threadNum);

    g -> printPool();

    g -> printListNodes();



    //g ->setNodeStatus(2,2);

    //g->setNodeClass(0);

    std::thread thread1(func1,ref(*g),1);
    std::thread thread2(func1,ref(*g),5);
    std::thread thread3(func1,ref(*g),2);


    thread1.join();
    thread2.join();
    thread3.join();



    g->printRes();

    g->printPool();


    cout<<"-------------------------"<<endl;

    Prims *prims=new Prims(graph);

    prims -> findMst();

    prims->printMst();


}


