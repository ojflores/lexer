#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include "lexer.h"
using namespace std;


int main(int argc, const char * argv[]){
	cout << argv[1] << endl;
	
	
	Lexer A(argv[1]);
	A.openFile();
	//A.printArray();
	
	A.lexemeGenerator();
	//A.print_pulled_apart();
	A.findToken();
	A.put_out();

	
	return 0;
}