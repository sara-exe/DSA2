#include<iostream>
#include<cstdlib>
#include<fstream>
#include<vector>
#include<list>
#include<sstream>
#include<string>
#include<algorithm>
#include "graph.h"
#include "hash.h"
#define INFINITY 1000000000

using namespace std;

graph::graph(ifstream &fin) {
	table = new hashTable();
	initialVertex(fin);
	minheap = new heap(Node.size());
	node *nodeptr;
	list<node *>::iterator it = Node.begin();
	for (; it != Node.end(); it++) {
		minheap->insert((*it)->name,INFINITY,*it);
		nodeptr = *it;
		nodeptr->min = INFINITY; 
		nodeptr->previous = NULL;
		nodeptr->known = false;
		minheap->setKey(nodeptr->name,nodeptr->min);
	}
}

int graph::validVertex(string v) {
	if(table->contains(v)) {
		return true;
	}
	else {
		return false;
	}
}

void graph::initialVertex(ifstream &fin) {
	string input;
	int cost;
	string v_1, v_2;
	bool s;
	while (getline(fin,input)) {
		std::stringstream ss(input);
		string tmp;
		vector<string> arg;
		while (ss >> tmp)
			arg.push_back(tmp);
		if (arg.size() != 3) {
			cerr << "Error: invalid input argument" << endl;
			break; 
		}
		else {
			v_1 = arg[0];
			v_2 = arg[1];
			std::stringstream tt(arg[2]);
			tt >> cost; 
			if (!table->contains(v_1)) {
				addVertex(v_1);
			}
			if (!table->contains(v_2)) {
				addVertex(v_2);
			}
			node *nodeptr = new node;
			nodeptr = static_cast<node *>(table->getPointer(v_1,&s));
			edge *edgeptr = new edge;
			edgeptr->end = static_cast<node *>(table->getPointer(v_2,&s));
			edgeptr->cost = cost;
			nodeptr->adjlist.push_back(edgeptr);
		}
	}
}

void graph::addVertex(const string &v) {
	node *nodeptr = new node;
	nodeptr->name = v;
	nodeptr->previous = NULL;
	table->insert(v,nodeptr);
	Node.push_back(nodeptr);
	if (table->insert(v,nodeptr) == 0) {
		cerr << "Error: cannot add " << v << " for insertion into the hash table" << endl;
	}
}

void graph::dijkstrasAlgorithm(const string &source) {
	bool b;
	node *Source = static_cast<node *>(table->getPointer(source,&b));
	Source->min = 0;
	Source->previous = NULL;
	Source->known = false;
	minheap->setKey(Source->name,Source->min);
	node *w;
	int other = 0;
	while (minheap->deleteMin(NULL,NULL,&w) != 1) {
		w->known = true;
		//for each vertex w adjacent to v
		list<edge *>::iterator it = (w->adjlist).begin(); 
		for (; it != (w->adjlist).end(); it++) {
			node *v = (*it)->end;
			if (!v->known) {
				other = w->min + (*it)->cost;
				if (other < (v->min)) {
					v->min = other;
					v->previous = w; //update w
					minheap->setKey(v->name,v->min);
				}
			}
		}
	}
}

void graph::printPath(ofstream &fout) { //assume that the path exists
	int totalcost;
	node *nodeptr;
	list<string> vertices;
	list<node *>::iterator it = Node.begin();
	for (; it != Node.end(); it++) {
		nodeptr = *it;
		vertices.push_front(nodeptr->name);
		totalcost = nodeptr->min;
		if (totalcost < 0 || totalcost >= INFINITY) {
			fout << vertices.front() << ": NO PATH" << endl;
		}
		else {
			while (nodeptr->previous != NULL) {
				nodeptr = nodeptr->previous;
				vertices.push_front(nodeptr->name);
			}
			list<string>::iterator it1 = vertices.begin();
			fout << vertices.back() << ": " << totalcost << " [" <<(*it1);
			it1++;
			while (it1 != vertices.end()) {
				fout << ", " << (*it1);
				it1++;
			}
			fout << "]" << endl;
		}
		vertices.clear();
	}
}


