#include <string>
#include <iostream>
#include <algorithm>
#include <vector>
#include <sstream>

using namespace std;

vector<int> inputData(){
	vector<int> t1;
	string line;
	int num;

	getline(cin, line);
	istringstream stream(line);

	while(stream>>num) t1.push_back(num);

	return t1;

}

vector<int> sumazbioru(vector<int> t1, vector<int> t2){
	for(int i: t2){
		int isIn = 0;
		for(int j: t1){
			if(i==j) isIn=1;
			}
		if(isIn==0) t1.push_back(i);
		}
	return t1;
}

vector<int> roznicazbioru(vector<int> t1, vector<int> t2){
	vector<int> t3;
	for(int i:t1){
		int isIn=0;
		for(int j:t2){
			if(i==j) isIn=1;
		}
		if(isIn==1) continue;
		t3.push_back(i);
	}
	return t3;
}

vector<int> przecieciezbioru(vector<int> t1, vector<int> t2){
	vector<int> t3;
	for(int i:t1){
		for(int j:t2){
			if(i==j) t3.push_back(i);
		}
	}
	return t3;
}

vector<int> roznicasymetrycznazbioru(vector<int> t1, vector<int> t2){
	vector<int> t3;
	for(int i:t1){
		int isIn=0;
		for(int j:t2){
			if(i==j) isIn=1;
		}
		if(isIn==1) continue;
		t3.push_back(i);
	}
	for(int i:t2){
		int isIn=0;
		for(int j:t1){
			if(i==j) isIn=1;
		}
		if(isIn==1) continue;
		t3.push_back(i);
	}
	return t3;
}
void printVector(vector<int> t){
	for(auto const& value:t){
		cout<<value<<" ";
	}
	cout<<endl;
}



int main(){

	vector<int> t1 = inputData();
	vector<int> t2 = inputData();

	vector<int> suma(sumazbioru(t1,t2));
	vector<int> roznica(roznicazbioru(t1,t2));
	vector<int> przeciecie(przecieciezbioru(t1,t2));
	vector<int> roznicasymetryczna(roznicasymetrycznazbioru(t1,t2));
	cout << "suma: ";
	printVector(suma);
	cout << "roznica: ";
	printVector(roznica);
	cout << "przeciecie: ";
	printVector(przeciecie);
	cout << "roznica symetryczna: ";
	printVector(roznicasymetryczna);

	return 0;
}
