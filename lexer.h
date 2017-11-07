#ifndef LEXER_H
#define LEXER_H
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
using namespace std;

class Lexer{
	private:
		const char* file;
		string array[10000];
		int counter;
	public:
		
		
		//constructor
		Lexer(const char*);
		
		//takes the input and finds what token it is classified as
		void GetToken();
		
		//prints array
		void printArray();
		
		void openFile();
	
	
};

#endif