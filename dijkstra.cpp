#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include <string>
#include <queue>
#include <sstream>
#include <random>
#include <climits>
#include <fstream>
#include <unistd.h>
#include <set>

using namespace std;


struct vertex{
    typedef pair<int, vertex*> ve;
    vector<ve> adj;
    vertex* parent=NULL;
    int color = 0;
    int time = 0;
    int visited=0;
    int distance = 0;
    string name;
    vertex(string s) : name(s){}
};

class CompareDist{
public:
    bool operator()(vertex* n1,vertex* n2) {
        return n1->distance>n2->distance;
    }
};
class graph
{
public:
	int time=0;
	map<int, vertex*, std::greater<int>> topoSort;
    typedef map<string, vertex *> vmap;
    vmap work;
    void addvertex(const string &name);
    void addedge(const string& from, const string& to, double cost);
    void addedge(const string& from, const string& to);
    void printGraph();
    void bfs(const string &name);
    void printRoute(const string& name);
    void dijkstra(const string& name);
    void relax(vertex* u, vertex* v, int w);
    void printDistance(const string &name);
    priority_queue<vertex*,vector<vertex*>,CompareDist> pq;
};




void graph::addvertex(const string &name)
{
    vmap::iterator itr = work.find(name);
    if (itr == work.end())
    {
        vertex *v;
        v = new vertex(name);
        work[name] = v;
        return;
    }
    cout << "\nVertex already exists!";
    //test//
}

void graph::addedge(const string& from, const string& to, double cost)
{
    vertex *f = (work.find(from)->second);
    vertex *t = (work.find(to)->second);
    pair<int, vertex *> edge = make_pair(cost, t);
    f->adj.push_back(edge);
}

void graph::addedge(const string& from, const string& to)
{
    vertex *f = (work.find(from)->second);
    vertex *t = (work.find(to)->second);
    pair<int, vertex *> edge = make_pair(1, t);
    pair<int, vertex *> edge2 = make_pair(1, f);
    f->adj.push_back(edge);
    t->adj.push_back(edge2);
}

void graph::printGraph(){
    for(auto it = work.cbegin(); it != work.cend(); ++it){
    cout << it->first << " : ";
    for (auto i: it->second->adj) cout << i.second->name << " ";
    cout<<endl;
    }
}

void graph::printRoute(const string& name){
    vertex *ve = (work.find(name)->second);
    while(ve->parent!=NULL){
        cout << ve->parent->name << " ";
        ve = ve->parent;
    }
    cout<<endl;
}

void graph::bfs(const string &name){
    for(auto it = work.cbegin(); it != work.cend(); ++it) it->second->color=0;
    vertex *ve = (work.find(name)->second);
    vertex *ve2;
    queue<vertex*> Q;
    ve->color=1;
    ve->distance=0;
    ve->parent=NULL;
    Q.push(ve);
    while(!Q.empty()){
        ve2=Q.front();
        cout << ve2->name<<endl;
        Q.pop();
        for (auto i: ve2->adj){
            if (i.second->color==0){
                i.second->color=1;
                i.second->distance=(ve->distance)+1;
                i.second->parent=ve2;
                Q.push(i.second);
            }
        ve2->color=2;
        }
    }

}

void graph::printDistance(const string &name){
    vertex *ve=work.find(name)->second;
    cout<<ve->distance<<endl;
}

void makeMatrix(int v, graph* Graf, int p){
    for(int i=1;i<=v;i++){
    	Graf->addvertex(to_string(i));
    }
    int temp;
    int matrix[v][v];
    for(int i=0;i<v;i++){
        for(int j=0;j<v;j++){
            matrix[i][j]=0;
        }
    }
    for(int i=0;i<v;i++){
        for(int j=0;j<=i-1;j++){
            if(rand()%100<=p){
                matrix[i][j]=1;
                Graf->addedge(to_string(i+1),to_string(j+1),1);
            }
        }
    }
    for(int i=0;i<v;i++){
        for(int j=0;j<v;j++){
            cout<<matrix[i][j]<<" ";
        }
        cout<<endl;
    }

}
void inputGraph(graph* Graf){
    int x=1, y=1, b, a;
    cin>>a;
    for(int i=1;i<=a;i++){
        Graf->addvertex(to_string(i));
    }
    for(int i=0;i<a;i++){
        for(int j=0;j<a;j++){
            cin>>b;
            if(b!=0){
                Graf->addedge(to_string(y), to_string(x), b);
            }
            x++;
        }
        y++;
        x=1;
    }

}



void graph::relax(vertex* u, vertex* v, int w){
    if (v->distance>((u->distance) + w)){
        v->distance=u->distance + w;
        v->parent=u;
        pq.push(v);

    }
}
void graph::dijkstra(const string& name){
    for(auto it = work.cbegin(); it != work.cend(); ++it){
        it->second->color=0;
        it->second->distance=999999;
    } 
    vertex *ve = (work.find(name)->second);
    ve->distance=0;

    for(auto it = work.cbegin(); it != work.cend(); ++it){
        pq.push(it->second);
    } 
    while(!pq.empty()){
        vertex* ve2=pq.top();
        pq.pop();
        for(auto i:ve2->adj){
            relax(ve2, i.second, i.first);
        }
    }
}






int main(){
    

    graph test1;
    inputGraph(&test1);
    test1.printGraph();
    string a, b;
    cin>>a;
    cout<<a<<endl;
    test1.dijkstra(a);
    cin>>b;
    test1.printRoute(b);

    vertex* ve=test1.work.find(b)->second;
    cout<<ve->distance<<endl;

	return 0;
}
