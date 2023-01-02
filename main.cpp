#include <iostream>

#include <mutex>
#include <thread>
#include <vector>
#include <cstring>
#include <sstream>
#include <mutex>
#include "Graph.h"
#include "Prims.h"

using namespace std;

int number_of_nodes;
mutex mutex1;
mutex mutex3;
mutex mutex2;
int threadNum=6;
void printPool(vector<vector<int>> vec){
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


void func1(Graph &g,vector<vector<int>> &pool,int wakeupNode,vector<int> &res) {
    //lock_guard<mutex> lk(mutex1);
    vector <int> r_weigh;

    vector <int> r_route;

    vector <int> &inFragment=pool[wakeupNode];

    int id = wakeupNode;

    int min;

    int extendNode;



    r_route.push_back(wakeupNode);

    //需要注意的共享数据类型有：g以及pool

    //wakeup操作
    //lock1
    mutex1.lock();

    g.setNodeStatus(id,wakeupNode);
    inFragment.push_back(id);

    mutex1.unlock();



    for (int i = 0; i < number_of_nodes; ++i) {



        g.printListNodes();
        printPool(pool);

        min = INT_MAX;
        id = INT_MAX;

        //遍历片段中的点，更新出最小值
        mutex3.lock();
        for (int j = 0; j < inFragment.size(); ++j) {
            //cout<<"r_route["<<j<<"]"<<r_route[j]<<endl;

            int nodeId = inFragment[j];

            g.VectorNodes[nodeId].minWeightUnfinished(min,id,inFragment,extendNode);

            cout<<wakeupNode<<"main: min: "<<min<<"\t id: "<<id<<"\t"<<extendNode<<endl;

        }

        r_route.push_back(id);
        r_weigh.push_back(min);



        if(min == INT_MAX)
        {
            cout << "Finished!!!" << endl;
            mutex3.unlock();
            break;
        }


        // 判断是否终止

        bool flag2= false;
        for (int k = 0; k < inFragment.size(); ++k) {

            if(id==inFragment[k]) flag2= true;

        }



        if((flag2== false)&&(g.findStatusById(id)!=UNFINISHED)){

            int st=g.findStatusById(id);
            cout<<"Merged by "<<id<<", which is in status "<< st <<endl;
            for (int l = inFragment.size()-1; l >= 0; --l) {
                int tmp = inFragment[l];
                pool[st].push_back(tmp);
                inFragment.pop_back();

            }
            cout<<"This thread should be stopped here!!!"<<endl;
            cout << endl;


            //lock

            for (int j = 0; j < r_route.size()-2; ++j) {

                cout << r_route[j]<<" - "<<r_route[j+1] << "\t"
                     << r_weigh[j] <<endl;
            }

            cout<<extendNode<<" - "<<id<<endl;
            res.push_back(extendNode);
            res.push_back(id);
            cout<<endl;
            mutex3.unlock();
            return;

        }


        res.push_back(extendNode);
        res.push_back(id);
        g.setNodeStatus(id,wakeupNode);
        inFragment.push_back(id);

        mutex3.unlock();


    }


    cout << endl;
    for (int i = 0; i < r_route.size()-2; ++i) {
        cout << r_route[i]<<" - "<<r_route[i+1] << "\t"
             << r_weigh[i] <<endl;

    }

    //mutex2.unlock();
    return;


}


void printRes(vector<int> res){

    cout<<"------------------------------------"<<endl;
    cout<<"Res: "<<endl;
    for (int i = 0; i < (res.size()/2); ++i) {
        cout<<res[i*2]<<" - "<<res[i*2+1]<<endl;
    }

    cout<<"------------------------------------"<<endl;

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

    vector<vector<int>> pool;

    vector<int> res;


    for (int i = 0; i < threadNum; ++i) {
        vector<int> vector;

        pool.push_back(vector);

    }

    printPool(pool);


    vector<int>graph=create();

    Graph *g= new Graph(number_of_nodes,graph);

    g -> distribute();

    g -> printListNodes();


    //g ->setNodeStatus(2,2);

    std::thread thread1(func1,ref(*g),ref(pool),1,ref(res));
    std::thread thread2(func1,ref(*g),ref(pool),5,ref(res));
    std::thread thread3(func1,ref(*g),ref(pool),2,ref(res));
    thread1.join();
    thread2.join();
    thread3.join();

    //func1(*g,pool,3,res);

    printRes(res);

    printPool(pool);

    cout<<"-------------------------"<<endl;
    Prims *prims=new Prims(graph);

    prims -> findMst();

    prims->printMst();



}


