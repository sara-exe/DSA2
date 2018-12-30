//Sara Huang
//ECE 365 
//DSA Programming Assignment 1

#include "hash.h"
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <exception>

using namespace std;

hashTable::hashTable (int size) {
        capacity = getPrime(size);
        data.resize(capacity);
        for (int i = 0; i < data.size(); i++) {
                data[i].isOccupied = false;
                data[i].isDeleted = false;
        }
        filled = 0;
}

unsigned int hashTable::getPrime(int size) { //uses precomputed sequence of selected prime numbers
        int list_of_primes[] = {98317, 196613, 393241, 786433, 1572869, 3145739, 6291469, 12582917, 25165843, 50331653, 100663319, 201326611, 402653189, 805306457, 1610612741}; //list of primes taken from https://planetmath.org/goodhashtableprimes
        int i = 0;
        while (list_of_primes[i] <= size) {
                i++;
        }
                return list_of_primes[i]; //returns a prime number at least as large as size
}

int hashTable::insert(const std::string &key, void *pv) { //insert the specified key in hash table
        if (filled > (capacity)/2) {
                if (rehash()) { //success
                        return 0;
                }
                else {
                        return 2; //failure
                }
        }
        if (contains(key) == true) { //key already exists in hash table
                return 1;
        }
        int i = hash(key) % capacity;
        if (i < 0) {
                i += capacity;
        }
        while (data[i].isOccupied == true) {
                i++;
                i %= capacity;
        }
        if ((data[i].isOccupied == false) || (data[i].isDeleted == true)) { //either or condition
                data[i].key = key;
                data[i].isOccupied = true;
                data[i].isDeleted = false;
                data[i].pv = pv;
                filled++;
                return 0;
        }
        return -1;
}

bool hashTable::contains(const string &key) { //Check if the specified key is in the hash table.
        int i = findPos(key);
        if (i == -1) {
                return false; //specified key is not in hash table
        }
        else {
                return true; //specified is in hash table
        }
}

bool hashTable::remove(const string &key) { //lazy deletion
        int i = findPos(key);
        if (i >= 0) {
                data[i].isDeleted = true;
                return true; //on success
        }
        else {
                return false; //if specified key is not in hash table
        }
}

int hashTable::hash(const string &key) { //The hash function.
        int hash = 0;
        unsigned int i = 0;
        for (i = 0; i < key.size(); i++) {
                hash = hash * 37 + key[i]; //linear probing from textbook
                hash %= capacity;
                if (hash < 0) {
                        hash += capacity;
                }
        }
        return hash;
}

int hashTable::findPos(const string &key) { //Search for an item with the specified key.
        int i = hash(key) % capacity;
        while (data[i].isOccupied == true) {
                if ((data[i].key == key) && (data[i].isDeleted == false)) {
                        return i; //returns position if found
                }
                i++;
        }
        return -1; //returns -1 otherwise
}

bool hashTable::rehash() { //the rehash function, makes the hash table bigger.
        try {
                vector<hashItem> tmp = data;
                capacity = getPrime(capacity);
                filled = 0;
                data.clear();
                data.resize(capacity);
                for(int i = 0; i < tmp.size(); i++) {
                        if ((tmp[i].isOccupied == true) && (tmp[i].isDeleted == false)) {
                                insert(tmp[i].key,tmp[i].pv);
                        }
                }
                return true; //on success
        }
        catch (exception& e) {
                cerr << "Resize failed: " << e.what() << endl;
                return false; //memory allocation fails
        }
}

void *hashTable::getPointer(const string &key, bool *b) {
        int i = findPos(key);
        if (i == -1) {
                *b = false;
                return NULL;
        }
        else {
                *b = true;
                return data[i].pv;
        }
}

int hashTable::setPointer(const string &key, void *pv) {
        int i = findPos(key);
        if (i == -1) {
                return -1;
        }
        else {
                data[i].pv = pv;
                return 0;
        }
}


