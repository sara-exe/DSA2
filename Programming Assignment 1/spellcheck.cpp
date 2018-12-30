// Spellchecker program
//Sara Huang ECE 365

#include "hash.h"
#include <cstdlib>
#include <string>
#include <ctime>
#include <cctype>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <array>
#include <vector>

using namespace std;

void loadDict(hashTable *my_hash, string my_dict);
void spellCheck(hashTable *dict, string my_file, string my_out);

int main() {
	hashTable *my_hash = new hashTable(50000); //for dictionary
	string my_dict, my_file, my_out;
	cout << "Enter name of dictionary: ";
	cin >> my_dict;
	clock_t t_1, t_2; //time
	t_1 = clock();
	loadDict(my_hash, my_dict);
	t_2 = clock();
	cout << "Total time (in seconds) to load dictionary: " << ((double)(t_2 - t_1)/(CLOCKS_PER_SEC)) << endl;
	cout << "Enter name of input file: ";
	cin >> my_file;
	cout << "Enter name of output file: ";
	cin >> my_out;
	t_1 = clock();
	spellCheck(my_hash, my_file, my_out);
	t_2 = clock();
	cout << "Total time (in seconds) to check document: " << ((double)(t_2 - t_1)/(CLOCKS_PER_SEC)) << endl;
	return 0;
}

void loadDict(hashTable *my_hash, string my_dict) {
	ifstream dictionary;
	dictionary.open(my_dict);
	if (dictionary.fail()) {
		cout << "Error: cannot open file" << my_dict << "for reading" << endl;
		exit(EXIT_FAILURE); 
	}
	string line;
	while (getline(dictionary,line)) {
		std::transform(line.begin(),line.end(),line.begin(),::tolower);
		(*my_hash).insert(line);
	}
	dictionary.close();
}

void spellCheck(hashTable *my_hash, string my_file, string my_out) {
	ifstream in_file;
	in_file.open(my_file);
	if (in_file.fail()) {
		cout << "Error: Cannot open file "<< my_file << "for reading" << endl;
		exit(EXIT_FAILURE);
	}
	ofstream out_file;
	out_file.open(my_out);
	if (out_file.fail()) {
		cout << "Error: Cannot open file " << my_out << "for reading" << endl;
		exit(EXIT_FAILURE);
	}
	char t;
	string line = "";
	string known_word = "";
	unsigned long line_no = 0;
	bool containsNum = false;
	while (getline(in_file,line)) {
		int i = 0;
		line_no++;
		while (i <= line.size()) {
			t = tolower(line[i++]); //convert uppercase to lowercase
			if (isdigit(t)) containsNum = true; 
				if (isalnum(t)||(t == '-') || (t =='\'')) { //check if t is uppercase/lowercase or a number
					known_word+=t;
				}
				else if (known_word.size() != 0 && containsNum == 0) {
					if (known_word.size() > 20) { //check if exceeds 20 character length
						out_file << "Long word at line " << line_no << ", starts: " << known_word.substr(0,20) << endl;
					}
					else if (!my_hash->contains(known_word)) {
						out_file << "Unknown word at line " << line_no << ": " << known_word << endl;
					}
				known_word = "";
			}
			else {
				known_word = "";
				containsNum = false;
			}
		}
	}
	in_file.close();
	out_file.close();
}