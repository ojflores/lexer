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
	else if((sum > 96) && (sum < 123)){
		tokenize_var(word, character);
	}
	else if((sum > 47) && (sum < 58)){
		tokenize_number(word, character);
	}
	else{
		tokenize_punk(word, character);
	}
	
	
	
	return;
}

void Lexer::tokenize_var(string word, string character){
	
	return;
}

void Lexer::tokenize_number(string word, string character){
	cout << word << endl;
	return;
}

void Lexer::tokenize_punk(string word, string character){
	string punkTokens[PUNK] = {"&", "^", "|", ":", ",", "=", ">", "{", "[", "(", "<", "-", "#", "+", "}", "]", ")", ";", "~", "/", "*"};
	string punkTokens_t[PUNK] = {"T_&", "T_^", "T_|", "T_:", "T_,", "T_=", "T_>", "T_{", "T_[", "T_(", "T_<", "T_-", "T_#", "T_+", "T_}", "T_]",
	"T_)", "T_;", "T_~", "T_/", "T_*"};
	int i;
	for(i = 0; i < PUNK; i++){
		if(word == punkTokens[i]){
			cout << word << " " << punkTokens_t[i] << endl;
			break;
		}
	}
	if( i == PUNK){
		cout << word << " << I'm sorry but that is an illegal symbol\n";
	}
	
	
	return;
}

//what if they are not a keyword?
void Lexer::tokenize_keyword(string word, string character){
	string token[KEYWORD] = {"ARRAY", "BEGIN", "BY", "BOOLEAN", "CASE", "CONST", "CHAR", "DIV", "DO", "ELSE", "ELSIF", "END", "EXIT", "FOR", "FALSE", "IF", "IMPORT",
	"IN", "IS", "INTEGER", "LOOP", "MOD", "MODULE", "NIL", "NEW", "OF", "OR", "POINTER", "PROCEDURE", "RECORD", "REAL", "REPEAT", "RETURN", "THEN", "TO",
	"TYPE", "TRUE", "UNTIL", "VAR", "WHILE", "WITH"};
	string token_t[KEYWORD] = {"T_ARRAY", "T_BEGIN", "T_BY", "T_BOOLEAN", "T_CASE", "T_ONST", "T_CHAR", "T_DIV", "T_DO", "T_ELSE", "T_ELSIF", "T_END", "T_EXIT", "T_FOR", "T_FALSE", "T_IF", "T_IMPORT",
	"T_IN", "T_IS", "T_INTEGER", "T_LOOP", "T_MOD", "T_MODULE", "T_NIL", "T_NEW", "T_OF", "T_OR", "T_POINTER", "T_PROCEDURE", "T_RECORD", "T_REAL", "T_REPEAT", "T_RETURN", "T_THEN", "T_TO",
	"T_TYPE", "T_TRUE", "T_UNTIL", "T_VAR", "T_WHILE", "T_WITH"};
	int i;
	for(i = 0; i < KEYWORD; i++){
		if(word == token[i]){
			cout << word << " " << token_t[i] << endl;
			break;
		}
	}
	if(i == KEYWORD){
		cout << word << " T_ID" << endl;
	}
	
	
	
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









