#include "lexer.h"
#define KEYWORD 41
#define PUNK 22
//how the functions do what they do
//g++ lexer.cpp gets.cpp -o lexer
Lexer::Lexer(const char* x){
	file = x;
	counter = 0;
	point = 0;
}

void Lexer::findToken(){
	int i = 0;
	string words, character;
	for(i = 0; i < point; i++){
		if(pulled_apart[i].length() > 0){
			words = pulled_apart[i];
			character = words[0];
			GetToken(words, character);
		}
	}
	
}

void Lexer::GetToken(string word, string character){
	int sum = 0;
	sum += character[0];
	if((sum > 64) && (sum < 91)){
		tokenize_keyword(word, character);
	}
	
	
	
	return;
}

void Lexer::tokenize_keyword(string word, string character){
	string token[KEYWORD] = {"ARRAY", "BEGIN", "BY", "BOOLEAN", "CASE", "CONST", "CHAR", "DIV", "DO", "ELSE", "ELSIF", "END", "EXIT", "FOR", "FALSE", "IF", "IMPORT",
	"IN", "IS", "INTEGER", "LOOP", "MOD", "MODULE", "NIL", "NEW", "OF", "OR", "POINTER", "PROCEDURE", "RECORD", "REAL", "REPEAT", "RETURN", "THEN", "TO",
	"TYPE", "TRUE", "UNTIL", "VAR", "WHILE", "WITH"};
	
	
	
	
}

void Lexer::printArray(){
	int i = 0;
	while(i < counter){
		cout << array[i] << endl;
		i++;
	}
}

void Lexer::print_pulled_apart(){
	int i = 0;
	while(i < point+1){
		cout << pulled_apart[i] << endl;
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

void Lexer::lexemeGenerator(){
	string punkTokens[PUNK] = {"&", "^", "|", ":", ",", "=", ">", "{", "[", "(", "<", "-", "#", "+", "}", "]", ")", ";", "~", "/", "*"};
	int i, b, p;
	string words, compare, token;
	for(i = 0; i < counter; i++){				//for each item in the array
		words = array[i];						//puts the item in array[i] in words
		
		for(b = 0; b < words.length(); b++){	//for every character in the string
			int point_break = 0;
			compare = words[b];
			for(p = 0; p < 22; p++){			//compare with every char in the punkTokens array
				if(compare == punkTokens[p]){
					point++;
					point_break = 1;
					pulled_apart[point] += compare;
					point++;
					break;
				}
			}
			if(point_break == 0){
				pulled_apart[point] += compare;
			}
		}
		point++;	
	}	
}









