//============================================================================
// Name        : 2.cpp
// Author      : 
// Version     :
// Copyright   : 
// Description : 
//============================================================================

#include <iostream>
#include <array>
#include <vector>
#include <iterator>
//#include <algorithm>
using namespace std;

int leftSon(int i){
	return 2*i+1;
	}
int rightSon(int i){
	return 2*i+2;
	}
int father(int i){
	return (i-1)/2;
	}


void przywrocWlasnoscKopca(vector<int> &table, int i, int length){
	int min, lewy, prawy;
	lewy = leftSon(i);
	prawy = rightSon(i);

	if(length<=lewy) return;
	min=i;
	if(table[lewy]>table[i]){
		min=lewy;
	}

	if (prawy < length && table[min]<table[prawy]){
			min=prawy;
	}

	if(min!=i){
		swap(table[min], table[i]);
		przywrocWlasnoscKopca(table, min, length);
	}
}




void budujKopiec(vector<int> &table){
	for (int i=table.size()/2-1; i>=0; --i){
		przywrocWlasnoscKopca(table, i, table.size());
	}
}

int PobierzNajwiekszy(vector<int> &table){
	int n = table.size();
	--n;
	int max = table[0];
	swap(table[0],table[n]);
	--n;
	przywrocWlasnoscKopca(table, 0, n);
	return max;
}

void WstawElement(vector<int> &table, int a){
	int n = table.size();
	table.push_back(a);
	while(n>0 && a>table[father(n)]){
		swap(table[n], table[father(n)]);
		n=father(n);
	}
}

void HeapSort(auto &table){
	int n=table.size();
	budujKopiec(table);
	for(int i=n-1; i>=1; --i){
		swap(table[0], table[i]);
		--n;
		przywrocWlasnoscKopca(table, 0, n);
	}
}


int main() {
	//int table[] = {12 ,4, 7, 6, 8};
	vector<int> table = {12,4,7,6,8,9};
	budujKopiec(table);
	for (int i: table) cout<< i << " " << endl;
	HeapSort(table);
	cout<<"Posortowane HeapSort: "<<endl;
	for (int i: table) cout<< i << " " << endl;
//	WstawElement(table, 5);
//	for (int i: table) cout<< i << " " << endl;
//	cout << PobierzNajwiekszy(table) << endl;
	return 0;
}
