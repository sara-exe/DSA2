#ifndef _GRAPH_H
#define _GRAPH_H

#include<cstdlib>
#include<iostream>
#include<vector>
#include<list>
#include<algorithm>
#include<string>
#include<fstream>
#include<sstream>
#include "hash.h"
#include "heap.h"

class graph {
	private:
	struct node;
	struct edge;
	struct edge {
		node *end;
		int cost;
	};
	struct node {
		std::string name;
		int min;
		node *previous;
		std::list<edge*> adjlist;
		bool known; //if exists in tree
	};
	hashTable *table;
	heap *minheap;
	std::list<node*> Node;
	
	public:
	graph(std::ifstream&); //initialization
	int validVertex(std::string); //function to see if vertex is valid
	void initialVertex(std::ifstream&); //function for initialization of vertices
	void addVertex(const std::string&); //function for adding vertices to nodes
	void dijkstrasAlgorithm(const std::string&);
	void printPath(std::ofstream&); //function for printing shortest path to v after dijkstra has run
};

#endif




