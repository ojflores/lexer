#include "lexer.h"
#include "yytype.h"
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
	token_counter = 0;
	finally = new Token[SIZE];
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
	string add;
	compare = word[wlength];
	
	sum += compare[0];
	
	if(sum == 34){
		identifier = 326;
		parenthesis_arr[parenthesis_count] = word;
		
		if(string_length > MAX_STRING_LENGTH){
			
			for(i = 0; i < MAX_STRING_LENGTH; i++){
				add += parenthesis_arr[i];
				
			}
			finally[token_counter].word[i] += add;
			finally[token_counter].nCode = identifier; 
			cout << "too many characters in this string" << identifier << endl;
			token_counter++;
		}
		else{
			for(i = 0; i < parenthesis_count+1; i++){
				add += parenthesis_arr[i];
			}
			finally[token_counter].word[0] += add;
			finally[token_counter].nCode = identifier;
			token_counter++;
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
	string add;
	if(word.length() > MAX_LENGTH){
		cout << "ERROR, " << file << "ID length too long" << word << endl;
		for(i = 0; i < MAX_LENGTH; i++){
			cout << word[i];
		}
		int identifier = 324;
		add = word;
		finally[token_counter].word[0] += add;
		finally[token_counter].nCode = identifier; 
		token_counter++;
		cout << endl;
	}
	else{
		int identifier = 324;
		add = word;
		finally[token_counter].word[0] += add;
		finally[token_counter].nCode = identifier; 
		
		token_counter++;
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
	string add;
	for(i = 0; i < word.length(); i++){
		compare = word[i];
		if(compare == "E"){
			int identifier = 324;
			add = word;
			finally[token_counter].word[0] += add;
			finally[token_counter].nCode = identifier; 
		
			token_counter++;
			break;
		}
	}
	if(i > 9 || ((wlength-i) > 14)){
		cout << "ERROR, " << file << "too many characters" << word << endl;
		
	}
	else{
		identifier = 327;
		
		add = word;
		finally[token_counter].word[0] += add;
		finally[token_counter].nCode = identifier; 
		
		token_counter++;			//add the return variable here
	}
	
	
}

void Lexer::tokenize_number(string word, string character){
	int identifier;
	string add;
	if(is_mantice(word) > 0){
		mantice(word);
		return;
	}
	int i, n = 0;
	int wlength = word.length();
	string compare, zero = "0";
	compare = word[wlength-1];
	if(wlength > 10){
		cout << "ERROR, " << file << "Integer too long" << word << endl;
		
		for(i = 0; i < 10; i++){
			add += word[i];
		}
		identifier = 325;
		add = word;
		finally[token_counter].word[0] += add;
		finally[token_counter].nCode = identifier; 
		
		token_counter++;
		
		
		cout << "H\n" << " " << identifier;
	}
	else if((compare != "H") && (compare != "X")){
		cout << word;
		cout << "ERROR, " << file << "No 'H' at the end of your hex number" << word << endl;
	}
	else if(compare == "X"){
		identifier = 328;
		add = word;
		finally[token_counter].word[0] += add;
		finally[token_counter].nCode = identifier; 
		token_counter++;
	}
	else{										//does not take off leading zeros
		identifier = 325;
		for(n; n < word.length(); n++){
			add += word[n];
		}
		finally[token_counter].word[0] += add;
		finally[token_counter].nCode = identifier; 
		token_counter++;
	}
	cout << endl;
	return;
}

void Lexer::tokenize_punk(string word, string character){
	string punkTokens[PUNK] = {"&", "^", "|", ":", ",", "=", ">", "{", "[", "(", "<", "-", "#", "+", "}", "]", ")", ";", "~", "/", "*"};
	int punkTokens_t[PUNK] = {292, 293, 295, 296, 297, 300, 301, 303, 304, 305, 306, 308, 309, 310, 311, 312,
	313, 314, 315, 316, 317};
	string add;
	int i;
	for(i = 0; i < PUNK; i++){
		if(word == punkTokens[i]){
			int identifier = punkTokens_t[i];
			add = punkTokens[i];
			finally[token_counter].word[0] += add;
			finally[token_counter].nCode = identifier; 
			token_counter++;
			break;
		}
	}
	if( i == PUNK){
		cout << "ERROR, " << file << "Unknown character" << word << endl;
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
	string add;
	
	if((compare == "X") && (word.length() <= 4)){
		identifier = 328;
		add = word;
		finally[token_counter].word[0] += add;
		finally[token_counter].nCode = identifier; 
		token_counter++;
		
		return;
	}
	
	 
	
	int i;
	for(i = 0; i < KEYWORD; i++){
		if(word == token[i]){
			identifier = token_t[i];
			add = word;
			finally[token_counter].word[0] += add;
			finally[token_counter].nCode = identifier; 
			token_counter++;
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

void Lexer::put_out(){
	int i;
	for(i = 0; i < token_counter; i++){
		switch (finally[i].nCode)
        {
            case T_ARRAY:
                cout << "keyword: ARRAY\n";
                break;
            case T_BEGIN:
                cout << "keyword: BEGIN\n";
                break;
            case T_BY:
                cout << "keyword: BY\n";
                break;
            case T_CASE:
                cout << "keyword: CASE\n";
                break;
            case T_CONST:
                cout << "keyword: CONST\n";
                break;
            case T_DIV:
                cout << "keyword: DIV\n";
                break;
            case T_DO:
                cout << "keyword: DO\n";
                break;
            case T_ELSE:
                cout << "keyword: ELSE\n";
                break;
            case T_ELSIF:
                cout << "keyword: ELSIF\n";
                break;
            case T_END:
                cout << "keyword: END\n";
                break;
            case T_EXIT:
                cout << "keyword: EXIT\n";
                break;
            case T_FOR:
                cout << "keyword: FOR\n";
                break;
            case T_IF:
                cout << "keyword: IF\n";
                break;
            case T_IMPORT:
                cout << "keyword: IMPORT\n";
                break;
            case T_IN:
                cout << "keyword: IN\n";
                break;
            case T_IS:
                cout << "keyword: IS\n";
                break;
            case T_LOOP:
                cout << "keyword: LOOP\n";
                break;
            case T_MOD:
                cout << "keyword: MOD\n";
                break;
            case T_MODULE:
                cout << "keyword: MODULE\n";
                break;
            case T_NIL:
                cout << "keyword: NIL\n";
                break;
            case T_OF:
                cout << "keyword: OF\n";
                break;
            case T_OR:
                cout << "keyword: OR\n";
                break;
            case T_POINTER:
                cout << "keyword: POINTER\n";
                break;
            case T_PROCEDURE:
                cout << "keyword: PROCEDURE\n";
                break;
            case T_RECORD:
                cout << "keyword: RECORD\n";
                break;
            case T_REPEAT:
                cout << "keyword: REPEAT\n";
                break;
            case T_RETURN:
                cout << "keyword: RETURN\n";
                break;
            case T_THEN:
                cout << "keyword: THEN\n";
                break;
            case T_TO:
                cout << "keyword: TO\n";
                break;
            case T_TYPE:
                cout << "keyword: TYPE\n";
                break;
            case T_UNTIL:
                cout << "keyword: UNTIL\n";
                break;
            case T_VAR:
                cout << "keyword: VAR\n";
                break;
            case T_WHILE:
                cout << "keyword: WHILE\n";
                break;
            case T_WITH:
                cout << "keyword: WITH\n";
                break;
            case T_BOOLEAN:
                cout << "predef id: BOOLEAN\n";
                break;
            case T_CHAR:
                cout << "predef id: CHAR\n";
                break;
            case T_FALSE:
                cout << "predef id: FALSE\n";
                break;
            case T_INTEGER:
                cout << "predef id: INTEGER\n";
                break;
            case T_NEW:
                cout << "predef id: NEW\n";
                break;
            case T_REAL:
                cout << "predef id: REAL\n";
                break;
            case T_TRUE:
                cout << "predef id: TRUE\n";
                break;
            case T_AMPERSAND:
                cout << "punctuation: AMPERSAND\n";
                break;
            case T_ARROW:
                cout << "punctuation: ARROW\n";
                break;
            case T_ASSIGN:
                cout << "punctuation: ASSIGN\n";
                break;
            case T_BAR:
                cout << "punctuation: BAR\n";
                break;
            case T_COLON:
                cout << "punctuation: COLON\n";
                break;
            case T_COMMA:
                cout << "punctuation: COMMA\n";
                break;
            case T_DOTDOT:
                cout << "punctuation: DOTDOT\n";
                break;
            case T_DOT:
                cout << "punctuation: DOT\n";
                break;
            case T_EQU:
                cout << "punctuation: EQU\n";
                break;
            case T_GT:
                cout << "punctuation: GT\n";
                break;
            case T_GTE:
                cout << "punctuation: GTE\n";
                break;
            case T_LBRACE:
                cout << "punctuation: LBRACE\n";
                break;
            case T_LBRACKET:
                cout << "punctuation: LBRACKET\n";
                break;
            case T_LPAREN:
                cout << "punctuation: LPAREN\n";
                break;
            case T_LT:
                cout << "punctuation: LT\n";
                break;
            case T_LTE:
                cout << "punctuation: LTE\n";
                break;
            case T_MINUS:
                cout << "punctuation: MINUS\n";
                break;
            case T_NEQ:
                cout << "punctuation: NEQ\n";
                break;
            case T_PLUS:
                cout << "punctuation: PLUS\n";
                break;
            case T_RBRACE:
                cout << "punctuation: RBRACE\n";
                break;
            case T_RBRACKET:
                cout << "punctuation: RBRACKET\n";
                break;
            case T_RPAREN:
                cout << "punctuation: RPAREN\n";
                break;
            case T_SEMI:
                cout << "punctuation: SEMI\n";
                break;
            case T_SLASH:
                cout << "punctuation: SLASH\n";
                break;
            case T_STAR:
                cout << "punctuation: STAR\n";
                break;
            case T_TILDE:
                cout << "punctuation: TILDE\n";
                break;
            case T_ID:
                cout << "identifier\n";
                break;
            case T_INT_LITERAL:
                cout << "integer literal\n";
                break;
            case T_STR_LITERAL:
                cout << "string literal\n";
                break;
            case T_REAL_LITERAL:
                cout << "real literal\n";
                break;
            case T_CHAR_LITERAL:
                cout << "character literal\n";
                break;
        }

	}
}
