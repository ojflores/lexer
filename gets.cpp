#include "lexer.h"
#define KEYWORD 41
#define PUNK 22
#define MAX_LENGTH 40
#define MAX_STRING_LENGTH 82
//how the functions do what they do
//g++ lexer.cpp gets.cpp -o lexer
Lexer::Lexer(const char* x){
	file = x;
	counter = 0;
	point = 0;
	parenthesis_count = 0;
	string_length = 0;
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
	if(parenthesis_count > 0){
		parenthesis(word);
	}
	else if(sum == 34){
		parenthesis_arr[parenthesis_count] = word;
		parenthesis_count++;
	}
	else if((sum > 64) && (sum < 91)){
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

void Lexer::parenthesis(string word){
	int identifier;
	parenthesis_count++;
	int sum = 0, i;
	int wlength = word.length() -1;
	string_length += word.length();
	string compare;
	compare = word[wlength];
	
	sum += compare[0];
	
	if(sum == 34){
		identifier = 326;
		parenthesis_arr[parenthesis_count] = word;
		for(i = 0; i < parenthesis_count+1; i++){
			cout << " " << parenthesis_arr[i];
		}
		cout << "     T_REAL_LITERAL\n";
		if(string_length > MAX_STRING_LENGTH){
		cout << "too many characters in this string" << identifier << endl;
		}
		parenthesis_count = 0;
		cout << endl;
		string_length = 0;
		return;
	}
	parenthesis_arr[parenthesis_count] = word;
	
	
}

void Lexer::tokenize_var(string word, string character){
	int i;
	if(word.length() > MAX_LENGTH){
		cout << "     ID length is too long. 40 characters max\n";
		for(i = 0; i < MAX_LENGTH; i++){
			cout << word[i];
		}
		cout << endl;
	}
	else{
		int identifier = 324;
		cout << word << "     T_ID" << identifier << endl;
	}
	return;
}

int Lexer::is_mantice(string word){
	int i;
	string compare;
	for(i = 0; i < word.length(); i++){
		compare = word[i];
		if(compare == "."){
			return 1;
		}
	}
	return 0;
}

//Double check if this is right man
void Lexer::mantice(string word){
	int wlength = word.length();
	string compare;
	int i;
	int identifier;
	for(i = 0; i < word.length(); i++){
		compare = word[i];
		if(compare == "E"){
			cout << "     T_REAL_LITERAL\n";
			break;
		}
	}
	if(i > 9 || ((wlength-i) > 14)){
		cout << "too many symbols in this mantissa\n";
	}
	else{
		identifier = 327;
		cout << word << identifier << endl;				//add the return variable here
	}
	
	
}

void Lexer::tokenize_number(string word, string character){
	int identifier;
	if(is_mantice(word) > 0){
		mantice(word);
		return;
	}
	int i, n = 0;
	int wlength = word.length();
	string compare, zero = "0";
	compare = word[wlength-1];
	if(wlength > 10){
		cout << word << "     integer literal too long\n";
		for(i = 0; i < 10; i++){
			cout << word[i];
		}
		identifier = 325;
		cout << "H\n" << " " << identifier;
	}
	else if((compare != "H") && (compare != "X")){
		cout << word;
		cout << "     illegal hex integer literal\n";
	}
	else if(compare == "X"){
		identifier = 328;
		cout << word << "     T_CHAR_LITERAL\n" << identifier;
	}
	else{										//does not take off leading zeros
		for(n; n < word.length(); n++){
			cout << word[n];
		}
		 cout << "      T_INT_LITERAL";
	}
	cout << endl;
	return;
}

void Lexer::tokenize_punk(string word, string character){
	string punkTokens[PUNK] = {"&", "^", "|", ":", ",", "=", ">", "{", "[", "(", "<", "-", "#", "+", "}", "]", ")", ";", "~", "/", "*"};
	int punkTokens_t[PUNK] = {292, 293, 295, 296, 297, 300, 301, 303, 304, 305, 306, 308, 309, 310, 311, 312,
	313, 314, 315, 316, 317};
	int i;
	for(i = 0; i < PUNK; i++){
		if(word == punkTokens[i]){
			int identifier = punkTokens_t[i];
			cout << word << "     " << identifier << endl;
			break;
		}
	}
	if( i == PUNK){
		cout << word << "      << I'm sorry but that is an illegal symbol\n";
	}
	
	
	return;
}

//what if they are not a keyword?
void Lexer::tokenize_keyword(string word, string character){
	string token[KEYWORD] = {"ARRAY", "BEGIN", "BY", "BOOLEAN", "CASE", "CONST", 
						"CHAR", "DIV", "DO", "ELSE", "ELSIF", "END",
						"EXIT", "FOR", "FALSE", "IF", "IMPORT",
						"IN", "IS", "INTEGER", "LOOP", "MOD", 
						"MODULE", "NIL", "NEW", "OF", "OR", 
						"POINTER", "PROCEDURE", "RECORD", "REAL",
						"REPEAT", "RETURN", "THEN", "TO","TYPE",
						"TRUE", "UNTIL", "VAR", "WHILE", "WITH"};
	int token_t[KEYWORD] = {257, 258, 259, 318, 260,
						261, 319, 262, 263, 264, 265, 
						266, 267, 268, 320, 269, 270,
						271, 272, 321, 273, 274, 275,
						277, 276, 278, 279, 280, 281,
						282, 322, 283, 284, 285, 286,
						287, 323, 288, 289, 290, 291};
	
	int identifier;
	int wlength = word.length();
	string compare;
	compare = word[wlength-1];
	
	
	if((compare == "X") && (word.length() <= 4)){
		identifier = 328;
		cout << word << "     T_CHAR_LITERAL" << identifier << endl;
		return;
	}
	
	
	
	int i;
	for(i = 0; i < KEYWORD; i++){
		if(word == token[i]){
			identifier = token_t[i];
			cout << word << "     " << identifier << endl;
			break;
		}
	}
	if(i == KEYWORD){
		tokenize_var(word, character);
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
