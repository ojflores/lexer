#include "lexer.h"
//how the functions do what they do
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
	int n, p;
	int i = 0;
	int word_length;
	
	string words;
	string punkTokens[23] = {"&", "^", "|", ":", ",", ".", "=", ">", "{", "[", "(", "<", "-", "#", "+", "}", "]", ")", ";", "~", "/", "*"};
	string token;
	string compare;
	for(i = 0; i < counter; i++){
		words = array[i];
		word_length = words.size();
		for(n = 0; n < word_length; n++){
			for(p = 0; p < 23; p++){
				token = punkTokens[p];
				compare = words[n];
				if(token == compare){
					//cout << token << endl;
					pulled_apart[point] = token;
					point++;
					words.erase(n, 1);
					//cout << words << endl;
					
				}
				
			}
		pulled_apart[point] = compare;
		point++;
		}
		
	}
	
	
}

























