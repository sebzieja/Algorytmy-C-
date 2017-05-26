#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include <string>
#include <queue>
#include <sstream>
#include <random>

using namespace std;


struct vertex{
    typedef pair<int, vertex*> ve;
    vector<ve> adj;
    vertex* parent=NULL;
    int color = 0;
    int time = 0;
    int visited=0;
    double distance;
    string name;
    vertex(string s) : name(s){}
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
    void dfsVisit(vertex* ve);
    void dfs();
    void printTopoSort();
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

void graph::dfs(){
	for(auto it = work.cbegin(); it != work.cend(); ++it) it->second->color=0;
	time=0;
	for(auto it = work.cbegin(); it != work.cend(); ++it){
		//cout<<"dfs dla "<<it->second->name<<endl;
		if (it->second->color==0){;
			dfsVisit(it->second);
		}
	}
}
void graph::dfsVisit(vertex *ve){
	++time;
	ve->time=time;
	ve->color=1;
    vertex* ve2;
    ve2=ve;
	for(auto i: ve->adj){
		if(i.second->color==0){
            i.second->parent=ve;
            //cout<<"Ustawia "<<i.second->name<<" "<<i.second->parent->name<<endl;
            dfsVisit(i.second);	
	    }
        if(i.second->color==1){
            cout<<"Jest cykl\n";
            cout<<i.second->name<<" "<<ve->name<<" ";
            while(ve2->parent!=i.second){
                cout << ve2->parent->name << " ";
                ve2 = ve2->parent;
            }
        cout<<endl;
        }
    }
	ve->color=2;
	++time;
	ve->time=time;
	//cout<<ve->name<<" ";
	topoSort[ve->time]=ve;
}

void graph::printTopoSort(){
	for(auto elem : topoSort){
		cout << elem.second->name << " "<< "\n";
	}
	cout<<endl;
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


int main(){
    graph test1;
    /*int ve, ed, length;
    string v1, v2;
    cin>>ve>>ed;
    for(int i=1;i<=ve;i++){
    	test1.addvertex(to_string(i));
    }
    for(int i=0;i<ed;i++){
    	cin>>v1>>v2>>length;
    	test1.addedge(v1,v2, length);
    }
    test1.printGraph();
    //test1.bfs("1");
    //cout<<"Najkrotsza droga z 4 do 1 to: "<<endl;
    //test1.printRoute("3");
    test1.dfs();

    test1.printTopoSort();*/
    makeMatrix(6, &test1, 70);
    test1.dfs();
    test1.printGraph();
    test1.printTopoSort();


	return 0;
}
