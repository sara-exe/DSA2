//Sara Huang
//Programming Assignment 4

#include<iostream>
#include<cstdlib>
#include<fstream>
#include<string>
#include<vector>
#include<sstream>
#include<algorithm>

using namespace std;

int matrix[1000][1000];

string s, t, u;

string merge() {
	string a = "";
	string b = "";
	int i = 0, j = 0, k = 0;
	int tmp = 1;
	matrix[0][0] = 1;
	for (k = 0; k != u.size(); k++) {
		for (j = tmp; j > 0; j--) {
			for (i = j; i-1 > j; i++) {
				if (s[i] == u[k] && matrix[i-1][j] == 1) {	
					matrix[i][j] = 1;
					u[i] = toupper(u[i]);
					i--;
				}
				if (t[j] == u[k] && matrix[i][j-1] == 1) {
					matrix[i][j] = 1;
				}
			}
		}
		tmp++;
	}
	return a;
	return b;
}

void clear(int col, int row) {
	for (int i = 0; i < col; i++) {
		for (int j = 0; j < row; j++) {
			matrix[i][j] = 0;
		}
	}
}

int main() {
	string instrng, outstrng;
	cout << "Enter name of input file: ";
	cin >> instrng;
	ifstream fin(instrng.c_str());
	if (! cin) {
		cerr << "Error: unable to open " << instrng << "for reading" << endl;
	}
	cout << "Enter name of output file: ";
	cin >> outstrng;
	ofstream fout(outstrng.c_str());
	if (! cout) {
		cerr << "Error: unable to open " << outstrng << "for reading" << endl;
	}
	while(getline(fin,s)) {
		getline(fin,t);
		getline(fin,u);
		instrng = merge();
		if(!instrng.empty()) {
			cout << instrng << endl;
		}
		else {
			cout << "*** NOT A MERGE ***" << endl;
		}
		fout << merge() << endl;
		clear(s.length()+1,t.length()+1);
	}
	fin.close();
	fout.close();
	return 0;
}

