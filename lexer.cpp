#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include "lexer.h"
using namespace std;


int main(int argc, const char * argv[]){
	cout << argv[1] << endl;
	int x = 0;
	ifstream readFile;
	readFile.open(argv[1]);
	string word;
	
	
	Lexer A(argv[1]);
	string array[1000];
	if (readFile.is_open()){
		while(readFile >> word){
			array[x] = word;
			x++;
		}
	}
	int i = 0;
	while(i < x){
		cout << array[i] << endl;
		i++;
	}
	
	readFile.close();
	
	cout << x << endl;
	
	return 0;
}