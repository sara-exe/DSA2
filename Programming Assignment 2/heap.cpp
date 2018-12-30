// Sara Huang
// ECE 365: Data Structures & Algorithms II
// Programming Assignment #2: Priority Queues

#include <iostream>
#include <string>
#include <vector>
#include "heap.h"
#include "hash.h"

using namespace std;

heap::heap(int capacity): capacity(capacity),size(0) {
	data.resize(capacity+1);
	map = new hashTable(capacity*1000);
	node item;
}

int heap::parent(int index) {
	return (index/2);
}

int heap::left(int index) {
	return (index*2);
}

int heap::right(int index) {
	return (index*2+1);
}

int heap::getPos(node *pn) {
	int pos = pn - &data[0];
	return pos;

}

void heap::percolateUp(int posCur) {
	node tmp = data[posCur];
	int i = posCur;
	while ((i > 1) && ((tmp).key < data[parent(i)].key)) {
		data[i] = data[parent(i)];
		map->setPointer(data[i].id,&data[i]);
		i = parent(i);
	}
	data[i] = tmp;
	map->setPointer(data[i].id,&data[i]);
}

void heap::percolateDown(int posCur) { 
	node tmp = data[posCur];
	int i = posCur;
	while (i*2 <= size) { //similar to textbook 
		if ((tmp.key > data[left(i)].key) && (data[right(i)].key >= data[left(i)].key)) {
			data[i] = data[left(i)];
			map->setPointer(data[i].id,&data[i]);
			i = left(i);
		}
		else if ((tmp.key > data[right(i)].key) && (data[right(i)].key < data[left(i)].key)) {
			data[i] = data[right(i)];
			map->setPointer(data[i].id,&data[i]);
			i = right(i);
		}
		else {
			break;
		}
	}
		data[i] = tmp;
		map->setPointer(data[i].id,&data[i]);
}

int heap::insert(const string &id, int key, void *pv) {
	if (size == capacity) {
		return 1; //if the heap is already filled to capacity
	}
	if (map->contains(id)) {
		return 2; //if a node with the given id already exists (but the heap is not filled to capacity)
	}
	size++;
	data[size].id = id;
	data[size].key = key;
	data[size].pData = pv;
	map->insert(id,&data[size]);
	percolateUp(size);
	return 0; //on success
}

int heap::setKey(const string &id, int key) {
	bool b;
	node *pn = static_cast<node *> (map->getPointer(id,&b));
	if (!pn) {
		return 1; //if a node with the given id does not exist
	}
	int pos = getPos(pn);
	data[pos].key = key;
	if (key < data[parent(pos)].key) {
		percolateUp(pos);
	}
	else if ((key > data[right(pos)].key) || (key > data[left(pos)].key)) {
		percolateDown(pos);
	}
	return 0; //on success
}

int heap::deleteMin(string *pId, int *pKey, void *ppData) {
	if (size == 0) {
		return 1; //if the heap is empty
	}
	if (pId) {
		*pId = data[1].id;
	}
	if (pKey) {
		*pKey = data[1].key;
	}
	if (ppData) {
		*(static_cast<void **> (ppData)) = data[1].pData;
	}
	map->remove(data[1].id);
	data[1] = data[size];
	size--;
	percolateDown(1);
	return 0; //on success
}

int heap::remove(const string &id, int *pKey, void *ppData) {
	bool b;
	node *pn = static_cast<node *> (map->getPointer(id,&b));
	if (!pn) {
		return 1; //if a node with the given id does not exist
	}
	if (pKey) {
		*pKey = pn->key;
	}
	else if (ppData) {
		*(static_cast<void **> (ppData)) = data[1].pData;
	}
	int pos = getPos(pn);
	data[pos] = data[size];
	map->remove(id);
	size--;
	if (pos == 1) {
		percolateDown(pos);
	}
	else if (data[pos].key < data[parent(pos)].key) {
		percolateUp(pos);
	}
	else {
		percolateDown(pos);
	}
	return 0; //on success
}

