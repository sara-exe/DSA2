#include "graph.h"
#include<string>
#include<iostream>
#include<fstream>
#include<cstdlib>
#include<time.h>
#include<sstream>
#include<vector>

using namespace std;

int main() {
	string Source;
	string name;
	cout << "Enter name of graph file: ";
	cin >> name;
	ifstream fin(name.c_str());
	cout << "Enter a valid vertex id for the staring vertex: ";
	cin >> Source;
	graph g(fin);
	while(!g.validVertex(Source)) {
		cout << "Enter a valid vertex id for the staring vertex: ";
		cin >> Source;
	}
	clock_t t1 = clock();
	g.dijkstrasAlgorithm(Source);
	clock_t t2 = clock();
	cout << "Total time (in seconds) to apply Dijkstra's algorithm: " << double(t2-t1)/CLOCKS_PER_SEC << endl;
	cout << "Enter name of output file: ";
	cin >> name;
	ofstream fout(name.c_str());
	g.printPath(fout);
	fin.close();
	fout.close();
	return 0;
}


