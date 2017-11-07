#include "lexer.h"
//how the functions do what they do
Lexer::Lexer(string x){
	file = x;
};

void Lexer::GetToken(){}

void Lexer::printArray(){
	char array[100];
	int sizeArray = 1;
	for(int i = 0; i < sizeArray; i++){
		cout << array[i] << endl;
	}
}