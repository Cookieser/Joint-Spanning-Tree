#include <iostream>


#include <thread>
#include <vector>

#include "Graph.h"
#include "Prims.h"
using namespace std;

int number_of_nodes;


int main (void) {
    // We need to take the input here.
    cin >> number_of_nodes;

    vector <int> graph;
    graph.resize(number_of_nodes * number_of_nodes);

    int temp;
    for (int i = 0; i < number_of_nodes * number_of_nodes; i++) {
        cin >> temp;
        graph[i] = temp;
    }


    vector <int> r_weigh;
    vector <int> r_route;

    Graph *g= new Graph(number_of_nodes,graph);
    g -> distribute();
    g -> printListNodes();

    int min = INT_MAX;
    int id = INT_MAX;
    g->wakeup(0);
    r_route.push_back(0);
    g -> printListNodes();
    g->VectorNodes[0].minWeightUnfinished(min,id);
    r_route.push_back(id);
    r_weigh.push_back(min);



    for (int i = 0; i < number_of_nodes-1; ++i) {
        g->setNodeStatus(id,1);
        g -> printListNodes();
        min = INT_MAX;
        id = INT_MAX;
        for (int j = 0; j < r_route.size(); ++j) {
            //cout<<"r_route["<<j<<"]"<<r_route[j]<<endl;
            int nodeId=r_route[j];
            g->VectorNodes[nodeId].minWeightUnfinished(min,id);
            //cout <<id<<" "<<min<<endl;

        }
        r_route.push_back(id);
        r_weigh.push_back(min);
        cout<< endl;
        if(min==INT_MAX)
        {
            cout<<"Finished!!!"<<endl;
            break;
        }

    }
    cout <<endl;

    for (int i = 0; i < r_route.size()-2; ++i) {
        cout<<r_route[i]<<" - "<<r_route[i+1]<<"\t"
        <<r_weigh[i] <<endl;
    }






    return 0;
}


