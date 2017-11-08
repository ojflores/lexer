#include "lexer.h"
//how the functions do what they do
//g++ lexer.cpp gets.cpp -o lexer
Lexer::Lexer(const char* x){
	file = x;
	counter = 0;
	point = 0;
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

void Lexer::lexemeGenerator(){
	int n, p, c = 0;
	int i = 0;
	int word_length;
	
	string words;
	string punkTokens[22] = {"&", "^", "|", ":", ",", "=", ">", "{", "[", "(", "<", "-", "#", "+", "}", "]", ")", ";", "~", "/", "*"};
	string token;
	string compare;
	for(i = 0; i < counter; i++){
		words = array[i];
		word_length = words.size();
		for(n = 0; n < word_length; n++){
			for(p = 0; p < 22; p++){
				token = punkTokens[p];
				compare = words[n];
				
				if(token == compare){
					//cout << token << endl;
					
					point++;
					pulled_apart[point] = token;
					point++;
					words.erase(n, 1);
					//cout << words << endl;	
				}
				
				
				
			}
			
			pulled_apart[point] += words[n];
			
			
		}
		
	}
	
	for(i = 0; i < point+2; i++){
		cout << pulled_apart[i] << endl;
	}
	
	
}

void Lexer::is_keyword(){
	/*
	looks at all the left over strings that are not tokens and decideds if it's a keyword or not
	*/
}























