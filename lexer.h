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
		string new_aww[SIZE];
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
		
		//individually passes each word to find its token in GetToken
		void findToken();
		
		//takes and assigns a token to each item
		void GetToken(string, string);
		
		//prints array
		void printArray();
		
		//opens the file from which we are reading
		void openFile();
		
		//seperates all the words into lexemes
		void lexemeGenerator();
		
		void print_pulled_apart();
		
		void check_array();
		
		void tokenize_keyword(string, string);
	
	
};

#endif