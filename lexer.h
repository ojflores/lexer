#ifndef LEXER_H
#define LEXER_H
#include <iostream>
#include <string>
#include <cstring>
#include <sstream>
#include <fstream>
#define SIZE 10000
using namespace std;

class Lexer{
	private:
		const char* file;
		string array[SIZE];
		string pulled_apart[SIZE];
		int counter;
		int point;
		string punkTokens[22];
		struct {
			string* word;
			int nCode;
		};
	public:
		
		
		//constructor
		Lexer(const char*);
		
		//takes the input and finds what token it is classified as
		void GetToken();
		
		//prints array
		void printArray();
		
		//opens the file from which we are reading
		void openFile();
		
		//seperates all the words into lexemes
		void lexemeGenerator();
	
	
};

#endif