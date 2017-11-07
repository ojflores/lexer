#include "lexer.h"
//how the functions do what they do
Lexer::Lexer(const char* x){
	file = x;
	counter = 0;
}

void Lexer::GetToken(){}

void Lexer::printArray(){
	int i = 0;
	while(i < counter){
		cout << array[i] << endl;
		i++;
	}
}

void Lexer::openFile(){
	ifstream readFile;
	readFile.open(file);
	string word;

	
	if (readFile.is_open()){
		while(readFile >> word){
			array[counter] = word;
			counter++;
		}
	}
}