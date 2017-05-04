#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;


class Graph{
	int v,u;
	int **GMatrix; //macierz
	vector< vector<int> > GLists; //tablica wskaznikow na listy wierzcholkow
	vector<int> GColors;
	
	public:
	Graph(int n, int m); //tworzy macierz o n wierzcholkach i 0 krawedziach
	~Graph();
	void Insert(int n, int m);
	void Colorize(); //przypisuje kolory, tak  aby takie same nie byly obok siebie
	void printGraph();
};
Graph::Graph(int n, int m){
	v=n;
	u=m;
	GMatrix = new int*[n];
	for(int i=0;i<n;++i){
		GLists.push_back(vector<int>());
		GColors.push_back(0);
		GMatrix[i]=new int[m];
		for(int j=0;j<n;++j) GMatrix[i][j]=0;
	}
}
Graph::~Graph(){
    for(int i = 0; i < v; ++i)
         delete[] GMatrix[i];
    delete[] GMatrix; 
}
void Graph::Insert(int n, int m){
	++GMatrix[n-1][m-1];
	++GMatrix[m-1][n-1];
	GLists[n-1].push_back(m);
	GLists[m-1].push_back(n);
	sort(GLists[n-1].begin(), GLists[n-1].end());
	sort(GLists[m-1].begin(), GLists[m-1].end());
}
void Graph::Colorize(){
	int blue =0, red=0, green=0;//przelec po wszystkich, sprawdz czy mozesz dac BLUE, jesli nie, testuj dalej
	for(int i=0; i<GLists.size(); i++){
		blue=0;
		red=0;
		green=0;
			for(int j=0; j<GLists[i].size();j++){
				switch(GColors[GLists[i][j]-1]){
					case 0: 
						break;
					case 1: 
						blue=1;
						break;
					case 2: 
						red=1;
						break;
					case 3: 
						green=1;
						break;
				}
			}
			if(blue==0){
				GColors[i]=1;
			}
			else if(red==0){
				GColors[i]=2;
			}
			else{
				GColors[i]=3;
			}
	}
	
}
void Graph::printGraph(){
	//Macierz sasiedztwa
	for(int i=0; i<v; i++){
		for(int j = 0; j<v; j++){
			cout << GMatrix[i][j] << " ";
		}
		cout << endl;
	}
	//Listy sasiedztwa
	for(int i=0; i<v; i++){
		cout<<i+1<<" "<<GColors[i]<<": ";
		for(int j=0; j<GLists[i].size();j++){
			cout<<GLists[i][j]<<" ";	
		}
		cout<<endl;
	}
}

int main(){
	int n,m,v1,v2;
	cin >> n;
	cin >> m;
	
	Graph mojGraf(n, m);
	
	for(int i=0; i<m; i++){
		cin >> v1 >> v2;
		mojGraf.Insert(v1,v2);
	}
	mojGraf.Colorize();
	mojGraf.printGraph();

	return 0;
}
