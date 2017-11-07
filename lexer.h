#ifndef LEXER_H
#define LEXER_H
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
using namespace std;

class Lexer{
	private:
		string file;
	public:
		
		
		//constructor
		Lexer(string text_file);
		
		//takes the input and finds what token it is classified as
		void GetToken();
		
		//prints array
		void printArray();
	
	
};

#endif