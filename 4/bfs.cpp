#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include <string>
#include <queue>

using namespace std;

struct vertex{
    typedef pair<int, vertex*> ve;
    vector<ve> adj;
    vertex* parent=NULL;
    int color = 0;
    double distance;
    string name;
    vertex(string s) : name(s){}
};

class graph
{
public:
    typedef map<string, vertex *> vmap;
    vmap work;
    void addvertex(const string &name);
    void addedge(const string& from, const string& to, double cost);
    void printGraph();
    void bfs(const string &name);
    void printRoute(const string& name);
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
    pair<int, vertex *> edge2 = make_pair(cost, f);
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
}

void graph::bfs(const string &name){
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



int main(){
	/*
	int n,m,v1,v2;
	cin >> n;
	cin >> m;
	
	Graph mojGraf(n, m);
	
	for(int i=0; i<m; i++){
		cin >> v1 >> v2;
		mojGraf.Insert(v1,v2);
	}
	mojGraf.Colorize();
	mojGraf.printGraph();*/
    graph test1;
    test1.addvertex("1");
    test1.addvertex("2");
    test1.addvertex("3");
    test1.addvertex("4");
    test1.addvertex("5");
    test1.addvertex("6");
    test1.addedge("1", "2", 1);
    test1.addedge("1", "6", 1);
    test1.addedge("5", "6", 1);
    test1.addedge("2", "5", 1);
    test1.addedge("2", "3", 1);
    test1.addedge("3", "4", 1);
    test1.printGraph();
    test1.bfs("1");
    cout<<"Najkrotsza droga z 4 do 1 to: "<<endl;
    test1.printRoute("4");
	return 0;
}
