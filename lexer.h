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
		string parenthesis_arr[SIZE];
		int counter;
		int point;
		int parenthesis_count;
		int string_length;
		string punkTokens[22];
		struct Token{
			string word[84];
			int nCode;
		};
		Token * finally;
		int token_counter;
		
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
		
		//prints the array "pulled_apart"
		void print_pulled_apart();
		
		//gets the token of a given keyword
		void tokenize_keyword(string, string);
		
		//gets the token of a given variable
		void tokenize_var(string, string);
		
		//gets the token of either a number or a mantice, also decideds which is which
		void tokenize_number(string, string);
		
		//gets the token of a punctuation symbol
		void tokenize_punk(string, string);
		
		//handles when strings are in the input 
		void parenthesis(string);
		
		//checks if a number given can be a mantice
		int is_mantice(string);
		
		//handles the tokenization of the mantice
		void mantice(string);
	
	
};

#endif